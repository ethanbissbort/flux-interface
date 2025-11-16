# UE Content Folder Structure

This document defines the organization of the Unreal Engine Content folder for the Homestead Twin project.

**Location**: `homestead_twin/Project/Content/`

---

## Directory Structure

```
Content/
├── Blueprints/
│   ├── Core/
│   │   ├── BP_GI_HomesteadTwin.uasset
│   │   ├── BP_GM_HomesteadTwin.uasset
│   │   ├── BP_PC_Desktop.uasset
│   │   ├── BP_PC_VR.uasset
│   │   ├── BP_Pawn_Desktop.uasset
│   │   └── BP_Pawn_VR.uasset
│   ├── Subsystems/
│   │   ├── BP_US_HomesteadPhaseManager.uasset
│   │   ├── BP_US_SOPManager.uasset
│   │   ├── BP_US_AnnotationManager.uasset
│   │   ├── BP_US_TelemetryManager.uasset (future)
│   │   └── BP_US_ScenarioManager.uasset (future)
│   ├── Actors/
│   │   ├── BP_HomesteadObject.uasset
│   │   ├── BP_Annotation.uasset
│   │   ├── Objects/
│   │   │   ├── BP_RackContainer.uasset
│   │   │   ├── BP_WorkshopContainer.uasset
│   │   │   ├── BP_TinyHomeContainer.uasset
│   │   │   ├── BP_Greenhouse.uasset
│   │   │   ├── BP_RackUnit.uasset
│   │   │   ├── BP_Generator.uasset
│   │   │   ├── BP_SolarPanel.uasset
│   │   │   └── BP_PerimeterSensor.uasset
│   │   └── Helpers/
│   │       ├── BP_PlayerSpawn.uasset
│   │       └── BP_LightingRig.uasset
│   └── Components/
│       ├── BP_InteractableComponent.uasset
│       ├── BP_SOPComponent.uasset
│       └── BP_TelemetryComponent.uasset (future)
├── UI/
│   ├── Widgets/
│   │   ├── Core/
│   │   │   ├── WID_HUD_Minimal.uasset
│   │   │   └── WID_HUD_VR.uasset
│   │   ├── Phase/
│   │   │   └── WID_PhaseSelector.uasset
│   │   ├── Interaction/
│   │   │   ├── WID_ObjectInfoPanel.uasset
│   │   │   └── WID_SOPViewer.uasset
│   │   ├── Annotation/
│   │   │   ├── WID_AnnotationEditor.uasset
│   │   │   └── WID_AnnotationDisplay.uasset
│   │   ├── Telemetry/ (future)
│   │   │   ├── WID_TelemetryText.uasset
│   │   │   ├── WID_TelemetryGraph.uasset
│   │   │   └── WID_TelemetryOverlay.uasset
│   │   └── Scenario/ (future)
│   │       └── WID_ScenarioPanel.uasset
│   ├── Materials/
│   │   ├── M_UI_Base.uasset
│   │   ├── M_UI_Button.uasset
│   │   └── M_UI_Panel.uasset
│   └── Textures/
│       ├── Icons/
│       │   ├── T_Icon_Rack.uasset
│       │   ├── T_Icon_Container.uasset
│       │   ├── T_Icon_Power.uasset
│       │   └── T_Icon_Security.uasset
│       └── UI_Elements/
│           ├── T_Crosshair.uasset
│           ├── T_LaserPointer.uasset
│           └── T_ButtonBG.uasset
├── Materials/
│   ├── Base/
│   │   ├── M_Master_Opaque.uasset
│   │   ├── M_Master_Transparent.uasset
│   │   └── M_Master_Emissive.uasset
│   ├── Scanned/
│   │   ├── M_ScannedMesh_Generic.uasset
│   │   ├── M_ScannedMesh_Metal.uasset
│   │   └── M_ScannedMesh_Concrete.uasset
│   ├── Environment/
│   │   ├── M_Terrain.uasset
│   │   ├── M_Grass.uasset
│   │   └── M_Gravel.uasset
│   ├── Debug/
│   │   ├── M_Debug_Red.uasset
│   │   ├── M_Debug_Green.uasset
│   │   ├── M_Debug_Blue.uasset
│   │   └── M_Debug_Wireframe.uasset
│   └── Telemetry/ (future)
│       ├── M_Telemetry_Green.uasset
│       ├── M_Telemetry_Yellow.uasset
│       └── M_Telemetry_Red.uasset
├── Textures/
│   ├── Scanned/
│   │   └── (albedo/normal/roughness maps from photogrammetry)
│   ├── Environment/
│   │   └── (terrain, grass, gravel textures)
│   └── Debug/
│       └── T_GridLines.uasset
├── Scans/
│   ├── Environment/
│   │   ├── SM_Terrain_Site_v1.uasset
│   │   ├── SM_Terrain_Site_v2.uasset
│   │   └── SM_GroundPatch_v1.uasset
│   ├── Containers/
│   │   ├── SM_RackContainer_Exterior_v1.uasset
│   │   ├── SM_RackContainer_Exterior_v2.uasset
│   │   ├── SM_WorkshopContainer_Exterior_v1.uasset
│   │   ├── SM_TinyHomeContainer_Exterior_v1.uasset
│   │   └── SM_Greenhouse_Exterior_v1.uasset
│   ├── Rack/
│   │   ├── SM_RackInterior_v1.uasset
│   │   ├── SM_RackInterior_v2.uasset
│   │   ├── SM_RackUnit_42U_v1.uasset
│   │   └── SM_RackMount_v1.uasset
│   ├── Workshop/
│   │   ├── SM_WorkshopInterior_v1.uasset
│   │   └── SM_Workbench_v1.uasset
│   ├── TinyHome/
│   │   └── SM_TinyHomeInterior_v1.uasset
│   └── Greenhouse/
│       └── SM_GreenhouseInterior_v1.uasset
├── Models/
│   ├── Greybox/
│   │   ├── SM_Greybox_Container_20ft.uasset
│   │   ├── SM_Greybox_Container_40ft.uasset
│   │   ├── SM_Greybox_Cube_1m.uasset
│   │   ├── SM_Greybox_Cylinder_1m.uasset
│   │   └── SM_Greybox_Plane_10m.uasset
│   ├── Primitives/
│   │   ├── SM_Rack_42U_Placeholder.uasset
│   │   ├── SM_SolarPanel_Placeholder.uasset
│   │   └── SM_Battery_Placeholder.uasset
│   └── Helpers/
│       ├── SM_PlayerSpawn_Marker.uasset
│       └── SM_Annotation_Billboard.uasset
├── Maps/
│   ├── Main/
│   │   ├── Map_Homestead_Main.umap (persistent level)
│   │   └── Map_Homestead_Main_BuiltData.uasset
│   ├── Sublevels/
│   │   ├── Lvl_Containers.umap
│   │   ├── Lvl_RackInterior.umap
│   │   ├── Lvl_WorkshopInterior.umap
│   │   ├── Lvl_TinyHomeInterior.umap
│   │   ├── Lvl_Greenhouse.umap
│   │   ├── Lvl_OrchardAndSwales.umap
│   │   └── Lvl_SecurityAndPerimeter.umap
│   ├── Test/
│   │   ├── Map_Test_Greybox.umap
│   │   ├── Map_Test_VR.umap
│   │   └── Map_Test_Interaction.umap
│   └── Lighting/
│       └── Map_Lighting_Sandbox.umap
├── Data/
│   ├── Tables/
│   │   ├── DT_PhaseDefinitions.uasset
│   │   ├── DT_SOPs.uasset
│   │   ├── DT_ScenarioDefinitions.uasset (future)
│   │   └── DT_TelemetryEndpoints.uasset (future)
│   └── Config/
│       ├── DA_GameSettings.uasset
│       └── DA_VRSettings.uasset
├── Audio/
│   ├── SFX/
│   │   ├── UI/
│   │   │   ├── SFX_UI_Click.uasset
│   │   │   ├── SFX_UI_Hover.uasset
│   │   │   └── SFX_UI_Notification.uasset
│   │   ├── Interaction/
│   │   │   ├── SFX_Interact.uasset
│   │   │   └── SFX_Teleport.uasset
│   │   └── Alerts/
│   │       ├── SFX_Alert_Warning.uasset
│   │       └── SFX_Alert_Critical.uasset
│   ├── Music/
│   │   └── (optional ambient music)
│   └── Cues/
│       ├── SC_UI_Click.uasset
│       └── SC_Alert_Warning.uasset
├── VFX/
│   ├── Teleport/
│   │   ├── P_TeleportArc.uasset
│   │   └── P_TeleportMarker.uasset
│   ├── Interaction/
│   │   ├── P_InteractionHighlight.uasset
│   │   └── P_LaserPointer.uasset
│   └── Scenario/ (future)
│       ├── P_CoverageCone.uasset
│       └── P_Alert_Overlay.uasset
└── Input/
    ├── IM_Desktop.uasset (Input Mapping Context for desktop)
    ├── IM_VR.uasset (Input Mapping Context for VR)
    ├── IA_Move.uasset (Input Action)
    ├── IA_Look.uasset (Input Action)
    ├── IA_Interact.uasset (Input Action)
    └── IA_PhaseSelector.uasset (Input Action)
```

