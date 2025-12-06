# Claude Context: Homestead Twin Project

This document provides comprehensive context for Claude Code sessions working on the Homestead Twin project. Read this to quickly understand the project architecture, conventions, and workflows.

---

## Project Overview

### What is Homestead Twin?

The **Homestead Twin** is a single-user Unreal Engine 5.x digital twin application for the Fluxology Homestead — a private, off-grid technology homestead. It provides:

- **Spatially accurate 3D/VR environment** of the physical property, containers, and infrastructure
- **Operations planning and training tool** for power, IT, security, and deterrence systems
- **Visual front-end** for 3D-scanned geometry and future live telemetry integration
- **Documentation platform** linking Standard Operating Procedures (SOPs) to physical objects

**This is NOT a game.** It's a practical planning and operations tool with simulation flavor.

### Key Design Principles

1. **Accuracy over aesthetics**: 1:1 spatial representation using real-world 3D scans
2. **Utility over polish**: Functional tools, not AAA graphics
3. **Air-gap capable**: No hard dependency on internet or cloud services
4. **Single maintainer**: Optimized for solo development, not a team
5. **Iterative development**: Greybox → scans → refinement → telemetry

### Core Technologies

- **Engine**: Unreal Engine 5.7 (Nanite + Lumen capable)
- **Platforms**: Windows Desktop (primary), PCVR via SteamVR (planned)
- **Input**: Desktop (keyboard/mouse via Enhanced Input), VR (teleport + smooth locomotion - TODO)
- **3D Scanning**: Tier 2 prosumer handheld scanners (Einstar/Miraco class)
- **Telemetry (future)**: REST APIs, MQTT topics (NetBotz, PV/battery monitoring, security sensors)
- **Modules**: HeadMountedDisplay, UMG, Slate, JSON, HTTP, EnhancedInput

---

## Repository Structure

```
/flux-interface/
├── homestead_twin/          # Unreal Engine 5.x project
│   └── Project/
│       ├── HomesteadTwin.uproject
│       ├── Content/         # UE assets (Blueprints, widgets, scans)
│       └── Source/          # C++ code (optional, minimal)
├── data/                    # NOT IN GIT (large files)
│   ├── scans/
│   │   ├── raw/             # Raw 3D scan captures (vendor-specific formats)
│   │   └── processed/
│   │       ├── for_ue5/     # FBX/OBJ meshes for Unreal import
│   │       └── for_cad/     # STL/STEP for CAD/printing
│   ├── textures/            # Optional texture overlays
│   └── exports/             # Screenshots, videos, documentation exports
├── docs/                    # Design and operational documentation
│   ├── design/              # Architecture, coordinate system, phase plans
│   ├── procedures/          # SOP definitions and structure
│   ├── scanners/            # 3D scanner workflows and hardware evaluation
│   └── telemetry/           # Telemetry endpoint specs (future)
├── tools/                   # Helper scripts (Blender automation, mesh processing)
├── ROADMAP.md               # Phased development plan (Phases A–G)
├── README.md                # Quick start and repo overview
└── claude.md                # This file (Claude context primer)
```

### Important: What's Gitignored

- `data/scans/raw/` — Raw 3D scan data (extremely large)
- `homestead_twin/Project/Saved/`, `Intermediate/`, `Binaries/` — UE temporary/build files
- Large binary assets that don't compress well

---

## Coordinate System (Critical!)

All spatial work must align to this coordinate system:

- **Units**: 1 Unreal unit = 1 cm
- **Origin (0,0,0)**: SW external corner of the rack container at final-grade ground level
- **Axes**:
  - **X+**: East
  - **Y+**: North
  - **Z+**: Up (standard UE Z-up)

Documented in: `docs/design/coordinate_system.md`

**Why this matters**: All scans, greybox meshes, and placed objects must respect this system for accurate spatial planning.

---

## Phase System (P0–P5)

