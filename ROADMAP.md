# Homestead Twin Development Roadmap

## Project Vision

The **Homestead Twin** is a single-user Unreal Engine 5.x digital twin application for the Fluxology Homestead — providing a spatially accurate, interactive 3D/VR environment for operations planning, training, design iteration, and eventual live telemetry visualization.

**Core Objectives:**
- Accurate 1:1 spatial representation of homestead physical infrastructure
- VR and desktop navigation for immersive inspection and planning
- Integration of 3D-scanned geometry from site and structures
- Standard Operating Procedure (SOP) documentation linked to physical objects
- Phase-based visualization (P0–P5) to track build-out progress
- Future-ready telemetry visualization framework

## Development Philosophy

- **Start simple, iterate ruthlessly**: Greybox first, polish later
- **Scans drive geometry**: Real-world accuracy from 3D scanner pipeline
- **Tool, not game**: Prioritize utility and clarity over AAA presentation
- **Air-gap capable**: No hard dependency on internet or cloud services
- **Single maintainer**: Optimized for solo development workflow

---

## Phase A: Bootstrap & Foundation

**Goal**: Establish working UE5 project with basic navigation and architecture.

### Milestones

#### A.1 - Project Initialization
- [x] Create UE5 project structure (`homestead_twin/Project/HomesteadTwin.uproject`)
- [x] Set up repository structure (`data/`, `docs/`, `tools/`)
- [x] Document coordinate system (origin at rack container SW corner, X=East, Y=North, Z=Up)
- [ ] Configure `.gitignore` for large binary assets (raw scans, UE intermediate files)
- [ ] Set up UE project settings:
  - Target platform: Windows Desktop + PCVR (SteamVR)
  - Rendering: DirectX 12, Lumen/Nanite support
  - VR plugins enabled

#### A.2 - Core Framework
- [ ] Create base classes:
  - `GI_HomesteadTwin` (GameInstance)
  - `GM_HomesteadTwin` (GameMode)
  - `PC_Desktop` and `PC_VR` (PlayerControllers)
  - `Pawn_Desktop` and `Pawn_VR` (Player pawns)
- [ ] Implement basic movement:
  - Desktop: WASD + mouse look, sprint/slow walk
  - VR: Teleport locomotion, smooth locomotion toggle
- [ ] Create minimal HUD widgets:
  - `WID_HUD_Minimal` (desktop)
  - `WID_HUD_VR` (VR)

#### A.3 - Test Environment
- [ ] Create test map: `Map_Homestead_Main`
- [ ] Add basic terrain plane at origin
- [ ] Place greybox container meshes (rack, workshop, tiny home placeholders)
- [ ] Verify coordinate system alignment with real-world measurements

**Success Criteria:**
- Can launch project in UE5 Editor
- Can navigate test map in desktop mode (WASD + mouse)
- Can navigate test map in VR (teleport/smooth locomotion)
- Coordinate system documented and verified in-engine

**Estimated Duration**: 1–2 weeks

**Dependencies**: Unreal Engine 5.3+ installed, VR headset available for testing

---

## Phase B: Greybox Homestead & Phase System

**Goal**: Rough spatial layout of entire homestead with phase-based visibility toggling.

### Milestones

#### B.1 - Greybox Geometry
- [ ] Model or place greybox primitives for:
  - All container locations (rack, workshop, tiny home, greenhouse)
  - Orchard zones
  - Retention ponds / swales
  - PV array field
  - Perimeter fence line
  - Access roads/paths
- [ ] Verify real-world dimensions and spacing
- [ ] Create sub-levels for organization:
  - `Lvl_Containers`
  - `Lvl_OrchardAndSwales`
  - `Lvl_SecurityAndPerimeter`

#### B.2 - Phase Manager Subsystem
- [ ] Implement `US_HomesteadPhaseManager` (Game Instance Subsystem):
  - Enum: `EHomesteadPhase` {P0, P1, P2, P3, P4, P5}
  - Data table: phase definitions and associated actors/levels
  - API: `SetCurrentPhase(EHomesteadPhase)`, `GetCurrentPhase()`