---

## Naming Conventions

### Prefixes

Follow Unreal Engine standard prefixes:

| Asset Type | Prefix | Example |
|------------|--------|---------|
| Blueprint (Actor) | BP_ | BP_HomesteadObject |
| Blueprint (Component) | BP_ | BP_InteractableComponent |
| Widget Blueprint | WID_ | WID_HUD_Minimal |
| Static Mesh | SM_ | SM_RackContainer_v1 |
| Skeletal Mesh | SK_ | SK_HandMesh |
| Material | M_ | M_Master_Opaque |
| Material Instance | MI_ | MI_Container_Metal |
| Texture | T_ | T_Icon_Rack |
| Data Table | DT_ | DT_SOPs |
| Data Asset | DA_ | DA_GameSettings |
| Sound Cue | SC_ | SC_UI_Click |
| Sound Wave | SFX_ or MUS_ | SFX_UI_Click, MUS_Ambient |
| Particle System (Niagara) | P_ | P_TeleportArc |
| Level/Map | Map_ or Lvl_ | Map_Homestead_Main, Lvl_Containers |
| Input Action | IA_ | IA_Interact |
| Input Mapping Context | IM_ | IM_Desktop |

### Naming Patterns

**Scanned Meshes**:
- Pattern: `SM_<Area>_<Detail>_v<N>`
- Examples:
  - `SM_RackContainer_Exterior_v2`
  - `SM_Terrain_Site_v1`
  - `SM_RackInterior_v3`