The homestead is built out in phases. The application visualizes these phases to show planned vs. current vs. future state.

| Phase | Description |
|-------|-------------|
| **P0** | Minimal containers + basic power/data |
| **P1** | Workshop container, initial rack population |
| **P2** | Tiny-home container, basic orchard layout |
| **P3** | Greenhouse, expanded orchard, ponds/swales |
| **P4** | Extended perimeter and deterrence systems |
| **P5** | Full build-out (Aircela, auxiliary infrastructure) |

**Implementation**: `US_HomesteadPhaseManager` subsystem toggles actor visibility and level streaming based on current phase.

Documented in: `docs/design/phase_plan.md`

---

## Unreal Engine Architecture

### Core Framework

| Class/Asset | Purpose |
|-------------|---------|
| `GI_HomesteadTwin` | GameInstance subclass (persistent across levels) |
| `GM_HomesteadTwin` | GameMode (defines rules for main map) |
| `PC_Desktop` | PlayerController for desktop input |
| `PC_VR` | PlayerController for VR input |
| `Pawn_Desktop` | First-person pawn (WASD + mouse) |
| `Pawn_VR` | VR pawn (teleport/smooth locomotion) |

### Subsystems (Game Instance Subsystems)

Subsystems provide global, persistent functionality:

| Subsystem | Purpose |
|-----------|---------|
| `US_HomesteadPhaseManager` | Manages P0–P5 phase visibility and metadata |
| `US_SOPManager` | Loads and queries Standard Operating Procedures |
| `US_AnnotationManager` | Create/read/update/delete in-world annotations |
| `US_TelemetryManager` (future) | Poll and cache live telemetry data |
| `US_ScenarioManager` (future) | Trigger and manage scenario simulations |

### Object Model

**Base Actor**: `A_HomesteadObject`

- Properties:
  - `FString ObjectId` (e.g., "rack_main_42u_01")
  - `FString Category` (e.g., "rack", "container", "sensor", "deterrent")
  - `FTransform WorldTransform`
  - `UStaticMeshComponent* VisualMesh`
- Optional components:
  - `U_InteractableComponent` — handles interaction (E key / VR trigger)
  - `U_SOPComponent` — links to SOP data
  - `U_TelemetryComponent` (future) — live data display

**Why this matters**: All scanned and hand-modeled assets should inherit from `A_HomesteadObject` to support interaction, SOPs, and telemetry.

### UI Widgets (UMG)

| Widget | Purpose |
|--------|---------|
| `WID_HUD_Minimal` | Desktop HUD (minimal, non-intrusive) |
| `WID_HUD_VR` | VR HUD (3D space widgets) |
| `WID_PhaseSelector` | UI to switch between P0–P5 |
| `WID_ObjectInfoPanel` | Display object metadata when interacted with |
| `WID_SOPViewer` | Display SOP steps for selected object |
| `WID_AnnotationEditor` | Create/edit in-world annotations |
| `WID_TelemetryOverlay` (future) | Live telemetry dashboard |
| `WID_ScenarioPanel` (future) | Trigger scenario simulations |

---

## Standard Operating Procedures (SOPs)

SOPs are documented procedures linked to physical objects in the world.

### Data Structure

Defined in: `docs/procedures/sop_structure.md`

```
SOPId: string (e.g., "SOP_POWER_DOWN_RACK_01")
Title: string
LinkedObjectIds: array of ObjectIds
Steps: array of step text or structured data
EstimatedTime: duration
Tags: array of strings (e.g., "power", "fire", "security")
```

### Storage

- Stored in UE Data Table (imported from JSON or CSV)
- Managed by `US_SOPManager` subsystem
- Linked to objects via `U_SOPComponent`

### User Experience

1. User interacts with object (e.g., rack, generator)
2. `WID_ObjectInfoPanel` appears
3. If SOPs exist, `WID_SOPViewer` shows relevant procedures
4. User can step through procedures in-world

