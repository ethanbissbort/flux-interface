# Phase A Implementation Guide: Blueprint Extension

This guide walks you through implementing Phase A (Bootstrap & Foundation) by creating Blueprint classes that extend the C++ stub headers.

**Target Duration**: 1-2 weeks
**Prerequisites**: Unreal Engine 5.3+ installed, HomesteadTwin.uproject created

---

## Overview

Phase A focuses on establishing:
- Working UE5 project with basic navigation
- Core framework (Game Instance, Game Mode, Player Controllers, Pawns)
- Desktop and VR input/movement
- Test environment with basic HUD

By the end of Phase A, you should be able to:
- Launch the project in UE5 Editor
- Navigate in desktop mode (WASD + mouse)
- Navigate in VR mode (teleport/smooth locomotion)
- See a minimal HUD with interaction prompts

---

## Part 1: Project Setup & Verification

### Step 1.1: Open Project in Unreal Engine

1. **Locate the project file**:
   ```
   homestead_twin/Project/HomesteadTwin.uproject
   ```

2. **Right-click** on `HomesteadTwin.uproject` → **Generate Visual Studio project files** (Windows) or **Generate Xcode project** (Mac)

3. **Double-click** `HomesteadTwin.uproject` to open in Unreal Engine Editor

4. **If prompted to rebuild**:
   - Click **Yes** to compile C++ code
   - Wait for compilation to complete
   - Editor will open when ready

5. **Verify C++ classes are visible**:
   - In **Content Browser**, click **View Options** (bottom-right)
   - Enable **Show C++ Classes**
   - Navigate to **C++ Classes > HomesteadTwin** folder
   - You should see all header stub classes (GI_HomesteadTwin, GM_HomesteadTwin, etc.)

**Troubleshooting**:
- If compilation fails, check `homestead_twin/Project/Source/README.md` for build instructions
- Ensure Visual Studio 2022 (Windows) or Xcode (Mac) is installed with C++ tools

---

### Step 1.2: Configure Project Settings

Before creating Blueprints, configure base project settings:

1. **Edit → Project Settings**

2. **Maps & Modes**:
   - Set **Default Maps**:
     - Editor Startup Map: (none for now)
     - Game Default Map: (none for now)
   - We'll set these after creating the test map

3. **Engine → Input**:
   - Enhanced Input: **Enabled** (UE5 default)
   - We'll configure input mappings later

4. **Project → Description**:
   - Project Name: `Homestead Twin`
   - Description: `Digital twin of Fluxology Homestead`
   - Company Name: `Fluxology`
   - Version: `0.1.0-alpha`

5. **VR Settings** (if using VR):
   - **Platforms → Windows → D3D12 Targeted Shader Formats**: Add `PCD3D_SM6`
   - **Platforms → Windows → Default RHI**: DirectX 12
   - **Engine → Rendering**:
     - Default Settings → Forward Shading: **Enabled** (better VR performance)
     - VR → Instanced Stereo: **Enabled**
     - VR → Round Robin Occlusion Queries: **Enabled**

6. **Save** settings

---

## Part 2: Create Core Blueprint Classes

We'll create Blueprint classes in this order:
1. Game Instance
2. Game Mode
3. Player Controllers (Desktop and VR)
4. Pawns (Desktop and VR)

### Step 2.1: Create BP_GI_HomesteadTwin (Game Instance)

**Location**: `Content/Blueprints/Core/BP_GI_HomesteadTwin`

1. **Content Browser**: Navigate to `Content` folder
2. **Right-click** → **New Folder** → Name: `Blueprints`
3. **Inside Blueprints**: Create new folder → Name: `Core`
4. **Inside Core** folder:
   - **Right-click** → **Blueprint Class**
   - **Pick Parent Class** window: Click **All Classes** dropdown
   - Search for `GI_HomesteadTwin` (your C++ class)
   - Select `GI_HomesteadTwin` → Click **Select**
5. **Name** the Blueprint: `BP_GI_HomesteadTwin`
6. **Double-click** to open Blueprint Editor

**Configure BP_GI_HomesteadTwin**:

1. **Event Graph**:
   - You should see event nodes for `OnHomesteadTwinInit` and `OnHomesteadTwinShutdown` (from C++ BlueprintImplementableEvent)
   - For now, leave them empty (we'll add subsystem initialization later)

2. **Class Defaults** (Details panel on right):
   - Set **Application Version**: `"0.1.0-alpha"`
   - Set **Is VR Mode**: `false` (default to desktop, we'll add VR toggle later)

3. **Compile** and **Save**

4. **Set as Game Instance**:
   - **Edit → Project Settings**
   - **Project → Maps & Modes**
   - **Game Instance Class**: Select `BP_GI_HomesteadTwin`
   - **Save** settings

---

### Step 2.2: Create BP_GM_HomesteadTwin (Game Mode)

**Location**: `Content/Blueprints/Core/BP_GM_HomesteadTwin`

1. **Content Browser**: Navigate to `Content/Blueprints/Core/`
2. **Right-click** → **Blueprint Class** → **All Classes** → Search `GM_HomesteadTwin`
3. **Name**: `BP_GM_HomesteadTwin`
4. **Open** Blueprint Editor

**Configure BP_GM_HomesteadTwin**:

1. **Class Defaults** (Details panel):
   - **Default Spawn Transform**:
     - Location: `(0, 0, 100)` (100 cm above origin, adjust as needed)
     - Rotation: `(0, 0, 0)`
     - Scale: `(1, 1, 1)`
   - **Force VR Mode**: `false`

2. **Classes** section (will set these after creating Pawns and Controllers):
   - Default Pawn Class: (leave for now)
   - Player Controller Class: (leave for now)
   - HUD Class: (leave for now, we'll create HUD later)

3. **Event Graph**:
   - Events `OnGameModeInit` and `OnGameplayStart` are available
   - Leave empty for now

4. **Compile** and **Save**

---

### Step 2.3: Create BP_PC_Desktop (Desktop Player Controller)

**Location**: `Content/Blueprints/Core/BP_PC_Desktop`

1. **Content Browser**: Navigate to `Content/Blueprints/Core/`
2. **Right-click** → **Blueprint Class** → **All Classes** → Search `PC_Desktop`
3. **Name**: `BP_PC_Desktop`
4. **Open** Blueprint Editor

**Configure BP_PC_Desktop**:

1. **Class Defaults**:
   - **Interaction Raycast Distance**: `500.0` (cm, = 5 meters)
   - **Interaction Update Rate**: `0.1` (seconds, update 10 times per second)

2. **Event Graph** - Implement basic interaction raycast:

   **Add Event Tick**:
   ```
   Event Tick
   ├─> Branch (if IsValid(Controlled Pawn))
   │   ├─ True → Call PerformInteractionRaycast
   │   │         ├─ Max Distance: 500.0
   │   │         └─ Return Value → Set FocusedObject variable
   │   └─ False → (do nothing)
   ```

   To create this:
   - **Right-click** → Search "Event Tick" → Add
   - From Event Tick, drag out → Search "Branch"
   - For Branch condition: Get Controlled Pawn → IsValid
   - From True pin: Search "Perform Interaction Raycast" (from C++ function)
   - Connect return value to Set FocusedObject (create variable if needed)

3. **Implement OnInteractPressed event**:
   - **Right-click** → Search "Event On Interact Pressed" (from C++ BlueprintImplementableEvent)
   - This event fires when player presses E key
   - For now, add a **Print String** node with text "Interact pressed!" for testing

4. **Compile** and **Save**

**Note**: We'll add input bindings later in Part 4.

---

### Step 2.4: Create BP_PC_VR (VR Player Controller)

**Location**: `Content/Blueprints/Core/BP_PC_VR`

1. **Content Browser**: Navigate to `Content/Blueprints/Core/`
2. **Right-click** → **Blueprint Class** → **All Classes** → Search `PC_VR`
3. **Name**: `BP_PC_VR`
4. **Open** Blueprint Editor

**Configure BP_PC_VR**:

1. **Class Defaults**:
   - **Use Teleport Locomotion**: `true` (default to teleport for comfort)
   - **Enable Vignette**: `true` (reduce motion sickness)
   - **Enable Snap Turning**: `true` (comfort over smooth turning)
   - **Snap Turn Angle**: `45.0` (degrees)
   - **Laser Pointer Distance**: `1000.0` (cm, = 10 meters)

2. **Event Graph**:
   - For Phase A, leave minimal implementation
   - We'll implement VR-specific logic when we have VR pawn and motion controllers

3. **Compile** and **Save**

---

### Step 2.5: Create BP_Pawn_Desktop (Desktop Pawn)

**Location**: `Content/Blueprints/Core/BP_Pawn_Desktop`

1. **Content Browser**: Navigate to `Content/Blueprints/Core/`
2. **Right-click** → **Blueprint Class** → **All Classes** → Search `Pawn_Desktop`
3. **Name**: `BP_Pawn_Desktop`
4. **Open** Blueprint Editor

**Configure BP_Pawn_Desktop Components**:

1. **Components Panel** (top-left):
   - You should see inherited components: `CameraComponent`, `MovementComponent`
   - If not visible, they're defined in C++ but may not show in Blueprint

2. **Add Camera Component** (if not present):
   - Click **Add Component** → Search "Camera"
   - Name: `CameraComponent`
   - Location: (0, 0, 88) — eye height, about 88 cm for first-person

3. **Add Floating Pawn Movement** (if not present):
   - Click **Add Component** → Search "Floating Pawn Movement"
   - Name: `MovementComponent`

4. **Class Defaults**:
   - **Base Movement Speed**: `600.0` (cm/s, = walking speed)
   - **Sprint Multiplier**: `2.0` (double speed when sprinting)
   - **Slow Walk Multiplier**: `0.5` (half speed for precision)
   - **Mouse Sensitivity**: `1.0`

5. **Event Graph** - Implement movement functions:

   **These functions are defined in C++ header as protected, so we implement them here:**

   **MoveForward function**:
   - **Right-click** → Add Custom Event → Name: `MoveForward`
   - Add input parameter: `Value` (Float)
   - Logic:
     ```
     MoveForward(Value)
     └─> Branch (if Value != 0)
         └─ True → Add Movement Input
                   ├─ World Direction: Get Actor Forward Vector
                   ├─ Scale Value: Value
                   └─ (connects to controlled pawn)
     ```

   **MoveRight function**:
   - Similar to MoveForward, but use `Get Actor Right Vector`

   **LookUp function**:
   - Custom Event: `LookUp` (Value: Float)
   - Logic: `Add Controller Pitch Input` with Value

   **Turn function**:
   - Custom Event: `Turn` (Value: Float)
   - Logic: `Add Controller Yaw Input` with Value

6. **Compile** and **Save**

**Note**: We'll bind these functions to input in Part 4.

---

### Step 2.6: Create BP_Pawn_VR (VR Pawn)

**Location**: `Content/Blueprints/Core/BP_Pawn_VR`

1. **Content Browser**: Navigate to `Content/Blueprints/Core/`
2. **Right-click** → **Blueprint Class** → **All Classes** → Search `Pawn_VR`
3. **Name**: `BP_Pawn_VR`
4. **Open** Blueprint Editor

**Configure BP_Pawn_VR Components**:

VR pawn requires more complex component setup:

1. **Components Panel**:

   **VR Root** (Scene Component):
   - Should be inherited from C++
   - This is the origin of your play space

   **VR Camera**:
   - Inherited Camera Component
   - Attached to VR Root
   - Tracks HMD position automatically

   **Motion Controllers**:
   - Should be inherited: `LeftController`, `RightController`
   - If not present, add them:
     - **Add Component** → **Motion Controller**
     - Name: `LeftController`
     - Details → Motion Source: `Left`
     - Repeat for Right

   **Hand Meshes** (visual representation):
   - Should be inherited: `LeftHandMesh`, `RightHandMesh`
   - If not present, add **Static Mesh Components** attached to controllers
   - For now, use placeholder meshes (cube or sphere)
   - We'll replace with proper hand models later

   **Laser Pointers**:
   - Should be inherited: `LeftLaserPointer`, `RightLaserPointer`
   - These are visual beams from controllers
   - For Phase A, we can use simple line traces (no mesh yet)

2. **Class Defaults**:
   - **Teleport Arc Velocity**: `500.0` (cm/s)
   - **Smooth Locomotion Speed**: `300.0` (cm/s)
   - **Max Teleport Distance**: `1000.0` (cm, = 10 meters)

3. **Event Graph**:
   - For Phase A, we'll implement basic teleport in Part 5
   - Leave minimal for now

4. **Compile** and **Save**

---

## Part 3: Create Minimal HUD Widgets

### Step 3.1: Create WID_HUD_Minimal (Desktop HUD)

**Location**: `Content/UI/Widgets/Core/WID_HUD_Minimal`

1. **Content Browser**: Create folder structure:
   - `Content/UI/` → `Widgets/` → `Core/`

2. **Inside Core**:
   - **Right-click** → **User Interface** → **Widget Blueprint**
   - Name: `WID_HUD_Minimal`

3. **Open Widget Blueprint**:

**Designer Tab**:

1. **Canvas Panel** (root):
   - Should be default root

2. **Add Crosshair** (center of screen):
   - Drag **Image** widget onto Canvas Panel
   - Name: `Crosshair`
   - Anchors: Center (0.5, 0.5)
   - Position: (0, 0)
   - Size: (32, 32)
   - Alignment: (0.5, 0.5) — centers the image on anchor point
   - Brush → Tint: White with 50% opacity
   - For now, use **DefaultTexture** or create simple crosshair texture

3. **Add Interaction Prompt** (below crosshair):
   - Drag **Text Block** onto Canvas Panel
   - Name: `InteractionPromptText`
   - Anchors: Center (0.5, 0.5)
   - Position: (0, 50) — 50 pixels below center
   - Size To Content: Enabled
   - Alignment: (0.5, 0.0)
   - Text: `"Press E to interact"`
   - Font Size: 16
   - Justification: Center
   - Color: White
   - Visibility: **Hidden** (default hidden, show when focused on object)

4. **Add Phase Indicator** (top-left):
   - Drag **Text Block** onto Canvas Panel
   - Name: `PhaseIndicatorText`
   - Anchors: Top-Left (0, 0)
   - Position: (20, 20)
   - Text: `"Phase 0"`
   - Font Size: 14
   - Color: White with 70% opacity

**Graph Tab**:

1. **Create BindableEvent for updating prompt**:
   - Create function: `UpdateInteractionPrompt`
   - Input: `bShowPrompt` (Boolean), `PromptText` (String)
   - Logic:
     ```
     If bShowPrompt:
       Set InteractionPromptText → Visibility: Visible
       Set InteractionPromptText → Text: PromptText
     Else:
       Set InteractionPromptText → Visibility: Hidden
     ```

2. **Create function to update phase indicator**:
   - Function: `UpdatePhaseIndicator`
   - Input: `PhaseNumber` (Integer)
   - Logic: Set PhaseIndicatorText → Text: Format("Phase {0}", PhaseNumber)

3. **Compile** and **Save**

---

### Step 3.2: Create WID_HUD_VR (VR HUD)

**Location**: `Content/UI/Widgets/Core/WID_HUD_VR`

1. **Content Browser**: In `Content/UI/Widgets/Core/`
   - **Right-click** → **User Interface** → **Widget Blueprint**
   - Name: `WID_HUD_VR`

2. **Open Widget Blueprint**:

**Designer Tab**:

For VR, we want MINIMAL screen-space UI (avoid discomfort):

1. **Canvas Panel** (root)

2. **Add Laser Pointer Reticle Indicator** (center):
   - **Image** widget
   - Name: `LaserReticle`
   - Anchors: Center (0.5, 0.5)
   - Size: (24, 24)
   - Tint: Cyan with 50% opacity
   - Visibility: **Hidden** (only show when laser pointer is active)

3. **Add Phase Indicator** (small, top-left):
   - **Text Block**
   - Name: `PhaseText`
   - Anchors: Top-Left
   - Position: (20, 20)
   - Font Size: 12
   - Text: `"Phase 0"`
   - Color: White with 50% opacity

**Graph Tab**:

- Similar update functions as desktop HUD
- For Phase A, keep minimal
- We'll add 3D widget components in Phase D

**Compile** and **Save**

---

## Part 4: Configure Input Mappings

### Step 4.1: Create Input Actions

UE5 uses Enhanced Input system. We'll create Input Actions and Input Mapping Contexts.

**Create folder**: `Content/Input/`

1. **Create Input Actions**:

   Navigate to `Content/Input/`

   **IA_Move** (Movement):
   - **Right-click** → **Input** → **Input Action**
   - Name: `IA_Move`
   - Open it → **Value Type**: Axis2D (Vector2D)
   - Save

   **IA_Look** (Camera rotation):
   - Create Input Action: `IA_Look`
   - Value Type: Axis2D (Vector2D)
   - Save

   **IA_Interact** (Interact with objects):
   - Create Input Action: `IA_Interact`
   - Value Type: Digital (bool)
   - Save

   **IA_Sprint** (Sprint modifier):
   - Create Input Action: `IA_Sprint`
   - Value Type: Digital (bool)
   - Save

   **IA_SlowWalk** (Slow walk modifier):
   - Create Input Action: `IA_SlowWalk`
   - Value Type: Digital (bool)
   - Save

   **IA_Jump** (VR teleport trigger):
   - Create Input Action: `IA_Jump`
   - Value Type: Digital (bool)
   - Save

2. **Create Input Mapping Context** for Desktop:

   **Right-click** in `Content/Input/` → **Input** → **Input Mapping Context**
   - Name: `IM_Desktop`
   - Open it

   **Add Mappings**:
   - Click **+** next to Mappings

   **Movement (WASD)**:
   - Mapping: `IA_Move`
     - Key: `W` → Modifiers: **Swizzle Input Axis Values** → Order: XZY, then **Negate** → Y axis
     - (This makes W = forward as positive Y)
     - Actually, simpler approach:
   - Delete that, let's do it properly:

   **IA_Move mappings**:
   - `W` key: Add modifier "Swizzle Input Axis Values" (YXZ order), value (0, 1)
   - `S` key: Modifier "Swizzle" + "Negate", value (0, -1)
   - `A` key: Modifier "Swizzle", value (-1, 0)
   - `D` key: Modifier "Swizzle", value (1, 0)

   **Actually, Enhanced Input is complex. Simpler approach for Phase A:**

   Let's bind keys directly in Player Controller Blueprint for now, and configure proper Enhanced Input in Phase B.

### Step 4.2: Bind Input in BP_PC_Desktop (Simplified for Phase A)

Open `BP_PC_Desktop`:

**Event Graph**:

1. **Add Input Event: W Key**:
   - Right-click → Input → Keyboard Events → W
   - Pressed → Call `MoveForward` (on Controlled Pawn, cast to BP_Pawn_Desktop)
   - Value: 1.0
   - Released → Call `MoveForward` with Value: 0.0

2. **Add Input Event: S Key**:
   - Similar, but Value: -1.0 (move backward)

3. **Add Input Event: A Key**:
   - Call `MoveRight` with Value: -1.0

4. **Add Input Event: D Key**:
   - Call `MoveRight` with Value: 1.0

5. **Add Mouse Input**:
   - Right-click → Input → Mouse Events → Mouse X
   - Add Mouse X → Call `Turn` on Controlled Pawn
   - Add Mouse Y → Call `LookUp` on Controlled Pawn (with Negate for inverted Y)

6. **Add Interact Key (E)**:
   - Right-click → Input → Keyboard Events → E
   - Pressed → Call your `OnInteractPressed` event implementation

This is a simplified approach. We'll refactor to proper Enhanced Input in Phase B.

**Compile** and **Save**

---

## Part 5: Create Test Map

### Step 5.1: Create Map_Homestead_Main

**Location**: `Content/Maps/Main/Map_Homestead_Main`

1. **Content Browser**: Create folder `Content/Maps/` → `Main/`

2. **File → New Level**:
   - Select **Empty Level** (we'll add lighting manually)
   - **Save As**: `Content/Maps/Main/Map_Homestead_Main`

3. **Add Basic Lighting**:
   - **Place Actors Panel** (left side) → Search "Directional Light"
   - Drag into level
   - Position: (0, 0, 1000)
   - Rotation: (-45, 0, 0) — sunlight angle
   - **Intensity**: 10.0 (lux)
   - **Mobility**: Stationary (for baked lighting)

4. **Add Sky Light**:
   - Place Actors → "Sky Light"
   - Position: (0, 0, 0)
   - **Intensity**: 1.0
   - **Mobility**: Stationary

5. **Add Sky Atmosphere**:
   - Place Actors → "Sky Atmosphere"
   - Default settings OK

6. **Add Ground Plane**:
   - Place Actors → "Plane" (or create floor)
   - Scale: (100, 100, 1) — large flat ground
   - Position: (0, 0, 0) — this is our origin (SW corner of rack container)
   - Add simple material (gray or grass color)

7. **Add Greybox Container Placeholders**:

   For now, use basic geometry:
   - **Place Actors** → **Basic** → **Cube**
   - Rack Container:
     - Scale: (243, 610, 260) — 20ft shipping container in cm
     - Position: (0, 0, 130) — sitting on ground, center at half-height
     - Material: Gray
     - Add Text Render Actor above it: "Rack Container"

8. **Add Player Start**:
   - **Place Actors** → "Player Start"
   - Position: (500, 500, 100) — offset from origin, 1m above ground
   - Rotation: Look toward origin

9. **Set World Settings**:
   - **Window → World Settings**
   - **Game Mode Override**: `BP_GM_HomesteadTwin`

10. **Save Map**

---

### Step 5.2: Configure Game Mode for Map

1. **Open BP_GM_HomesteadTwin**

2. **Class Defaults**:
   - **Default Pawn Class**: `BP_Pawn_Desktop`
   - **Player Controller Class**: `BP_PC_Desktop`
   - **HUD Class**: (none for now, we'll add in next step)

3. **Compile** and **Save**

---

### Step 5.3: Create and Assign HUD Class

We need a HUD Actor class to display our widget.

1. **Content Browser**: `Content/Blueprints/Core/`
   - **Right-click** → **Blueprint Class** → **HUD**
   - Name: `BP_HUD_Desktop`

2. **Open BP_HUD_Desktop**:

**Event Graph**:

1. **Event Begin Play**:
   - Create Widget → Class: `WID_HUD_Minimal`
   - Return value → Add to Viewport
   - Promote to variable: `HUDWidget`

2. **Compile** and **Save**

3. **Open BP_GM_HomesteadTwin** → Set **HUD Class** to `BP_HUD_Desktop`

---

### Step 5.4: Set Default Maps

1. **Edit → Project Settings**
2. **Maps & Modes**:
   - **Editor Startup Map**: `Map_Homestead_Main`
   - **Game Default Map**: `Map_Homestead_Main`
3. **Save**

---

## Part 6: Test & Verify

### Step 6.1: Desktop Mode Test

1. **Click Play** button in editor (or Alt+P)

2. **Expected Behavior**:
   - Game starts at Player Start location
   - HUD visible with crosshair and phase indicator
   - WASD keys move pawn
   - Mouse moves camera
   - E key prints "Interact pressed!" (if implemented)

3. **Test Movement**:
   - W: Forward
   - S: Backward
   - A: Strafe left
   - D: Strafe right
   - Mouse: Look around

4. **Verify HUD**:
   - Crosshair visible at center
   - Phase indicator shows "Phase 0" at top-left

5. **Check Console** (~ key):
   - No errors
   - Print string should show when pressing E

**Common Issues**:
- **Can't move**: Check input bindings in BP_PC_Desktop
- **No HUD**: Check HUD class in Game Mode
- **Camera not moving**: Check mouse input bindings

---

### Step 6.2: VR Mode Test (Optional, if VR hardware available)

1. **Connect VR headset** (Quest, Vive, Index, etc.)

2. **Launch SteamVR** (if using SteamVR-compatible headset)

3. **In UE Editor**:
   - **File → Project Settings → Plugins**
   - Ensure **SteamVR** plugin enabled

4. **Modify BP_GM_HomesteadTwin**:
   - Change **Default Pawn Class** to `BP_Pawn_VR`
   - Change **Player Controller Class** to `BP_PC_VR`

5. **Play in VR**:
   - Click dropdown next to Play → **VR Preview**
   - Put on headset

6. **Expected Behavior**:
   - Game starts in VR
   - Head tracking works
   - Motion controllers visible (as placeholder meshes)
   - Can look around naturally

**VR Implementation Note**:
- Teleport locomotion not yet fully implemented
- We'll complete VR controls in Phase E
- For Phase A, basic VR tracking is sufficient

---

## Part 7: Phase A Completion Checklist

### A.1 - Project Initialization
- [x] UE5 project opens without errors
- [x] C++ stub classes visible in Content Browser
- [x] Project settings configured
- [x] VR plugins enabled (if using VR)

### A.2 - Core Framework
- [x] BP_GI_HomesteadTwin created and set as Game Instance
- [x] BP_GM_HomesteadTwin created with proper class settings
- [x] BP_PC_Desktop created with input bindings
- [x] BP_PC_VR created with VR settings
- [x] BP_Pawn_Desktop created with movement implementation
- [x] BP_Pawn_VR created with VR components

### A.3 - HUD & UI
- [x] WID_HUD_Minimal created with crosshair and prompts
- [x] WID_HUD_VR created with minimal VR UI
- [x] BP_HUD_Desktop created and assigned to Game Mode
- [x] HUD displays correctly in-game

### A.4 - Test Environment
- [x] Map_Homestead_Main created with lighting
- [x] Ground plane at origin (0,0,0)
- [x] Greybox container placeholders placed
- [x] Player Start positioned correctly
- [x] Map set as default in project settings

### A.5 - Verification
- [x] Desktop mode: Can navigate with WASD + mouse
- [x] Desktop mode: HUD visible and functional
- [x] Desktop mode: Interaction prompt works (E key)
- [x] VR mode (if applicable): Head tracking works
- [x] VR mode (if applicable): Motion controllers visible
- [x] No console errors on launch
- [x] Coordinate system verified (origin at rack container)

---

## Next Steps: Phase B

Once Phase A is complete, proceed to Phase B (Greybox Homestead & Phase System):

1. **Create greybox geometry** for all containers and zones
2. **Implement US_HomesteadPhaseManager** subsystem in Blueprint
3. **Create WID_PhaseSelector** widget
4. **Set up level streaming** for sublevels
5. **Create phase data table** with P0-P5 definitions

See `ROADMAP.md` for detailed Phase B requirements.

---

## Troubleshooting

### Input Not Working

**Problem**: WASD/mouse input not responding

**Solutions**:
1. Check **Edit → Project Settings → Input**:
   - Verify "Use Legacy Input" is **disabled** (we want Enhanced Input)
   - Or if using legacy input, verify action mappings exist
2. Open `BP_PC_Desktop` → Verify input event bindings in Event Graph
3. Check **Click to Gain Focus** in World Settings
4. Verify Game Mode is using correct Player Controller class

---

### HUD Not Visible

**Problem**: HUD widget not showing

**Solutions**:
1. Open `BP_HUD_Desktop` → Verify `Event Begin Play` creates and adds widget to viewport
2. Check Game Mode has HUD class set to `BP_HUD_Desktop`
3. Open widget blueprint → Verify visibility settings (not Hidden)
4. Check Z-order (HUD should be on top)

---

### VR Not Launching

**Problem**: VR Preview fails to start

**Solutions**:
1. Verify VR headset connected and SteamVR running
2. **Edit → Plugins** → Ensure SteamVR plugin enabled
3. Restart UE Editor after enabling plugins
4. Check Windows → Developer → Output Log for VR init errors
5. Set **Start in VR** in project settings → VR

---

### Compilation Errors

**Problem**: C++ classes not compiling

**Solutions**:
1. Close UE Editor
2. Delete `Intermediate/`, `Saved/`, `Binaries/` folders
3. Right-click `.uproject` → Generate Visual Studio project files
4. Open `.sln` in Visual Studio → Build solution
5. Launch editor from Visual Studio (F5) or open `.uproject`

---

## Additional Resources

- **UE5 Enhanced Input**: https://docs.unrealengine.com/5.3/en-US/enhanced-input-in-unreal-engine/
- **VR Development**: https://docs.unrealengine.com/5.3/en-US/vr-development-in-unreal-engine/
- **Blueprint Visual Scripting**: https://docs.unrealengine.com/5.3/en-US/blueprints-visual-scripting-in-unreal-engine/

---

**Last Updated**: 2025-11-16
**Phase**: A (Bootstrap & Foundation)
**Status**: Implementation Guide
**Related**: `ROADMAP.md`, `claude.md`, `homestead_twin/Project/Source/README.md`