**Versioning**:
- Use `_v1`, `_v2`, `_vN` suffix for asset iterations
- Keep previous versions for rollback capability
- Document version changes in asset metadata

**Greybox/Placeholder**:
- Include `_Greybox` or `_Placeholder` in name
- Examples:
  - `SM_Greybox_Container_20ft`
  - `SM_Rack_42U_Placeholder`

**Data Tables**:
- Pattern: `DT_<DataType>`
- Examples:
  - `DT_PhaseDefinitions`
  - `DT_SOPs`

---

## Folder Organization Guidelines

### General Principles

1. **Group by function, not by type**: Organize by feature area (Blueprints/Actors, UI/Widgets) rather than dumping all materials in one folder
2. **Shallow hierarchies**: Avoid deep nesting (max 3-4 levels)
3. **Consistent naming**: Follow naming conventions strictly
4. **Version control**: Use suffixes (_v1, _v2) for iterations
5. **Separation of concerns**: Scanned assets separate from hand-modeled assets

### Specific Folder Rules

**Blueprints/**
- Core framework classes in `Core/`
- Subsystems in `Subsystems/`
- Specific object types in `Actors/Objects/`
- Helper/utility actors in `Actors/Helpers/`
- Components in `Components/`

**UI/**
- All UI-related assets
- Widgets organized by feature area
- UI materials/textures separate from 3D materials

**Scans/**
- **ONLY** imported 3D scan meshes
- Organized by scan area (Environment, Containers, Rack, etc.)
- Version suffixes mandatory
- Related textures/materials can be in same folder or in `Materials/Scanned/`

**Materials/**
- Master materials in `Base/`
- Material instances organized by usage
- Debug materials separate
- Telemetry/scenario-specific materials in own folders

**Maps/**
- Main persistent level in `Main/`
- Sublevels in `Sublevels/`
- Test maps in `Test/`
- Lighting experiments in `Lighting/`

**Data/**
- Data Tables in `Tables/`
- Data Assets in `Config/`
- No mixed types

---

## Asset Import Rules

### 3D Scanned Meshes

**Source**: `data/scans/processed/for_ue5/`

**Import Settings**:
- **Import Mesh**: Enabled
- **Skeletal Mesh**: Disabled (static meshes only)
- **Import Materials**: Enabled (if available)
- **Import Textures**: Enabled (if available)
- **Transform**:
  - Import Translation: 0,0,0
  - Import Rotation: 0,0,0
  - Import Uniform Scale: 1.0 (verify 1 UE unit = 1 cm)
- **Mesh**:
  - Auto Generate Collision: Enabled (but verify/optimize)
  - Combine Meshes: Depends on scan (usually disabled)
  - Generate Lightmap UVs: Enabled
- **Material**:
  - Search Location: All Assets (or specify)
  - Material Import Method: Create New Materials

**Post-Import**:
1. Verify scale (measure known dimension)
2. Check collision mesh (simplify if needed)
3. Verify lightmap UVs (no overlaps)
4. Apply appropriate material (generic scanned mesh material)
5. Test in map at origin (0,0,0) for alignment

**Destination**: `Content/Scans/<Area>/`

### Hand-Modeled Meshes

**Source**: External modeling software (Blender, etc.)

**Destination**: `Content/Models/Primitives/` or `Content/Models/Greybox/`

**Import Settings**: Similar to scanned meshes, verify scale

### Materials

**Source**: Exported from modeling software or created in UE

**Destination**: `Content/Materials/<Category>/`

**Workflow**:
1. Create Master Material first
2. Create Material Instances for variations
3. Use Material Functions for reusable logic

### Textures

**Source**: `data/textures/` or scanned data

**Destination**: `Content/Textures/<Category>/`

**Import Settings**:
- **Compression**: Default (DXT) or BC7 for high quality
- **sRGB**: Enabled for color/albedo, disabled for data maps (normal, roughness)
- **Mip Gen Settings**: FromTextureGroup (default)

### Data Tables

**Source**: CSV or JSON files

**Workflow**:
1. Create struct in C++ or Blueprint for row type
2. Import CSV/JSON via Data Table editor
3. Save to `Content/Data/Tables/`

**Struct Definitions**:
- `FPhaseDefinition`: See `US_HomesteadPhaseManager.h`
- `FStandardOperatingProcedure`: See `US_SOPManager.h`
- `FScenarioDefinition`: See `US_ScenarioManager.h`

---

## Asset Maintenance

### Version Control

**Git LFS** (Large File Storage) should be used for:
- Static Meshes (.uasset)
- Textures (.uasset)
- Materials (.uasset)
- Maps (.umap)
- Audio (.uasset)

**Standard Git** (text-based) for:
- Blueprints (.uasset) — debatable, but UE uses binary format
- Data Tables (.uasset) — consider exporting to CSV for git

**Best Practices**:
- Commit related assets together
- Use descriptive commit messages
- Tag milestone versions
- Don't commit Intermediate/, Saved/, Binaries/

### Asset Cleanup

**Regular Tasks**:
- Delete unused assets (use Reference Viewer)
- Consolidate duplicate assets
- Fix up redirectors (Right-click → Fix Up Redirectors)
- Validate assets (Right-click → Validate Assets)

**Before Milestone Release**:
- Run asset audit (find unused, missing, duplicates)
- Optimize textures (check mip levels, compression)
- Optimize meshes (check polycount, LODs)
- Verify all references resolve

### Performance Budgets

**Per-Scene Targets**:
- Draw calls: < 2000 (desktop), < 1500 (VR)
- Triangle count: < 2M (desktop), < 1M (VR)
- Texture memory: < 2GB (desktop), < 1.5GB (VR)

**Per-Asset Targets**:
- Scanned mesh: < 100k tris (use LODs)
- UI texture: < 1024x1024 (usually smaller)
- Material complexity: < 100 instructions (shader complexity)

---

## Phase-Specific Asset Roadmap

### Phase A (Bootstrap)
- [ ] Create basic folder structure
- [ ] Import greybox primitives
- [ ] Create minimal HUD widgets
- [ ] Set up test map

### Phase B (Greybox & Phase System)
- [ ] Create all greybox placeholder meshes
- [ ] Create phase data table
- [ ] Implement phase selector widget

### Phase C (First Scans)
- [ ] Import first scanned meshes (terrain, rack exterior, rack interior)
- [ ] Create scanned mesh materials
- [ ] Organize scans by area

### Phase D (Interaction)
- [ ] Create object info and SOP viewer widgets
- [ ] Create annotation actors and widgets
- [ ] Import object-specific icons/textures

### Phase E (Interior Scans)
- [ ] Import all interior scanned meshes
- [ ] Create sublevel maps
- [ ] Optimize scanned meshes (LODs, collision)

### Phase F (Telemetry & Scenarios)
- [ ] Create telemetry widgets and materials
- [ ] Create scenario VFX and materials
- [ ] Create telemetry data tables

---

**Last Updated**: 2025-11-16
**Related Documents**: `claude.md`, `ROADMAP.md`, `ui_widgets_reference.md`
