# Phase A Implementation Checklist

Use this checklist to track your progress through Phase A (Bootstrap & Foundation).

**Estimated Duration**: 1-2 weeks
**Goal**: Working UE5 project with basic desktop and VR navigation

---

## Pre-Implementation

- [ ] Unreal Engine 5.3 (or later) installed
- [ ] Visual Studio 2022 (Windows) or Xcode (Mac) installed with C++ tools
- [ ] Git repository cloned locally
- [ ] VR headset available (optional, for VR testing)

---

## Part 1: Project Setup (30-60 min)

- [ ] Open `HomesteadTwin.uproject` in UE5 Editor
- [ ] Compile C++ source successfully (click Yes if prompted to rebuild)
- [ ] Verify C++ classes visible in Content Browser (enable "Show C++ Classes")
- [ ] Configure Project Settings:
  - [ ] Set project name and description
  - [ ] Enable VR plugins (SteamVR, SteamVRInput) if using VR
  - [ ] Set rendering settings (DirectX 12, Forward Shading for VR)
- [ ] No compilation errors in Output Log

---

## Part 2: Core Blueprint Classes (3-5 hours)

### Game Instance
- [ ] Create `Content/Blueprints/Core/` folder structure
- [ ] Create `BP_GI_HomesteadTwin` Blueprint extending `GI_HomesteadTwin`
- [ ] Set Application Version to "0.1.0-alpha"
- [ ] Set as Game Instance in Project Settings → Maps & Modes
- [ ] Compile and save

### Game Mode
- [ ] Create `BP_GM_HomesteadTwin` Blueprint extending `GM_HomesteadTwin`
- [ ] Set Default Spawn Transform: Location (0, 0, 100)
- [ ] Compile and save (will set Pawn/Controller classes later)

### Desktop Player Controller
- [ ] Create `BP_PC_Desktop` Blueprint extending `PC_Desktop`
- [ ] Set Interaction Raycast Distance: 500.0
- [ ] Implement Event Tick → PerformInteractionRaycast logic
- [ ] Implement OnInteractPressed event (add Print String for testing)
- [ ] Compile and save

### VR Player Controller
- [ ] Create `BP_PC_VR` Blueprint extending `PC_VR`
- [ ] Set Use Teleport Locomotion: true
- [ ] Set Enable Vignette: true
- [ ] Set Enable Snap Turning: true
- [ ] Set Snap Turn Angle: 45.0
- [ ] Compile and save

### Desktop Pawn
- [ ] Create `BP_Pawn_Desktop` Blueprint extending `Pawn_Desktop`
- [ ] Verify CameraComponent and MovementComponent present
- [ ] Set Base Movement Speed: 600.0
- [ ] Set Sprint Multiplier: 2.0
- [ ] Set Slow Walk Multiplier: 0.5
- [ ] Implement MoveForward custom event
- [ ] Implement MoveRight custom event
- [ ] Implement LookUp custom event
- [ ] Implement Turn custom event
- [ ] Compile and save

### VR Pawn
- [ ] Create `BP_Pawn_VR` Blueprint extending `Pawn_VR`
- [ ] Verify VR component hierarchy (VRRoot, VRCamera, Controllers)
- [ ] Add/verify motion controller components (Left/Right)
- [ ] Add placeholder hand meshes (cubes/spheres for now)
- [ ] Set Teleport Arc Velocity: 500.0
- [ ] Set Max Teleport Distance: 1000.0
- [ ] Compile and save

---

## Part 3: Input Bindings (1-2 hours)

### Desktop Input (Simplified for Phase A)
In `BP_PC_Desktop` Event Graph:

