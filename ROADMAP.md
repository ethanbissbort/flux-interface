Here’s a first-pass design document for the UE 5.x Digital Homestead Twin app, built specifically around your homestead, tech stack, and scanner pipeline.

I’m writing this as if it’s going into a repo or Notion page.

Digital Homestead Twin – UE 5.x Design Document
1. Purpose & Goals

Working title: Homestead Twin

1.1 Primary Goal

A single-user Unreal Engine 5.x application that acts as:

A spatially accurate digital twin of your homestead (land, containers, infrastructure).

A training and planning environment for operations (power, IT, deterrence, workflows).

A visual front-end for scanned geometry (3D scanner pipeline) and, later, live telemetry (NetBotz, PV, batteries, Aircela, etc.).

1.2 Non-goals

No multiplayer / co-op.

Not a “game” with win conditions; this is a tool with some sim flavor.

No hard dependency on online services; assume air-gapped usability.

2. Target Platforms & Dependencies
2.1 Platform

Primary: Windows PC (your existing workstation / homestead server).

Input modes:

Desktop: keyboard + mouse.

VR: PCVR (SteamVR-compatible headset).

Single-player only.

2.2 Engine & Versions

Unreal Engine 5.x (Nanite + Lumen capable, but we’ll start conservative and enable as needed).

Project set up for:

C++ optional but not required initially; core logic via Blueprints.

Target DirectX 12 for Lumen/Nanite, with fallback profile if needed.

2.3 External Dependencies

3D scanner software (vendor-specific) – not embedded; outputs files we ingest.

Optional future telemetry endpoints:

Local HTTP REST APIs

MQTT broker (OPNsense/VMs)

Direct DB queries (if you feel masochistic later)

3. Core Use Cases
3.1 Spatial Planning & Layout

Walk through homestead in first-person / VR:

Validate container placement, orientation, spacing.

Check line-of-sight for deterrence (LRAD/strobes, cameras).

Inspect future orchard, swales, and retention ponds relative to containers and PV.

3.2 Operations Training

Practice standard operating procedures:

Rack power-up / power-down sequence.

Generator + Aircela operation windows.

Response to alerts: intrusion, fire, low water, low battery SOC.

In-app “SOP cards” tied to objects:

Click rack → see sequence.

Click generator pad → start/stop checklist.

3.3 Design & Documentation

Use the twin to:

Annotate where each major system lives (network, power, water, security).

Snapshot “Phase 0” through “Phase 5” to visually document progress.

Export:

Screenshots for manuals / documentation.

Simple flythrough videos.

3.4 Telemetry Visualization (Future Phase)

View live environmental and power data in 3D:

NetBotz temperature/humidity overlays on rack container.

PV production / battery SOC visualized on / near solar array.

Door open/closed, motion sensor hits, etc.

4. World Structure & Coordinate System
4.1 Coordinate System

Unit: 1 Unreal unit = 1 cm (UE default → keep).

Origin (0,0,0):

Chosen as SW external corner of the first container (e.g., rack container) sitting on final-grade ground.

Axes:

X+: East

Y+: North

Z+: Up

Document this in docs/coordinate_system.md.

4.2 World Composition

Use World Partition or simple level streaming (depending on scene size):

One persistent level:

Basic terrain + global lighting + sky.

Sub-levels:

Lvl_Containers

Lvl_RackInterior

Lvl_TinyHomeInterior

Lvl_WorkshopInterior

Lvl_Greenhouse

Lvl_OrchardAndSwales

Lvl_SecurityAndPerimeter

Each sub-level can be streamed in/out for performance or editing sanity.

5. Scanning & Asset Pipeline
5.1 High-level Flow

Physical world (homestead modules, rack, etc.)

3D Scanner (Tier 2 prosumer handheld – e.g., Einstar/Miraco).

Scanner software:

Clean + align + decimate → export FBX/OBJ/STL.

Processing workstation:

Optional further cleanup in MeshLab/Blender.

Output: FBX for UE5, STL/STEP for CAD/printing.

UE5 Content:

Import processed FBX into Content/Scans/....

5.2 File Structure (Host Filesystem)

Base:

/HomesteadTwin
  /docs
  /ue5
  /scans
  /cad_print
  /textures
  /exports
  /backups


