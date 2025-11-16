# UI Widgets Reference

This document defines all UI widgets (UMG) for the Homestead Twin application. Widgets should be created in `Content/UI/Widgets/` in Unreal Editor.

---

## Core HUD Widgets

### WID_HUD_Minimal (Desktop)

**Location**: `Content/UI/Widgets/WID_HUD_Minimal.uasset`

**Purpose**: Minimal, non-intrusive HUD for desktop mode.

**Elements**:
- **Crosshair/Reticle**: Center screen, subtle, changes when hovering over interactable object
- **Interaction Prompt**: Text below crosshair (e.g., "Press E to examine")
  - Only visible when focused on interactable object
  - Fades in/out smoothly
- **Phase Indicator**: Top-left corner, small text showing current phase (e.g., "Phase 2")
  - Clickable to open Phase Selector
- **Quick Info Panel**: Bottom-right corner, optional
  - FPS counter (toggle-able)
  - Current position (toggle-able for debugging)

**Design Notes**:
- Minimalist design, mostly transparent
- Text should be readable but not distracting
- No health bars, ammo counters, or game-like elements
- Respect 16:9 and 21:9 aspect ratios

**Inputs**:
- Tab key: Toggle Phase Selector
- F1 key: Toggle debug info

---

### WID_HUD_VR

**Location**: `Content/UI/Widgets/WID_HUD_VR.uasset`

**Purpose**: VR-specific HUD with 3D space widgets.

**Elements**:
- **Wrist Panel** (attached to non-dominant hand):
  - Phase indicator
  - Quick settings (locomotion mode, comfort settings)
  - Battery/system status (optional)
- **Laser Pointer Reticle**: Visual feedback at laser pointer hit location
  - Changes color/shape when hovering over interactable
- **Floating Panels**: Info panels spawn in 3D space, not screen-space
  - Auto-face player
  - Comfortable reading distance (80-120 cm)

**Design Notes**:
- NO screen-space HUD elements (causes discomfort in VR)
- All UI must be in 3D world space or attached to controllers
- Text must be large enough to read at distance
- Avoid bright whites (use soft grays)
- Support hand-based interaction (not just gaze)

**Inputs**:
- Dominant hand trigger: Interact with focused object
- Non-dominant hand menu button: Toggle wrist panel

---

## Phase System Widgets

### WID_PhaseSelector

**Location**: `Content/UI/Widgets/WID_PhaseSelector.uasset`

**Purpose**: UI panel to switch between homestead phases (P0-P5).

**Elements**:
- **Title**: "Homestead Build Phases"
- **Phase Buttons** (6 buttons, P0-P5):
  - Button text: "Phase N - [Name]" (e.g., "Phase 2 - Tiny Home & Orchard")
  - Active phase highlighted with different color
  - Hover shows phase description tooltip
- **Phase Description Panel**: Selected phase details
  - Phase name and number
  - Description text (2-3 sentences)
  - Key features/systems in this phase (bullet list)
- **Close Button**: X button or "Close" text button

**Layout**:
- Desktop: Center screen overlay, semi-transparent background
- VR: Floating panel in front of player, readable size

**Design Notes**:
- Clear visual feedback for current phase
- Smooth transitions when switching phases
- Loading indicator if phase switch takes time (level streaming)

**Inputs**:
- Desktop: Mouse click on buttons, Esc/Tab to close
- VR: Laser pointer + trigger, grip button to close

---

## Object Interaction Widgets

### WID_ObjectInfoPanel

**Location**: `Content/UI/Widgets/WID_ObjectInfoPanel.uasset`

**Purpose**: Display metadata and info when player interacts with an object.

**Elements**:
- **Header**:
  - Object name (large text)
  - Object category (small text, e.g., "Container", "Rack", "Sensor")
- **Description**: Object description text (editable per object)
- **Metadata Section** (optional, collapsible):
  - Object ID
  - Phase tags
  - Custom metadata tags
- **Action Buttons**:
  - "View SOPs" button (if object has linked SOPs)
  - "View Telemetry" button (if object has telemetry component, future phase)
  - "Add Annotation" button (quick annotation at object position)
- **Close Button**: X or "Close"

**Layout**:
- Desktop: Side panel (right side of screen) or center overlay
- VR: Floating panel near object, auto-positioned for comfort

**Design Notes**:
- Auto-dismiss when player moves away from object
- Smooth animations (fade in/out)
- Support scrolling for long descriptions

**Inputs**:
- Desktop: Mouse click, Esc to close, auto-close on movement
- VR: Laser pointer + trigger, auto-close on movement

---

### WID_SOPViewer

**Location**: `Content/UI/Widgets/WID_SOPViewer.uasset`

**Purpose**: Display Standard Operating Procedures for an object.

**Elements**:
- **Header**: "Standard Operating Procedures"
- **SOP List** (if multiple SOPs):
  - SOP titles as clickable items
  - Tags displayed (e.g., [Power] [Safety])
  - Estimated time shown