**Example SOPs**:
- Power-down sequence for rack
- Generator startup/shutdown
- Fire response in rack container
- Intrusion response at perimeter

---

## 3D Scanning Pipeline

### Workflow Overview

```
Physical world
  ↓
3D Scanner (Einstar/Miraco)
  ↓
Vendor software (align, clean, decimate)
  ↓
Export: FBX/OBJ (UE) + STL/STEP (CAD)
  ↓
Optional: MeshLab/Blender cleanup
  ↓
Import to UE: Content/Scans/...
```

Documented in: `docs/scanners/workflow_raw_to_processed.md`

### File Naming Conventions

**Raw scans**:
```
data/scans/raw/<area>/YYYY-MM-DD_area_detail_vN/
```
Example: `2025-11-20_rack_interior_v2/`

**Processed for UE**:
```
data/scans/processed/for_ue5/<area>/area_detail_1to1_vN.fbx
```
Example: `rack_interior_1to1_v3.fbx`

**Processed for CAD/Printing**:
```
data/scans/processed/for_cad/<category>/object_1to1_vN.(stl|step)
```
Example: `rack_mount_bracket_1to1_v1.stl`

### UE Import Rules

- All scanned meshes go under `Content/Scans/`:
  - `Content/Scans/Environment/`
  - `Content/Scans/Containers/`
  - `Content/Scans/Rack/`
  - `Content/Scans/Workshop/`
  - `Content/Scans/TinyHome/`
  - `Content/Scans/Greenhouse/`
- Verify scale on import: **1 Unreal unit = 1 cm**
- Start with simple generic materials; refine later if needed

---

## Telemetry System (Future Phase)

### Overview

Eventually, the twin will visualize live data from homestead systems:

- **NetBotz**: Temperature, humidity in rack container
- **PV/Battery**: SOC, voltage, current, production
- **Doors/Sensors**: Open/closed state, motion triggers
- **Security**: LRAD status, camera feeds (future)

### Architecture

- **`US_TelemetryManager`**: Polls REST endpoints or subscribes to MQTT topics
- **`U_TelemetryComponent`**: Attached to actors, displays data
- **Display modes**: Floating text, color overlays (green/yellow/red), time-series graphs

### Workflow

1. Define endpoints in: `docs/telemetry/telemetry_endpoints.md`
2. Configure `US_TelemetryManager` with endpoint URLs and poll intervals
3. Attach `U_TelemetryComponent` to relevant objects
4. Test with mock/dummy data first, then integrate real endpoints

**Important**: Design for offline fallback. App must work without telemetry.

---

## Scenario Simulations (Future Phase)

### Purpose

Test response to operational scenarios:

- **Power Failure**: Visualize which systems go offline
- **Intrusion at Perimeter**: Highlight LRAD coverage, camera FOVs, egress routes
- **Fire in Rack Container**: Show fire extinguisher locations, evacuation paths

### Implementation

- **`US_ScenarioManager`**: Manages scenario state
- **`WID_ScenarioPanel`**: UI to activate/reset scenarios
- **Visual effects**: Coverage cones, pathing arrows, color overlays

**Note**: These are visual planning tools, not full physics simulations.

---

## Critical Current Issues (2025-12-06)

### Build Status: BROKEN

**Current Error**: Forward declaration issue in `U_SOPComponent.cpp`
- `FStandardOperatingProcedure` is undefined
- Need proper include for `US_SOPManager.h` in header file

### Critical Blockers

1. **No Content Folder**: Project has no Content/, Blueprints, or maps
   - Cannot run or test the application
   - All C++ classes need Blueprint derivatives to be useful

2. **VR Systems**: All VR code is stubs (Pawn_VR, PC_VR)
   - Teleport locomotion: TODO
   - Smooth locomotion: TODO
   - All input handling: TODO

3. **Enhanced Input Not Configured**: All input bindings marked TODO
   - Desktop input partially working via legacy system
   - VR input completely unimplemented