- [ ] Add W key event → Call MoveForward(1.0) on controlled pawn
- [ ] Add S key event → Call MoveForward(-1.0) on controlled pawn
- [ ] Add A key event → Call MoveRight(-1.0) on controlled pawn
- [ ] Add D key event → Call MoveRight(1.0) on controlled pawn
- [ ] Add Mouse X event → Call Turn on controlled pawn
- [ ] Add Mouse Y event → Call LookUp on controlled pawn (with negate)
- [ ] Add E key event → Call OnInteractPressed
- [ ] Compile and save

### VR Input
- [ ] For Phase A, defer detailed VR input to Phase E
- [ ] Basic head tracking should work automatically

---

## Part 4: HUD Widgets (2-3 hours)

### Desktop HUD Widget
- [ ] Create `Content/UI/Widgets/Core/` folder structure
- [ ] Create `WID_HUD_Minimal` Widget Blueprint
- [ ] Add Canvas Panel (root)
- [ ] Add Crosshair image (center, anchored 0.5/0.5)
- [ ] Add Interaction Prompt text (below crosshair, initially hidden)
- [ ] Add Phase Indicator text (top-left corner)
- [ ] Create UpdateInteractionPrompt function
- [ ] Create UpdatePhaseIndicator function
- [ ] Compile and save

### VR HUD Widget
- [ ] Create `WID_HUD_VR` Widget Blueprint
- [ ] Add Canvas Panel (root)
- [ ] Add Laser Reticle image (center, initially hidden)
- [ ] Add Phase Indicator text (top-left, minimal)
- [ ] Keep very minimal (VR best practice)
- [ ] Compile and save

### HUD Actor Class
- [ ] Create `BP_HUD_Desktop` Blueprint extending HUD class
- [ ] Event Begin Play: Create WID_HUD_Minimal widget
- [ ] Add widget to viewport
- [ ] Store widget reference in variable
- [ ] Compile and save

---

## Part 5: Test Map (2-3 hours)

### Create Main Map
- [ ] Create `Content/Maps/Main/` folder
- [ ] File → New Level → Empty Level
- [ ] Save as `Map_Homestead_Main`

### Add Lighting
- [ ] Place Directional Light (position: 0,0,1000, rotation: -45,0,0)
- [ ] Set Intensity: 10.0, Mobility: Stationary
- [ ] Place Sky Light (intensity: 1.0, mobility: Stationary)
- [ ] Place Sky Atmosphere actor

### Add Geometry
- [ ] Add ground plane (scale: 100,100,1, position: 0,0,0)
- [ ] Apply basic material to ground
- [ ] Add greybox rack container placeholder:
  - [ ] Cube scaled to (243, 610, 260) cm
  - [ ] Position: (0, 0, 130)
  - [ ] Gray material
  - [ ] Text Render: "Rack Container"

### Configure Map
- [ ] Add Player Start (position: 500,500,100, face toward origin)
- [ ] Window → World Settings → Game Mode Override: BP_GM_HomesteadTwin
- [ ] Save map

---

## Part 6: Final Configuration (30 min)

### Game Mode Setup
- [ ] Open `BP_GM_HomesteadTwin`
- [ ] Set Default Pawn Class: `BP_Pawn_Desktop`
- [ ] Set Player Controller Class: `BP_PC_Desktop`
- [ ] Set HUD Class: `BP_HUD_Desktop`
- [ ] Compile and save

### Project Settings
- [ ] Edit → Project Settings → Maps & Modes
- [ ] Set Editor Startup Map: `Map_Homestead_Main`
- [ ] Set Game Default Map: `Map_Homestead_Main`
- [ ] Save settings

---

## Part 7: Testing & Verification (1-2 hours)

### Desktop Mode Tests
- [ ] Click Play (Alt+P) in editor
- [ ] Game launches without errors (check Output Log)
- [ ] HUD visible with crosshair and phase indicator
- [ ] WASD keys move pawn smoothly
- [ ] Mouse look works (pitch and yaw)
- [ ] E key triggers interaction (see "Interact pressed!" in log)
- [ ] Can navigate to greybox container
- [ ] Performance acceptable (60+ FPS)
- [ ] No console errors or warnings