Key parts:

/scans/raw
  /site
  /containers
  /rack
  /workshop
  /tiny_home
  /greenhouse

/scans/processed/for_ue5
  /site
  /containers
  /rack
  /tiny_home
  /workshop

/scans/processed/for_cad
  /mounts
  /fixtures


Naming convention:

Raw capture folder: YYYY-MM-DD_area_detail_vN/

Processed mesh for UE:
area_detail_1to1_vN.fbx
e.g., rack_container_interior_1to1_v3.fbx

5.3 Asset Import Rules (UE)

All imported scans go under:

Content/Scans/Environment
Content/Scans/Containers
Content/Scans/Rack
Content/Scans/Workshop
...


Each mesh is scaled to 1:1 (cm); verify on import.

Materials:

Start with simple, generic materials (no photoreal fuss early).

Later phases: optional custom materials/textures per asset.

5.4 Update Strategy

New scan version → increment vN and:

Update UE asset reference.

Log change in docs/changelog.md.

6. UE5 Architecture
6.1 High-level Modules

Core Framework

GameInstance subclass: GI_HomesteadTwin

Base GameMode: GM_HomesteadTwin

PlayerControllers:

PC_Desktop

PC_VR

Subsystems

US_HomesteadPhaseManager

US_TelemetryManager (future)

US_SOPManager (standard operating procedures)

US_AnnotationManager

Actors/Components

A_HomesteadObject (base class for physical things with metadata)

U_InteractableComponent

U_SOPComponent

U_TelemetryComponent (future)

UI

WID_HUD_Minimal (desktop)

WID_HUD_VR (VR)

WID_ObjectInfoPanel

WID_PhaseSelector

WID_SOPViewer

WID_TelemetryOverlay (future)

6.2 Object Representation

Base actor: A_HomesteadObject

Properties:

FString ObjectId (e.g., "rack_main_42u_01")

FString Category (e.g., "rack", "container", "sensor", "deterrent")

FTransform WorldTransform (aligned with coordinate system)

UStaticMeshComponent* VisualMesh

Optional U_InteractableComponent*

Optional U_SOPComponent*

Optional U_TelemetryComponent*

This lets you plug the same logic into scanned assets, not just hand-modeled ones.

6.3 Phase Manager

US_HomesteadPhaseManager:

Maintains:

CurrentPhase ∈ {0,1,2,3,4,5}

Data table mapping phases → visibility sets.

Finite list of Phase Layers:

Phase 0: minimal containers + basic power/data.

Phase 1: workshop container + rack fleshed out.

Phase 2: tiny-home container, basic orchard.

Phase 3: greenhouse + expanded orchard, ponds/swales.

Phase 4: extended perimeter & deterrence.

Phase 5: full build-out (Aircela, extra infra, etc.).

Mechanics:

Blueprint / C++ toggles SetActorHiddenInGame or level streaming per phase.

Phase selection exposed through UI (desktop + VR).

7. SOP & Annotation System
7.1 SOP Data Model

Represent SOPs in a data table (JSON/CSV imported into UE) with something like:

SOPId (string)

Title

LinkedObjectIds (array of object IDs)

Steps (array of step text, or a structured type)

EstimatedTime

Tags (e.g., "power", "fire", "security")

Example: SOP_POWER_DOWN_RACK_01.

7.2 SOPComponent

U_SOPComponent attached to A_HomesteadObject:

Holds:

List of SOPIds relevant to this object.

When player interacts:

UI panel (WID_SOPViewer) shows relevant SOPs.

7.3 Annotations

US_AnnotationManager:

Allows you to:

Create markers in the world: notes, reminders, future tasks.

Each annotation:

Position in world.

Text + optional category.

UX:

Desktop: Right-click + “Add note”, or hotkey.

VR: Laser pointer → press button to create note.

Data persistence via simple JSON file saved alongside UE save data (or a lightweight SQLite DB if you want to overkill it later).

8. Telemetry & Simulation Hooks (Future)
8.1 Telemetry Manager

US_TelemetryManager:

Config:

Endpoint URLs (REST) or MQTT topics.

Poll interval (e.g., 1–5 seconds).

Data structures:

Key-value map (e.g., {"rack_temp_c": 28.3, "battery_soc": 0.72}).