- [ ] Tag greybox actors/levels with phase metadata
- [ ] Implement visibility toggling based on phase selection

#### B.3 - Phase UI
- [ ] Create `WID_PhaseSelector` widget:
  - Buttons for P0–P5
  - Display current phase name and description
  - Accessible from both desktop and VR
- [ ] Integrate with HUD

**Success Criteria:**
- All major homestead zones represented in greybox form
- Can toggle between P0–P5 and see appropriate geometry appear/disappear
- Phase selector UI functional in desktop and VR
- Scale and spacing match real-world site measurements

**Estimated Duration**: 2–3 weeks

**Dependencies**: Phase A complete, real-world site measurements available

---

## Phase C: First Scans & Asset Pipeline

**Goal**: Replace greybox with actual 3D-scanned geometry; establish scan import workflow.

### Milestones

#### C.1 - Scanner Selection & Workflow
- [ ] Finalize 3D scanner hardware selection (document in `docs/scanners/hardware_evaluation.md`)
- [ ] Document scanner-to-UE workflow (capture → clean → export → import)
- [ ] Set up file naming conventions:
  - Raw: `YYYY-MM-DD_area_detail_vN/`
  - Processed: `area_detail_1to1_vN.fbx`
- [ ] Create directory structure:
  - `data/scans/raw/`
  - `data/scans/processed/for_ue5/`
  - `data/scans/processed/for_cad/`

#### C.2 - Priority Scans
- [ ] Scan, process, and import:
  - Site terrain (ground surface around containers)
  - Rack container exterior
  - Rack container interior (first pass)
- [ ] Import into UE under `Content/Scans/`:
  - `Content/Scans/Environment/`
  - `Content/Scans/Containers/`
  - `Content/Scans/Rack/`
- [ ] Verify scale (1 Unreal unit = 1 cm)
- [ ] Apply simple placeholder materials

#### C.3 - Asset Integration
- [ ] Replace greybox rack container with scanned mesh
- [ ] Replace greybox terrain with scanned terrain
- [ ] Test navigation and collision meshes
- [ ] Document any issues or mesh cleanup needed

**Success Criteria:**
- At least 3 scanned assets imported and placed in main map
- Meshes aligned to coordinate system
- Performance acceptable (60+ FPS desktop, 90 Hz VR)
- Scan workflow documented and repeatable

**Estimated Duration**: 3–4 weeks

**Dependencies**: Phase B complete, 3D scanner acquired and operational, initial scans captured

---

## Phase D: Interaction & Object System

**Goal**: Make objects in the world interactive; link metadata and SOPs.

### Milestones

#### D.1 - Base Object Architecture
- [ ] Implement `A_HomesteadObject` base actor class:
  - Properties: `ObjectId`, `Category`, `WorldTransform`, `VisualMesh`
  - Support for components: `U_InteractableComponent`, `U_SOPComponent`, `U_TelemetryComponent`
- [ ] Create component classes:
  - `U_InteractableComponent`: handles look-at detection and interaction events
  - `U_SOPComponent`: links object to SOP data
- [ ] Implement interaction pattern:
  - Desktop: look at object, press E to interact
  - VR: laser pointer, trigger to interact

#### D.2 - Object Info UI
- [ ] Create `WID_ObjectInfoPanel` widget:
  - Display: Object name, category, description
  - Show linked SOPs (if any)
  - Show phase-specific notes
  - "Close" button / auto-dismiss on move away
- [ ] Integrate with interaction system
- [ ] Test with multiple objects (rack, container, generator pad, etc.)

#### D.3 - SOP System
- [ ] Define SOP data structure (see `docs/procedures/sop_structure.md`):
  - Fields: SOPId, Title, LinkedObjectIds, Steps, EstimatedTime, Tags
- [ ] Create SOP data table (CSV or JSON imported to UE)
- [ ] Implement `US_SOPManager` subsystem:
  - Load SOP data table
  - Query SOPs by ID or linked object
- [ ] Create `WID_SOPViewer` widget:
  - List SOPs for selected object
  - Display SOP steps in readable format
  - Support for categories/tags