### VR Mode Tests (if VR hardware available)
- [ ] Connect VR headset and start SteamVR
- [ ] Open `BP_GM_HomesteadTwin`
- [ ] Change Default Pawn Class to `BP_Pawn_VR`
- [ ] Change Player Controller Class to `BP_PC_VR`
- [ ] Save and close
- [ ] Click Play dropdown → VR Preview
- [ ] Head tracking works in VR
- [ ] Motion controllers visible (as placeholder meshes)
- [ ] Can look around naturally
- [ ] No nausea-inducing issues
- [ ] 90 Hz frame rate maintained

### Performance Check
- [ ] Desktop: Stat FPS → verify 60+ FPS
- [ ] VR: Stat FPS → verify 90+ FPS
- [ ] No significant frame drops
- [ ] Memory usage reasonable (< 2GB)

---

## Part 8: Documentation (30 min)

- [ ] Take screenshots of working HUD
- [ ] Take screenshot of test map
- [ ] Document any deviations from guide in project notes
- [ ] Update ROADMAP.md Phase A checkboxes
- [ ] Commit working changes to git

---

## Optional Enhancements (Time Permitting)

- [ ] Add free-fly camera toggle (F key) for desktop
- [ ] Add minimap or overhead view
- [ ] Improve crosshair visual (custom texture)
- [ ] Add FPS counter to HUD (toggle with F1)
- [ ] Add basic teleport visualization for VR (arc + marker)
- [ ] Create additional greybox containers (workshop, tiny home)
- [ ] Implement sprint (Shift) and slow walk (Ctrl) for desktop
- [ ] Add simple audio (footsteps, UI clicks)

---

## Troubleshooting

### Common Issues

**Input not working**:
- [ ] Check input bindings in BP_PC_Desktop Event Graph
- [ ] Verify "Click to gain focus" in play mode
- [ ] Check Game Mode is using correct controller class

**HUD not visible**:
- [ ] Check HUD class set in Game Mode
- [ ] Check widget Z-order and visibility settings
- [ ] Verify Event Begin Play creates and adds widget

**VR not launching**:
- [ ] Verify SteamVR is running
- [ ] Check VR plugins enabled in Project Settings
- [ ] Restart UE Editor after enabling plugins
- [ ] Check Output Log for VR initialization errors

**Compilation errors**:
- [ ] Close UE Editor
- [ ] Delete Intermediate/, Saved/, Binaries/ folders
- [ ] Regenerate project files
- [ ] Rebuild in Visual Studio
- [ ] Reopen in UE Editor

**Performance issues**:
- [ ] Check lighting is set to Stationary (not Movable)
- [ ] Disable real-time lighting in viewport
- [ ] Simplify geometry (reduce poly count)
- [ ] Check for Blueprint Tick overhead

---

## Success Criteria

Phase A is complete when:

✅ **Project launches** without errors in UE Editor

✅ **Desktop navigation** works smoothly (WASD + mouse)

✅ **HUD displays** correctly with crosshair and prompts

✅ **Interaction system** triggers (E key event fires)

✅ **VR mode** launches and tracks head/controllers (if applicable)

✅ **Test map** has proper lighting and coordinate system

✅ **Performance** meets targets (60+ FPS desktop, 90 Hz VR)

✅ **Code compiles** without errors or warnings

✅ **Changes committed** to git with clear commit messages

---

## Next Phase

Once Phase A is complete:

**Phase B: Greybox Homestead & Phase System**

- Create greybox geometry for all containers and zones
- Implement Phase Manager subsystem
- Create Phase Selector widget
- Set up level streaming

See `ROADMAP.md` for Phase B details.

---

**Last Updated**: 2025-11-16
**Phase**: A (Bootstrap & Foundation)
**Related**: `phase_a_blueprint_guide.md`, `ROADMAP.md`