8.2 Telemetry Component

U_TelemetryComponent:

Attach to actors that want live data overlay:

Rack, PV array, batteries, NetBotz, doors, etc.

Config per component:

Telemetry key(s) (e.g., "rack_temp_c", "battery_soc").

Display mode:

Floating text

Color changes (e.g., green-yellow-red)

Graph widget when focused.

8.3 Scenario Buttons

In-world panel or UI widget with scenario triggers:

Power Failure Sim

Toggles visual “offline” state for non-critical loads.

Intrusion at North Perimeter

Highlights:

LRAD coverage cone.

Camera FOVs.

Fire in Rack Container

Highlights fire extinguisher locations, egress routes.

These can be purely visual; no need to build full physics or NFPA-level fire modeling.

9. UX & Interaction
9.1 Navigation

Desktop:

WASD movement, mouse look.

Shift for sprint; control for slow walk/fine movement.

Optional free-fly for “god mode.”

VR:

Teleport locomotion by default.

Optional smooth locomotion if you’re comfortable.

Simple laser pointer for UI interaction.

9.2 Interaction Pattern

Look at object → small context reticle.

Press interact key (desktop: E, VR: trigger):

Bring up:

Object info panel (name, category, notes).

SOPs list.

Telemetry (if available).

Phase-specific notes (e.g., “Phase 3: planned upgrade here”).

Short, low-bullshit UI: panels that auto-close when you move away or press escape/back.

10. Performance & Quality Targets

Target 60+ FPS desktop, 90 Hz in VR where possible.

Use Nanite for heavy scanned meshes where appropriate; or decimate externally.

Simplify:

Use low-res collision meshes.

Disable complex physics on static assets (containers, rack, etc.).

Lighting:

Start with static or simple Lumen GI.

Avoid overkill reflections; it’s a planning tool, not a AAA shooter.

11. Project Structure (UE)

Inside /ue5:

/ue5/Project/HomesteadTwin.uproject
/ue5/Project/Source/...
/ue5/Project/Content
  /Scans
    /Environment
    /Containers
    /Rack
    /Workshop
    /TinyHome
    /Greenhouse
  /Blueprints
    /Core
    /Subsystems
    /Actors
  /UI
    /Widgets
  /Materials
  /Maps
    /Main
    /Sublevels


Naming style:

Map: Map_Homestead_Main, Map_RackInterior.

Blueprint: BP_HomesteadObject, BP_Rack, BP_Container.

Widget: WID_SOPViewer, WID_ObjectInfoPanel, WID_PhaseSelector.

12. Development Phases (Implementation Roadmap)
Phase A – Bootstrap

Create UE5 project.

Set up:

Core GameInstance/GameMode/PlayerControllers.

Basic terrain, one container placeholder.

Basic first-person and VR pawns.

Phase B – Greybox Homestead

Greybox containers, pond, orchard zone, PV field.

Implement:

Coordinate system.

Phase Manager (basic toggling).

Simple HUD.

Phase C – Integrate First Scans

Scan + import:

Site terrain.

Rack container exterior.

Rack interior (first pass).

Replace greybox assets with scanned meshes in the main level.

Phase D – Interaction Layer

Implement A_HomesteadObject + U_InteractableComponent.

Build:

Object info UI.

SOP system (data table + viewer).

Basic annotations.

Phase E – Interior Pass & Usability

Scan tiny home, workshop, greenhouse (as they exist).

Add VR quality-of-life:

Comfortable teleport.

Object interaction.

Phase F – Telemetry & Scenarios (Optional, Later)

Implement US_TelemetryManager with dummy data.

Attach U_TelemetryComponent to:

Rack, PV, batteries, doors.

Add scenario panel for:

Power loss, intrusion, fire.

13. Open Questions / Later Decisions

Which specific scanner model are we standardizing around? (Miraco vs Einstar) – this affects typical mesh density / data rates but not high-level design.

How much of the NetBotz / OPNsense telemetry do you want pulled in vs just simulated?

Do you want a “print helper” panel inside the twin (e.g., select object → show which STL/CAD file it came from and where it lives on disk)?

Do we care about weather/time-of-day simulation beyond light angle? (e.g., PV shadow analysis per hour — possible, but a different level of effort.)