- [ ] Create example SOPs:
  - `SOP_POWER_DOWN_RACK_01`
  - `SOP_GENERATOR_STARTUP`
  - `SOP_FIRE_RESPONSE_RACK`

#### D.4 - Annotation System
- [ ] Implement `US_AnnotationManager` subsystem:
  - Create/read/update/delete annotations
  - Persist to JSON file
- [ ] Create annotation actor: `A_Annotation`
  - 3D marker (billboard sprite or simple mesh)
  - Text content, category, timestamp
- [ ] Implement annotation creation UX:
  - Desktop: right-click menu or hotkey
  - VR: laser pointer + button press
- [ ] Create `WID_AnnotationEditor` widget for editing notes

**Success Criteria:**
- Can interact with objects in world (click/VR trigger)
- Object info panel displays correctly for multiple objects
- At least 3 example SOPs created and viewable in-world
- Can create, view, and edit annotations
- Annotations persist across sessions

**Estimated Duration**: 4–5 weeks

**Dependencies**: Phase C complete, SOP content authored

---

## Phase E: Interior Scans & VR Polish

**Goal**: Scan and integrate interior spaces; refine VR experience.

### Milestones

#### E.1 - Interior Scans
- [ ] Scan, process, and import:
  - Rack container interior (detailed pass with equipment)
  - Workshop container interior
  - Tiny home container interior
  - Greenhouse structure (if built)
- [ ] Create sub-levels for interiors:
  - `Lvl_RackInterior`
  - `Lvl_WorkshopInterior`
  - `Lvl_TinyHomeInterior`
  - `Lvl_Greenhouse`
- [ ] Implement level streaming or manual loading for interiors
- [ ] Test transitions (exterior → interior)

#### E.2 - VR Quality of Life
- [ ] Refine VR locomotion:
  - Smooth teleport arc
  - Comfort settings (vignette, snap turning)
  - Speed adjustments
- [ ] Improve VR UI:
  - Laser pointer visual feedback
  - 3D widget placement (avoid HUD clipping)
  - Readable text at distance
- [ ] Optimize performance for VR (90 Hz minimum):
  - LOD settings on scanned meshes
  - Occlusion culling
  - Light baking or dynamic GI tuning

#### E.3 - Desktop Enhancements
- [ ] Add free-fly camera mode (god mode for overview/screenshots)
- [ ] Improve desktop HUD:
  - Minimap or overhead view option
  - Quick phase switcher hotkeys
- [ ] Screenshot/video capture helpers

**Success Criteria:**
- All primary interior spaces scanned and navigable
- VR experience smooth and comfortable (no nausea triggers)
- Level streaming works correctly
- Can capture high-quality screenshots/videos for documentation

**Estimated Duration**: 4–5 weeks

**Dependencies**: Phase D complete, interior spaces physically accessible for scanning

---

## Phase F: Telemetry & Scenario Simulation

**Goal**: Integrate live data visualization; add scenario planning tools.

### Milestones

#### F.1 - Telemetry Framework
- [ ] Implement `US_TelemetryManager` subsystem:
  - Config: endpoint URLs (REST) or MQTT topics
  - Polling logic (1–5 second intervals)
  - Data caching and refresh
  - Mock/dummy data mode for testing
- [ ] Implement `U_TelemetryComponent`:
  - Attach to actors (rack, PV array, batteries, NetBotz, doors)
  - Config: telemetry keys, display mode (text, color, graph)
  - Update loop: fetch data from manager, update visual
- [ ] Define telemetry endpoints (see `docs/telemetry/telemetry_endpoints.md`):
  - NetBotz: temperature, humidity
  - PV/Battery: SOC, voltage, current, production
  - Doors: open/closed state
  - Security: motion sensor triggers

#### F.2 - Telemetry Visualization
- [ ] Create telemetry display widgets:
  - `WID_TelemetryText`: floating text above object
  - `WID_TelemetryGraph`: simple time-series graph (when focused)
  - Color-coding: green/yellow/red based on thresholds
