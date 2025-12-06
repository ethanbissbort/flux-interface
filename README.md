# Homestead Twin

**Digital Twin for Fluxology Homestead**

A single-user Unreal Engine 5.7 application providing a spatially accurate 3D/VR environment for operations planning, training, and telemetry visualization of the Fluxology Homestead infrastructure.

[![UE Version](https://img.shields.io/badge/Unreal%20Engine-5.7-informational)](https://www.unrealengine.com/)
[![Platform](https://img.shields.io/badge/Platform-Windows-blue)](https://www.microsoft.com/windows)
[![Development Phase](https://img.shields.io/badge/Phase-A%20(30%25)-yellow)](ROADMAP.md)
[![Build Status](https://img.shields.io/badge/Build-⚠%20Errors-red)](#current-build-status)

---

## 📋 Table of Contents

- [Overview](#overview)
- [Current Status](#current-status)
- [Features](#features)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
- [Development](#development)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)

---

## 🎯 Overview

The **Homestead Twin** is a practical planning and operations tool (not a game) for a private, off-grid technology homestead. It provides:

- **Spatially accurate 1:1 3D environment** using real-world 3D scans
- **VR and desktop navigation** for immersive inspection and planning
- **Standard Operating Procedures (SOPs)** linked to physical objects
- **Phase-based visualization** (P0–P5) tracking build-out progress
- **Future telemetry integration** for live monitoring of power, environment, and security systems
- **Scenario simulation** for training and response planning

**Design Principles:**
- Accuracy over aesthetics
- Utility over polish
- Air-gap capable (no hard internet dependency)
- Single maintainer optimized
- Iterative development: greybox → scans → refinement → telemetry

---

## 📊 Current Status

**Last Updated**: 2025-12-06

| Aspect | Status |
|--------|--------|
| **Development Phase** | Phase A: Bootstrap & Foundation (~30% complete) |
| **UE Version** | 5.7 |
| **C++ Framework** | ~70% complete (scaffolded, many TODOs) |
| **Content/Blueprints** | 0% (not started) |
| **Build Status** | ⚠️ Compilation error (forward declaration issue) |
| **Runnable** | ❌ No (no maps, blueprints, or content) |

### What's Implemented (C++)

✅ **Working:**
- Desktop pawn movement (WASD, sprint, slow walk, camera control)
- Phase switching logic
- SOP query system
- Annotation CRUD operations
- Mock telemetry data generation
- Scenario activation framework
- Base object/component architecture

🟡 **Partial (Stubs/TODOs):**
- VR systems (structure only, all functionality TODO)
- Enhanced Input bindings (using legacy input)
- Data loading from Data Tables
- JSON serialization for annotations
- Level streaming and phase visibility

❌ **Not Started:**
- Content folder structure
- Blueprint classes
- UI widgets (UMG)
- Maps and levels
- 3D scans and assets

### Current Build Status

**⚠️ BUILD BROKEN** — Compilation error in `U_SOPComponent.cpp`:
```
error: 'FStandardOperatingProcedure' undefined
```

**Fix Required**: Add proper include for `US_SOPManager.h` in header file.

---

## ✨ Features

### Planned Features (by Phase)

- **Phase A** (current): Basic desktop navigation, test map
- **Phase B**: Greybox homestead layout, phase system UI
- **Phase C**: First 3D scans integrated, asset pipeline established
- **Phase D**: Object interaction, SOP viewer, annotations
- **Phase E**: Interior scans, VR locomotion, VR polish
- **Phase F**: Live telemetry visualization, scenario simulations
- **Phase G**: Performance optimization, packaging, deployment

See [ROADMAP.md](ROADMAP.md) for detailed phase breakdown.

---

## 📁 Repository Structure

```
flux-interface/
├── homestead_twin/             # Unreal Engine 5.7 project
│   └── Project/
│       ├── HomesteadTwin.uproject
│       ├── Source/             # C++ code
│       │   └── HomesteadTwin/
│       │       ├── Core/       # GameInstance, GameMode, Pawns, Controllers
│       │       ├── Subsystems/ # PhaseManager, SOPManager, TelemetryManager, etc.
│       │       ├── Components/ # InteractableComponent, SOPComponent, etc.
│       │       └── Actors/     # HomesteadObject, Annotation
│       ├── Content/            # ⚠️ NOT YET CREATED (Blueprints, Maps, UI)
│       ├── Plugins/            # VisualStudioTools
│       └── build-logs/         # Build output logs
├── data/                       # NOT IN GIT (large files)
│   ├── scans/                  # 3D scan data
│   │   ├── raw/                # Raw scan captures (gitignored)
│   │   └── processed/          # Processed meshes for UE/CAD
│   ├── tables/                 # Example CSV data tables (SOPs, phases)
│   ├── textures/               # Optional texture overlays
│   └── exports/                # Screenshots, videos, documentation
├── docs/                       # Design and operational documentation
│   ├── design/                 # Architecture, coordinate system, phase plans
│   ├── procedures/             # SOP structure and definitions
│   ├── scanners/               # 3D scanner workflows and hardware evaluation
│   ├── telemetry/              # Telemetry endpoint specs (future)
│   ├── implementation/         # Phase-specific implementation guides
│   └── ue_content/             # Content folder structure, UI widget reference
├── tools/                      # Helper scripts (future: Blender automation, mesh processing)
├── ROADMAP.md                  # Phased development plan (Phases A–G)
├── README.md                   # This file (quick start and overview)
├── claude.md                   # AI assistant context primer
└── .gitignore                  # Excludes large binaries, scans, UE temp files
```

---

## 🚀 Getting Started

### Prerequisites

- **Unreal Engine 5.7** ([Download](https://www.unrealengine.com/download))
- **Visual Studio 2022** (with C++ game development workload)
- **Windows 10/11** (64-bit)
- **Git** for version control
- *(Optional)* VR headset for VR development (deferred to Phase E)

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/ethanbissbort/flux-interface.git
   cd flux-interface
   ```

2. **Fix the current build error** (required):

   The project currently has a compilation error. See [Current Build Status](#current-build-status) for details.

3. **Generate Visual Studio project files:**

   Right-click `homestead_twin/Project/HomesteadTwin.uproject` → **Generate Visual Studio project files**

4. **Open the solution:**
   ```bash
   # Open in Visual Studio
   start homestead_twin/Project/HomesteadTwin.sln
   ```

5. **Build the project:**

   In Visual Studio: **Build → Build Solution** (Ctrl+Shift+B)

6. **Open in Unreal Editor:**

   Double-click `homestead_twin/Project/HomesteadTwin.uproject`

### ⚠️ Known Issues

**The project will NOT currently run** because:
1. ❌ Build error (FStandardOperatingProcedure forward declaration)
2. ❌ No Content folder (no maps, blueprints, or UI)
3. ❌ No test map to load

**Next Steps to Get a Runnable Build:**
1. Fix compilation error
2. Create `Content/` folder structure
3. Create `Map_Homestead_Main` test map
4. Create Blueprint classes derived from C++ base classes
5. Create minimal desktop HUD widget
6. Configure Enhanced Input assets

See [docs/implementation/phase_a_checklist.md](docs/implementation/phase_a_checklist.md) for detailed guidance.

---

## 🛠️ Development

### Quick Reference

- **Coordinate System**: Origin at rack container SW corner, X=East, Y=North, Z=Up (1 UE unit = 1 cm)
- **Phases**: P0–P5 (homestead build-out phases)
- **Primary Documentation**: [claude.md](claude.md) (comprehensive context for AI assistants)
- **Development Roadmap**: [ROADMAP.md](ROADMAP.md)

### Building the Project

```bash
# From repository root
cd homestead_twin/Project

# Clean build (if needed)
# Delete Binaries/, Intermediate/, Saved/ folders, then regenerate project files

# Build from command line (optional)
"C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\Build.bat" HomesteadTwinEditor Win64 Development "C:\path\to\HomesteadTwin.uproject"
```

### Running Tests

*(Tests not yet implemented)*

### Code Style

- Follow Unreal Engine C++ coding standards
- Prefix classes: `GI_` (GameInstance), `GM_` (GameMode), `PC_` (PlayerController), `A_` (Actor), `U_` (Component/Object), `US_` (Subsystem)
- Prefix widgets: `WID_`
- Use TODO comments for known incomplete implementations

---

## 📚 Documentation

### Key Documentation Files

| File | Purpose |
|------|---------|
| [claude.md](claude.md) | Comprehensive context for AI assistants (architecture, workflows, patterns) |
| [ROADMAP.md](ROADMAP.md) | Phased development plan (Phases A–G, timeline, milestones) |
| [docs/design/homestead_twin_design.md](docs/design/homestead_twin_design.md) | High-level architecture |
| [docs/design/coordinate_system.md](docs/design/coordinate_system.md) | Spatial coordinate system definition |
| [docs/design/phase_plan.md](docs/design/phase_plan.md) | Phase breakdown (P0–P5) |
| [docs/procedures/sop_structure.md](docs/procedures/sop_structure.md) | Standard Operating Procedure data structure |
| [docs/implementation/phase_a_checklist.md](docs/implementation/phase_a_checklist.md) | Phase A implementation guide |

### External Resources

- [Unreal Engine 5.7 Documentation](https://docs.unrealengine.com/5.7/)
- [VR Best Practices](https://docs.unrealengine.com/5.7/en-US/VirtualReality/)
- [Enhanced Input](https://docs.unrealengine.com/5.7/en-US/enhanced-input-in-unreal-engine/)

---

## 🤝 Contributing

This is primarily a single-maintainer project for internal Fluxology use. External contributions are not currently accepted.

For questions or clarifications, see [claude.md](claude.md) for project context.

---

## 📜 License

Copyright © Fluxology. All Rights Reserved.

This is a private project. Unauthorized copying, distribution, or use is prohibited.

---

## 🔗 Additional Information

### Phase System (P0–P5)

The homestead is built in phases. The application visualizes these to show planned vs. current vs. future state:

| Phase | Description |
|-------|-------------|
| **P0** | Minimal containers + basic power/data |
| **P1** | Workshop container, initial rack population |
| **P2** | Tiny-home container, basic orchard layout |
| **P3** | Greenhouse, expanded orchard, ponds/swales |
| **P4** | Extended perimeter and deterrence systems |
| **P5** | Full build-out (Aircela, auxiliary infrastructure) |

### 3D Scanning Pipeline

Future phases will integrate 3D scans from prosumer handheld scanners (Einstar/Miraco class) for spatially accurate geometry.

Workflow: Physical object → 3D scan → Clean/decimate → Export FBX/OBJ → Import to UE → Place in world

See [docs/scanners/workflow_raw_to_processed.md](docs/scanners/workflow_raw_to_processed.md) for details.

### Telemetry Integration (Future)

Phase F will integrate live telemetry from:
- NetBotz (temperature, humidity)
- PV/Battery systems (SOC, voltage, current, production)
- Security sensors (motion, door state, deterrent systems)

Designed for offline fallback — app works without telemetry.

---

**For comprehensive project context, read [claude.md](claude.md) before starting development.**