4. **Data Loading Not Implemented**: Subsystems can't load data
   - SOP data table loading: TODO
   - Phase definitions loading: TODO
   - Annotation JSON save/load: TODO

### Next Required Steps

**To Get a Runnable Build:**
1. Fix compilation error (FStandardOperatingProcedure)
2. Create Content folder structure (`Content/`, `Content/Maps/`, `Content/Blueprints/`, `Content/UI/`)
3. Create test map (`Map_Homestead_Main`)
4. Create Blueprint classes derived from C++ base classes
5. Create minimal HUD widget
6. Configure Enhanced Input assets

**Phase A Completion Requirements:**
- All above steps completed
- Desktop navigation fully functional end-to-end
- Basic greybox geometry placeable
- Documentation updated to reflect actual state

---

## Development Workflow

### Current Phase

As of 2025-12-06, we are in **Phase A: Bootstrap & Foundation** (~30% complete).

C++ framework is ~70% complete, but Content/Blueprint work has not started (0%). The project cannot currently be run or tested.

### When Working on a New Feature

1. **Check the roadmap**: Is this feature planned? Which phase?
2. **Review related docs**:
   - Design docs in `docs/design/`
   - Workflow docs in `docs/scanners/`, `docs/telemetry/`, etc.
3. **Follow naming conventions**:
   - Maps: `Map_Homestead_Main`, `Map_RackInterior`
   - Blueprints: `BP_HomesteadObject`, `BP_Rack`, `BP_Container`
   - Widgets: `WID_SOPViewer`, `WID_PhaseSelector`
   - Subsystems: `US_HomesteadPhaseManager`, `US_SOPManager`
4. **Test in both desktop and VR** (if applicable)
5. **Document changes** in relevant docs or changelog

### When Importing New Scans

1. Place raw scan data in: `data/scans/raw/<area>/YYYY-MM-DD_area_detail_vN/`
2. Clean, decimate, export in vendor software or Blender
3. Export to: `data/scans/processed/for_ue5/<area>/area_detail_1to1_vN.fbx`
4. Import to UE: `Content/Scans/<area>/`
5. Verify scale (1 UE unit = 1 cm)
6. Place in map, align to coordinate system
7. Document in: `docs/scanners/workflow_raw_to_processed.md` or changelog

### When Creating SOPs

1. Define SOP structure in: `docs/procedures/sop_structure.md` (if not already)
2. Author SOP content (can be JSON, CSV, or inline in UE Data Table)
3. Import to UE Data Table
4. Link to relevant objects via `U_SOPComponent`
5. Test interaction: click object → view SOP

---

## Common Tasks & Patterns

### Task: Add a New Interactive Object

1. Create or place static mesh in world
2. Convert to `BP_HomesteadObject` (or subclass)
3. Set `ObjectId`, `Category`, and other metadata
4. Attach `U_InteractableComponent`
5. (Optional) Attach `U_SOPComponent` if SOPs exist
6. Test: look at object, press E (desktop) or trigger (VR)

### Task: Add a New Phase-Specific Object

1. Create object as above
2. Tag with phase metadata (e.g., "Phase 3")
3. Configure in `US_HomesteadPhaseManager` data table
4. Test: switch phases and verify visibility

### Task: Create a New UI Widget

1. Create UMG widget in `Content/UI/Widgets/`
2. Follow naming: `WID_<Name>`
3. Add to HUD or spawn on interaction
4. Test in both desktop and VR contexts
5. Ensure readable text and usable buttons in VR

### Task: Optimize Performance

1. **Profile first**: Use UE Profiler to identify bottlenecks
2. **Scanned meshes**: Decimate externally, use LODs, consider Nanite
3. **Lighting**: Prefer baked lighting or simple Lumen GI; avoid complex reflections
4. **Collision**: Use low-res collision meshes, disable physics on static objects
5. **Level streaming**: Load/unload interiors and distant zones
6. **Target**: 60+ FPS desktop (1440p), 90 Hz VR