- [ ] Create `WID_TelemetryOverlay`:
  - Global telemetry dashboard (optional panel)
  - Show all telemetry sources at a glance
- [ ] Integrate with object interaction:
  - Click object → show detailed telemetry
- [ ] Test with dummy data, then integrate with real endpoints

#### F.3 - Scenario Simulation
- [ ] Implement `US_ScenarioManager` subsystem:
  - Define scenarios (data-driven or hardcoded)
  - Trigger scenario effects on actors
  - Reset to normal state
- [ ] Create scenario definitions:
  - **Power Failure**: Dim/disable lights, show offline state on non-critical loads
  - **Intrusion at North Perimeter**: Highlight LRAD coverage cone, camera FOVs, strobe positions
  - **Fire in Rack Container**: Highlight fire extinguisher locations, egress routes
- [ ] Create `WID_ScenarioPanel`:
  - List available scenarios
  - "Activate" / "Reset" buttons
  - Scenario description and objectives
- [ ] Implement visual effects:
  - Coverage cones for LRAD/cameras
  - Pathing/arrows for egress
  - Color overlays for affected zones

**Success Criteria:**
- Telemetry data (dummy or real) displays on relevant objects
- At least 3 scenarios implemented and testable
- Scenario panel functional in desktop and VR
- Visual effects clear and useful for planning

**Estimated Duration**: 5–6 weeks

**Dependencies**: Phase E complete, telemetry endpoints documented and accessible, scenario planning requirements defined

---

## Phase G: Polish, Documentation, & Deployment

**Goal**: Production-ready application with comprehensive documentation.

### Milestones

#### G.1 - Performance Optimization
- [ ] Profile and optimize:
  - Scanned mesh polycount and LODs
  - Material complexity
  - Lighting (baked vs. dynamic)
  - Level streaming and occlusion
- [ ] Target performance:
  - Desktop: 60+ FPS at 1440p
  - VR: 90 Hz minimum
- [ ] Test on target hardware (homestead workstation + VR headset)

#### G.2 - Content Completion
- [ ] Scan remaining structures and areas:
  - Any additional containers or zones
  - Updated scans for modified areas
- [ ] Finalize all phase data (P0–P5):
  - Verify phase-specific geometry and metadata
  - Ensure phase transitions are smooth
- [ ] Create all planned SOPs (estimate: 10–20 SOPs)
- [ ] Author annotations for key systems and decision points

#### G.3 - User Documentation
- [ ] Write user guide (`docs/user_guide.md`):
  - How to navigate (desktop and VR)
  - How to interact with objects
  - How to view SOPs and telemetry
  - How to use phase selector
  - How to create annotations
- [ ] Write operator manual for SOPs (`docs/sop_manual.md`):
  - Index of all SOPs
  - Detailed procedures for critical operations
- [ ] Create video tutorial (optional):
  - Walkthrough of core features
  - Example planning scenarios

#### G.4 - Developer Documentation
- [ ] Update design documents:
  - `docs/design/homestead_twin_design.md` (detailed architecture)
  - `docs/design/coordinate_system.md` (updated with any changes)
  - `docs/design/phase_plan.md` (finalize P0–P5 definitions)
- [ ] Document asset pipeline:
  - `docs/scanners/workflow_raw_to_processed.md` (complete workflow)
  - `docs/scanners/hardware_evaluation.md` (final scanner selection)
- [ ] Document telemetry integration:
  - `docs/telemetry/telemetry_endpoints.md` (all endpoints and data formats)
- [ ] Create contributor guide (`CONTRIBUTING.md`) (if applicable)

#### G.5 - Packaging & Deployment
- [ ] Package UE project for Windows:
  - Standalone executable
  - Installer (optional)
- [ ] Test packaged build on clean machine
- [ ] Set up backup and version control:
  - Tag release version in git
  - Backup raw scan data
  - Archive project snapshots

**Success Criteria:**
- Application runs smoothly on target hardware
- All planned content and features complete
- Comprehensive documentation available
- Packaged build tested and deployable

**Estimated Duration**: 4–6 weeks

**Dependencies**: Phases A–F complete

---

## Post-Launch: Iteration & Expansion