- **SOP Detail View** (when SOP selected):
  - SOP title
  - Description
  - Step-by-step list:
    - Step number
    - Step description
    - Warning/caution text (highlighted if present)
    - Estimated duration per step
  - Total estimated time
- **Navigation**:
  - "Back to List" button (if viewing detail)
  - "Back to Object Info" button
- **Close Button**

**Layout**:
- Desktop: Full-width panel or side panel
- VR: Readable floating panel, support scrolling

**Design Notes**:
- Clear hierarchy: list → detail
- Warnings/cautions should be visually distinct (color, icon)
- Support printing or exporting SOP (future feature)
- Step numbers clear and sequential

**Inputs**:
- Desktop: Mouse click, scroll, Esc to close
- VR: Laser pointer, thumbstick scroll, grip to close

---

## Annotation Widgets

### WID_AnnotationEditor

**Location**: `Content/UI/Widgets/WID_AnnotationEditor.uasset`

**Purpose**: Create or edit in-world annotations.

**Elements**:
- **Title**: "Create Annotation" or "Edit Annotation"
- **Text Input**: Multi-line text box for annotation content
  - Character limit: 500 characters
- **Category Dropdown**: Select category (optional)
  - Predefined categories: General, Power, IT, Security, Orchard, Future, etc.
  - "Add New Category" option
- **Phase Association**: Dropdown to link annotation to a phase (optional)
- **Linked Object**: Display linked object (if annotation created from object interaction)
- **Action Buttons**:
  - "Save" button
  - "Delete" button (if editing existing annotation)
  - "Cancel" button

**Layout**:
- Desktop: Center screen overlay, modal dialog
- VR: Floating panel with virtual keyboard or speech-to-text (future)

**Design Notes**:
- Simple, focused interface
- VR text input is challenging; consider pre-defined templates or voice input
- Color-code categories for visual distinction

**Inputs**:
- Desktop: Keyboard for text, mouse for buttons
- VR: Virtual keyboard (UE provides widget), laser pointer for buttons

---

### WID_AnnotationDisplay (in-world)

**Location**: `Content/UI/Widgets/WID_AnnotationDisplay.uasset`

**Purpose**: Widget displayed by A_Annotation actors in 3D space.

**Elements**:
- **Category Icon/Color**: Visual indicator of annotation type
- **Truncated Text Preview**: First 50 characters of annotation text
- **Full Text** (on hover or click):
  - Complete annotation text
  - Timestamp (created/modified)
  - Category and phase info
- **Action Buttons** (on hover):
  - "Edit" button
  - "Delete" button

**Layout**:
- 3D widget component attached to A_Annotation actor
- Billboard behavior (always faces player)
- Scale with distance for readability

**Design Notes**:
- Keep visual clutter minimal
- Preview mode vs. expanded mode
- Color-coded by category

**Inputs**:
- Desktop: Mouse hover/click
- VR: Laser pointer hover/trigger

---

## Telemetry Widgets (Future Phase F)

### WID_TelemetryText

**Location**: `Content/UI/Widgets/WID_TelemetryText.uasset`

**Purpose**: Floating text widget for displaying telemetry values.

**Elements**:
- **Label**: Telemetry key name (e.g., "Rack Temp")
- **Value**: Current value with units (e.g., "28.3°C")
- **Timestamp**: Last update time (relative, e.g., "2s ago")
- **Status Indicator**: Color dot (green/yellow/red)

**Layout**:
- Attached to object via UWidgetComponent
- Always faces player (billboard)
- Minimal size, high contrast text

**Design Notes**:
- Color-coded based on thresholds
- Fade out if data is stale
- Update smoothly (no jittery text)

---

### WID_TelemetryGraph

**Location**: `Content/UI/Widgets/WID_TelemetryGraph.uasset`

**Purpose**: Time-series graph for telemetry data (when object is focused).

**Elements**:
- **Graph Canvas**: Line graph of value over time
  - X-axis: Time (last 5-60 minutes, configurable)
  - Y-axis: Value range (auto-scaled)
- **Legend**:
  - Telemetry key name
  - Current value, min, max, average
- **Threshold Lines**: Horizontal lines for yellow/red thresholds
- **Close Button**

**Layout**:
- Desktop: Overlay panel, medium size
- VR: Floating panel near object

**Design Notes**:
- Smooth line rendering
- Auto-scale Y-axis to data range
- Show gaps for missing data

---

### WID_TelemetryOverlay

**Location**: `Content/UI/Widgets/WID_TelemetryOverlay.uasset`

**Purpose**: Global telemetry dashboard (optional, toggle-able).

**Elements**:
- **Title**: "Homestead Telemetry Dashboard"
- **Telemetry Cards** (grid layout):
  - Each card shows one telemetry source
  - Card elements: label, value, status color, mini-graph
  - Clickable to focus on object or open detailed graph
- **Filter/Sort Options**:
  - Filter by category (Power, IT, Environment, Security)
  - Sort by status (critical first), name, or value
- **Refresh Button**: Manual refresh trigger
- **Close Button**