---

## Important Constraints & Requirements

### Performance Targets

- **Desktop**: 60+ FPS at 1440p resolution
- **VR**: 90 Hz minimum (to avoid motion sickness)

### VR Comfort

- Follow VR best practices:
  - Smooth teleport arcs (not instant jumps)
  - Optional vignette during movement
  - Snap turning (45° increments)
  - No camera shake or forced movement
  - Readable UI text at distance

### Air-Gap Operation

- **No hard dependency on internet or cloud services**
- Telemetry is optional; app must work offline
- All assets and data stored locally

### Single Maintainer Philosophy

- **Prefer simplicity over clever solutions**
- **Document decisions inline and in docs/**
- **Avoid over-engineering**: "good enough" is often perfect
- **Blueprints over C++** (unless performance-critical)

### Security & Privacy

- This is a private homestead with security systems
- **Do not commit sensitive data** to git:
  - Telemetry endpoints with credentials
  - IP addresses, network topology
  - Security camera placement details (keep generic in docs)
- Use placeholders or generic examples in documentation

---

## Key Resources & References

### Internal Documentation

- **ROADMAP.md**: Phased development plan (Phases A–G)
- **docs/design/homestead_twin_design.md**: Detailed architecture (legacy detailed design)
- **docs/design/coordinate_system.md**: Coordinate system definition
- **docs/design/phase_plan.md**: Phase-by-phase build-out details
- **docs/procedures/sop_structure.md**: SOP data structure
- **docs/scanners/workflow_raw_to_processed.md**: 3D scanning workflow
- **docs/telemetry/telemetry_endpoints.md**: Telemetry endpoint specs (future)

### External References

- **Unreal Engine 5 Documentation**: https://docs.unrealengine.com/5.3/
- **VR Best Practices**: https://docs.unrealengine.com/5.3/en-US/VirtualReality/
- **Nanite**: https://docs.unrealengine.com/5.3/en-US/nanite-virtualized-geometry-in-unreal-engine/
- **Lumen**: https://docs.unrealengine.com/5.3/en-US/lumen-global-illumination-and-reflections-in-unreal-engine/
- **3D Scanning Best Practices**: (Vendor-specific; see `docs/scanners/hardware_evaluation.md`)

---

## Working with Claude: Best Practices

### What Claude Should Know

- **Current phase**: Check `ROADMAP.md` to understand what's in-scope now
- **Coordinate system**: Always verify spatial alignment (origin, axes)
- **Naming conventions**: Follow established patterns for Blueprints, widgets, subsystems
- **Performance constraints**: Keep VR performance in mind (90 Hz minimum)
- **Air-gap requirement**: Don't suggest cloud-based solutions

### When Claude Should Ask for Clarification

- **Ambiguous feature requests**: Which phase does this belong to?
- **Missing requirements**: What should the UX be? Desktop, VR, or both?
- **Performance tradeoffs**: Should this use Blueprints or C++?
- **Data sensitivity**: Is this information safe to document publicly?

### When Claude Should Suggest Alternatives

- **Over-engineering**: Propose simpler solutions first
- **Scope creep**: Flag features that should be deferred to later phases
- **Performance risks**: Warn about potential VR performance issues
- **Workflow inefficiencies**: Suggest better asset pipelines or automation

### Preferred Communication Style

- **Direct and concise**: No fluff, no over-the-top validation
- **Technically accurate**: Prioritize correctness over agreement
- **Objective**: Focus on facts and tradeoffs, not hype
- **Practical**: Suggest actionable next steps

---

## Quick Reference: File Paths

### Frequently Referenced Files

```
/flux-interface/ROADMAP.md                              # Development roadmap
/flux-interface/README.md                               # Quick start guide
/flux-interface/claude.md                               # This file (Claude context)
/flux-interface/docs/design/homestead_twin_design.md    # Detailed architecture
/flux-interface/docs/design/coordinate_system.md        # Coordinate system
/flux-interface/docs/design/phase_plan.md               # Phase definitions (P0–P5)
/flux-interface/docs/procedures/sop_structure.md        # SOP data structure
/flux-interface/docs/scanners/workflow_raw_to_processed.md  # Scanning workflow
/flux-interface/docs/telemetry/telemetry_endpoints.md   # Telemetry specs (future)
/flux-interface/homestead_twin/Project/HomesteadTwin.uproject  # UE project file
```

### Content Organization (UE)

```
Content/
├── Scans/                   # Imported 3D scans
│   ├── Environment/
│   ├── Containers/
│   ├── Rack/
│   ├── Workshop/
│   ├── TinyHome/
│   └── Greenhouse/
├── Blueprints/              # Blueprints (logic and actors)
│   ├── Core/                # GameInstance, GameMode, PlayerControllers
│   ├── Subsystems/          # Game Instance Subsystems
│   └── Actors/              # A_HomesteadObject and subclasses
├── UI/                      # UMG widgets
│   └── Widgets/
├── Materials/               # Materials and textures
└── Maps/                    # Levels and sub-levels
    ├── Main/
    └── Sublevels/
```

---

## Changelog & Version Tracking

### Current State (as of 2025-12-06)

- **Phase**: A (Bootstrap & Foundation) — ~30% complete
- **UE Version**: 5.7
- **UE Project**: C++ framework scaffolded (~70% complete), Content/Blueprints not started (0%)
- **Build Status**: Compiling but has forward declaration issue in U_SOPComponent.cpp
- **Documentation**: Comprehensive roadmap and design docs created
- **Scans**: None yet imported
- **SOPs**: Structure defined, example CSV data tables created
- **Telemetry**: Mock data generation working, real endpoints future phase (F)

### Implementation Status

**Fully Implemented (C++):**
- Desktop pawn movement (WASD, sprint, slow walk, camera)
- Annotation CRUD operations
- Phase switching logic
- SOP query methods (data loading TODO)
- Telemetry mock data generation
- Scenario activation framework
- Base object and component architecture

**Partially Implemented (Stubs/TODOs):**
- VR Pawn (structure only, all locomotion methods TODO)
- VR Player Controller (structure only, all methods TODO)
- Enhanced Input bindings (TODO across all controllers)
- Subsystem data loading from Data Tables (TODO)
- JSON save/load for annotations (TODO)
- Phase visibility and level streaming (TODO)

**Not Started:**
- Any Content folder structure
- Any Blueprint classes
- Any UI widgets (UMG)
- Any maps or levels
- Any 3D scans or assets
- VR functionality (all stubs)

### Update Log

- **2025-12-06**: Documentation audit and update; C++ implementation ~70% complete
- **2025-12-04**: Multiple build fixes (HeadMountedDisplay module, includes, component naming)
- **2025-11-16**: Initial roadmap and Claude context documentation created
- **2025-11-15**: UE5 project scaffolded, initial design docs
- **2025-11-14**: Repository initialized

---

## Common Pitfalls & How to Avoid Them

### Pitfall: Coordinate System Misalignment

**Problem**: Scanned meshes don't align with greybox or each other.

**Solution**:
- Always verify origin (rack container SW corner)
- Check axis orientation (X=East, Y=North, Z=Up)
- Use UE transform tools to align, then re-export scan if needed

### Pitfall: Performance Issues in VR

**Problem**: Frame rate drops below 90 Hz, causing nausea.

**Solution**:
- Profile first (UE Profiler, GPU Visualizer)
- Decimate scanned meshes externally
- Use LODs and Nanite where appropriate
- Simplify materials (avoid complex shaders)
- Implement level streaming for interiors

### Pitfall: Scope Creep

**Problem**: Feature requests expand beyond current phase.

**Solution**:
- Check `ROADMAP.md` — is this in the current phase?
- Defer "nice-to-have" features to later phases
- Maintain strict phase boundaries
- Document deferred features in roadmap "Post-Launch" section

### Pitfall: Data Loss (Scans, Work)

**Problem**: Raw scans or UE work lost due to hardware failure.

**Solution**:
- Back up `data/scans/raw/` to external storage (not in git)
- Commit UE content to git regularly
- Tag git releases at phase milestones
- Maintain offsite backup of critical data

### Pitfall: VR Comfort Issues

**Problem**: Users experience nausea or discomfort in VR.

**Solution**:
- Follow VR best practices (see UE VR docs)
- Implement comfort settings (vignette, snap turning)
- Test with multiple users if possible
- Avoid camera shake, forced movement, low frame rates

---

## FAQ for Claude

### Q: How do I know which phase we're in?

**A**: Check `ROADMAP.md`. Look for checked `[x]` milestones. The current phase is the earliest one with incomplete milestones.

### Q: Should I use Blueprints or C++?

**A**: Default to **Blueprints** unless:
- Performance-critical (e.g., tight loops, complex math)
- Requires engine-level access not exposed to Blueprints
- Maintainer explicitly requests C++

### Q: How do I test VR changes without a headset?

**A**: Use UE's VR Preview mode (simulates VR in editor). However, **always test on real hardware before committing VR features.**

### Q: What if a scan doesn't import correctly?

**A**: Common issues:
- **Scale wrong**: Check import settings (1 UE unit = 1 cm)
- **Polycount too high**: Decimate in Blender/MeshLab before import
- **Normals flipped**: Fix in Blender (Mesh → Normals → Recalculate Outside)
- **Multiple meshes**: Combine in Blender before export

### Q: How do I add a new SOP?

**A**: See "When Creating SOPs" in Development Workflow section above.

### Q: What if telemetry endpoints aren't available yet?

**A**: Use **mock/dummy data** during development (Phase F). `US_TelemetryManager` should support a "mock mode" config.

### Q: Can I add multiplayer features?

**A**: **No.** This is explicitly a single-user application. If multiplayer is needed in the future, it will be a major scope change requiring roadmap revision.

### Q: How do I handle sensitive information (IPs, credentials)?

**A**:
- **Never commit** sensitive data to git
- Use placeholder values in documentation
- Store credentials in local config files (gitignored)
- Document generic examples only

---

## Summary: Quick Start for Claude

When starting a new Claude Code session on this project:

1. **Read this file** (`claude.md`) for context
2. **Check `ROADMAP.md`** to understand current phase and priorities
3. **Review relevant design docs** in `docs/design/` for the task at hand
4. **Follow naming conventions** for Blueprints, widgets, and assets
5. **Test in both desktop and VR** (if applicable)
6. **Maintain coordinate system alignment** (origin, axes)
7. **Prioritize utility and performance** over visual polish
8. **Document decisions** inline or in relevant docs
9. **Ask for clarification** when requirements are ambiguous
10. **Flag scope creep** and suggest deferring to later phases

**This is a practical tool for a working homestead. Build accordingly.**

---

## Contact & Feedback

This is a single-maintainer project. For questions, clarifications, or suggestions:

- Update relevant docs in `docs/`
- Add notes to `ROADMAP.md` or phase-specific design docs
- Use in-world annotations (once `US_AnnotationManager` is implemented)

**Claude**: If you encounter unclear requirements or conflicting information in this documentation, flag it and ask for clarification.

---

**Last Updated**: 2025-12-06
**Roadmap Phase**: A (Bootstrap & Foundation) — ~30% Complete
**UE Version**: 5.7
**Build Status**: Has compilation errors (needs forward declaration fix)
**Next Critical Steps**: Fix build errors, create Content folder, create test map, create Blueprint classes