**Ongoing Goals**: Maintain and expand the Homestead Twin as the physical homestead evolves.

### Potential Future Features

#### Advanced Telemetry
- Historical data graphs and trend analysis
- Alerting and notification overlays
- Predictive modeling (e.g., battery runtime estimation)

#### Training Simulations
- Interactive SOP walkthroughs with validation
- Timed drills and performance scoring
- Scenario variations and randomization

#### Design Tools
- In-world CAD object placement preview
- Sun/shadow analysis per hour/season
- Water flow simulation for swales and ponds
- Orchard layout and spacing calculator

#### Integration Expansions
- Export data to external tools (Notion, spreadsheets)
- Import data from external sources (weather, satellite imagery)
- Integration with Blender for advanced modeling/texturing

#### Multi-User Collaboration (Scope Change)
- If needed in the future: networked sessions for remote walkthroughs
- Annotation sharing across users

---

## Success Metrics

**By Phase G Completion:**
- [ ] 100% of homestead containers scanned and integrated
- [ ] 10+ SOPs authored and linked to objects
- [ ] Phase system (P0–P5) fully functional with documented geometry per phase
- [ ] VR and desktop navigation smooth and comfortable
- [ ] At least 3 telemetry data sources visualized (real or simulated)
- [ ] At least 3 scenario simulations implemented
- [ ] Comprehensive documentation complete
- [ ] Packaged application deployable and tested

**Ongoing:**
- Application updated as homestead evolves (new scans, new SOPs)
- Telemetry endpoints expanded as systems come online
- Scenarios refined based on real-world operational experience

---

## Risk Management

| Risk | Likelihood | Impact | Mitigation |
|------|------------|--------|------------|
| Scanner hardware failure or inadequate quality | Medium | High | Evaluate multiple scanner options, have backup workflow with photogrammetry |
| UE5 version breaking changes | Low | Medium | Pin to specific UE5 version (e.g., 5.3.x), test upgrades in separate branch |
| Performance issues with large scanned meshes | Medium | High | Implement aggressive decimation and LOD strategies, use Nanite where appropriate |
| VR nausea/discomfort | Medium | Medium | Follow VR best practices, implement comfort settings, test with multiple users |
| Telemetry endpoint unavailability | Low | Low | Design for offline fallback, use mock data during development |
| Scope creep | High | Medium | Maintain strict phase boundaries, defer "nice-to-have" features to post-launch |
| Single maintainer burnout | Medium | High | Maintain realistic timelines, prioritize ruthlessly, accept "good enough" over perfection |

---

## Timeline Summary

| Phase | Estimated Duration | Cumulative |
|-------|-------------------|------------|
| Phase A: Bootstrap & Foundation | 1–2 weeks | 1–2 weeks |
| Phase B: Greybox Homestead & Phase System | 2–3 weeks | 3–5 weeks |
| Phase C: First Scans & Asset Pipeline | 3–4 weeks | 6–9 weeks |
| Phase D: Interaction & Object System | 4–5 weeks | 10–14 weeks |
| Phase E: Interior Scans & VR Polish | 4–5 weeks | 14–19 weeks |
| Phase F: Telemetry & Scenario Simulation | 5–6 weeks | 19–25 weeks |
| Phase G: Polish, Documentation, & Deployment | 4–6 weeks | 23–31 weeks |

**Total Estimated Timeline**: 23–31 weeks (approximately 6–8 months)

**Note**: Timelines assume part-time development (10–20 hours/week). Adjust accordingly for different time commitments.

---

## Conclusion

This roadmap provides a structured, phased approach to building the Homestead Twin digital twin application. Each phase builds on the previous, with clear milestones, success criteria, and dependencies. The focus is on pragmatic, iterative development that delivers value early and often, while remaining flexible to adapt as the physical homestead and requirements evolve.

**Next Steps:**
1. Review and refine this roadmap with stakeholders (if any)
2. Begin Phase A: Bootstrap & Foundation
3. Establish regular check-ins to assess progress and adjust timeline as needed
4. Document lessons learned and update this roadmap as the project progresses