**Layout**:
- Desktop: Full-screen overlay or side panel
- VR: Large floating panel, paginated if many telemetry sources

**Design Notes**:
- Overview of all telemetry at a glance
- Visual hierarchy: critical alerts stand out
- Not always visible; toggle on/off

---

## Scenario Widgets (Future Phase F)

### WID_ScenarioPanel

**Location**: `Content/UI/Widgets/WID_ScenarioPanel.uasset`

**Purpose**: UI to select and trigger scenario simulations.

**Elements**:
- **Title**: "Scenario Simulations"
- **Scenario List**:
  - Scenario name (e.g., "Power Failure", "Intrusion at North Perimeter")
  - Description (1-2 sentences)
  - Tags (e.g., [Power] [Safety])
  - "Activate" button
- **Active Scenario Info** (if scenario running):
  - Current scenario name
  - Description and objectives
  - Highlighted systems/objects
  - "Reset" button to deactivate scenario
- **Close Button**

**Layout**:
- Desktop: Center overlay or side panel
- VR: Floating panel

**Design Notes**:
- Clear indication of active scenario
- Prevent multiple scenarios from running simultaneously
- Smooth transitions when activating/resetting

**Inputs**:
- Desktop: Mouse click
- VR: Laser pointer + trigger

---

## General Widget Design Guidelines

### Typography
- **Primary Font**: Roboto or similar sans-serif (clean, readable)
- **Font Sizes** (desktop):
  - Headings: 24-32pt
  - Body text: 14-18pt
  - Small text: 10-12pt
- **Font Sizes** (VR):
  - Increase by 1.5-2x for readability at distance
  - Test at target viewing distance (80-120 cm)

### Colors
- **Background**: Dark semi-transparent (e.g., RGBA: 0.1, 0.1, 0.1, 0.8)
- **Text**: Off-white (e.g., RGB: 0.9, 0.9, 0.9)
- **Accent**: Subtle blue or teal (not bright)
- **Status Colors**:
  - Green: RGB: 0.3, 0.8, 0.3
  - Yellow: RGB: 0.9, 0.9, 0.3
  - Red: RGB: 0.9, 0.3, 0.3
- **Avoid**: Pure white, pure black, saturated colors (eye strain)

### Layout
- **Padding**: Generous padding around text (10-20px)
- **Margins**: Consistent margins between elements
- **Alignment**: Left-align body text, center-align headings
- **Hierarchy**: Clear visual hierarchy (size, weight, color)

### Interactions
- **Hover**: Subtle highlight (lighten background or border)
- **Click**: Brief scale animation or color change
- **Disabled**: Desaturated colors, lower opacity

### Accessibility
- **Contrast**: Minimum 4.5:1 contrast ratio for text
- **Focus Indicators**: Clear keyboard/controller focus indicators
- **Text Scaling**: Support for larger text sizes (future)

---

## Implementation Notes

### UMG Best Practices
- Use **Anchors** correctly for responsive layouts
- Use **Size Box** to constrain widget dimensions
- Use **Scale Box** for resolution-independent UI
- Use **Canvas Panel** sparingly; prefer **Vertical/Horizontal Boxes**
- Cache widget references in Blueprint (don't search repeatedly)

### Performance
- Minimize tick rate for UI elements
- Use **Invalidation Boxes** to reduce redraw overhead
- Avoid complex materials on UI elements
- Batch widget updates when possible

### VR-Specific
- Use **Widget Components** for 3D space widgets
- Set **Draw at Desired Size** to true for clarity
- Use **Two-Sided** materials for 3D widgets
- Avoid screen-space widgets entirely
- Test readability at various distances

### Testing Checklist (per widget)
- [ ] Desktop mode: Readable at 1080p, 1440p, 4K
- [ ] Desktop mode: Responsive to different aspect ratios (16:9, 21:9)
- [ ] VR mode: Readable at 80-120 cm distance
- [ ] VR mode: Interactable with laser pointer
- [ ] Keyboard/mouse inputs work correctly
- [ ] VR controller inputs work correctly
- [ ] Animations smooth (60fps minimum)
- [ ] No text truncation or overflow
- [ ] Focus/hover states clear
- [ ] Accessibility: Minimum contrast ratio met

---

## Widget Implementation Roadmap

### Phase A (Bootstrap)
- [ ] WID_HUD_Minimal (basic version)
- [ ] WID_HUD_VR (basic version)

### Phase B (Greybox & Phase System)
- [ ] WID_PhaseSelector

### Phase D (Interaction & Object System)
- [ ] WID_ObjectInfoPanel
- [ ] WID_SOPViewer
- [ ] WID_AnnotationEditor
- [ ] WID_AnnotationDisplay

### Phase F (Telemetry & Scenarios)
- [ ] WID_TelemetryText
- [ ] WID_TelemetryGraph
- [ ] WID_TelemetryOverlay
- [ ] WID_ScenarioPanel

---

**Last Updated**: 2025-11-16
**Related Documents**: `claude.md`, `ROADMAP.md`
