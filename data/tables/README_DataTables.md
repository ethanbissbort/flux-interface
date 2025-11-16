# Data Tables for Homestead Twin

This directory contains CSV files that can be imported into Unreal Engine as Data Tables.

## Files

### DT_PhaseDefinitions.csv

**Purpose**: Defines the six homestead build-out phases (P0-P5).

**Struct Definition**: `FPhaseDefinition` (defined in `US_HomesteadPhaseManager.h`)

**Import Instructions**:
1. In UE Editor Content Browser: `Content/Data/Tables/`
2. Right-click → Import to `/Game/Data/Tables/`
3. Select `DT_PhaseDefinitions.csv`
4. Choose Data Table asset type
5. Select Row Struct: `PhaseDefinition` (you may need to create this struct in Blueprint first based on C++ definition)
6. Import and save as `DT_PhaseDefinitions`

**Notes**:
- `VisibleObjectTags`: Pipe-separated list (will need manual editing in UE to convert to array)
- `StreamedLevels`: Pipe-separated list (will need manual editing in UE to convert to array)

**Manual Editing Required**:
After import, open the Data Table in UE and convert pipe-separated strings to proper arrays:
- `VisibleObjectTags`: Split "Phase0|RackContainer" → Array of Names: [Phase0, RackContainer]
- `StreamedLevels`: Split "Lvl_Containers|Lvl_RackInterior" → Array of Names: [Lvl_Containers, Lvl_RackInterior]

---

### DT_SOPs.csv

**Purpose**: Defines Standard Operating Procedures linked to homestead objects.

**Struct Definition**: `FStandardOperatingProcedure` (defined in `US_SOPManager.h`)

**Import Instructions**:
1. In UE Editor Content Browser: `Content/Data/Tables/`
2. Right-click → Import to `/Game/Data/Tables/`
3. Select `DT_SOPs.csv`
4. Choose Data Table asset type
5. Select Row Struct: `StandardOperatingProcedure`
6. Import and save as `DT_SOPs`

**Notes**:
- `LinkedObjectIds`: Pipe-separated, convert to array after import
- `Tags`: Pipe-separated, convert to array after import
- `Steps`: **NOT INCLUDED IN CSV** — too complex for CSV format

**Adding SOP Steps**:

The `Steps` field (array of `FSOPStep` structs) must be added manually in UE after import.

For each SOP, open the Data Table and add steps using this template:

#### SOP_POWER_DOWN_RACK_01 Steps:

1. **Step 1**: "Notify users of impending shutdown via email/Slack"
   - Warning: "Ensure 30-minute advance notice for graceful shutdowns"
   - Duration: 120 seconds

2. **Step 2**: "Initiate graceful shutdown of all VMs and services"
   - Warning: ""
   - Duration: 300 seconds

3. **Step 3**: "Wait for all services to report shutdown complete"
   - Warning: "Verify service status before proceeding"
   - Duration: 180 seconds

4. **Step 4**: "Shutdown network switches and routers"
   - Warning: ""
   - Duration: 60 seconds

5. **Step 5**: "Power down main rack servers in reverse boot order"
   - Warning: "Never hard power-off without graceful OS shutdown first"
   - Duration: 120 seconds

6. **Step 6**: "Disconnect UPS from load"
   - Warning: "Verify all equipment powered down before disconnecting UPS"
   - Duration: 60 seconds

7. **Step 7**: "Document shutdown in maintenance log"
   - Warning: ""
   - Duration: 60 seconds

**Total Estimated Time**: 900 seconds (15 minutes)

---

#### SOP_POWER_UP_RACK_01 Steps:

1. **Step 1**: "Verify UPS battery charge level (>80%)"
   - Warning: "Do not proceed if UPS SOC < 80% without generator backup"
   - Duration: 30 seconds

2. **Step 2**: "Connect UPS to load"
   - Warning: ""
   - Duration: 30 seconds

3. **Step 3**: "Power up network core switch"
   - Warning: ""
   - Duration: 60 seconds

4. **Step 4**: "Power up main rack servers in boot order"
   - Warning: "Wait 30 seconds between server power-ups to avoid current surge"
   - Duration: 180 seconds

5. **Step 5**: "Verify network connectivity and routing"
   - Warning: ""
   - Duration: 120 seconds

6. **Step 6**: "Start VM host services"
   - Warning: ""
   - Duration: 120 seconds

7. **Step 7**: "Verify all critical services online"
   - Warning: "Check monitoring dashboard for service health"
   - Duration: 60 seconds

**Total Estimated Time**: 600 seconds (10 minutes)

---

#### SOP_GENERATOR_STARTUP Steps:

1. **Step 1**: "Perform visual inspection of generator"
   - Warning: "Check for fuel leaks, loose connections, or damage"
   - Duration: 120 seconds

2. **Step 2**: "Check generator fuel level"
   - Warning: "Do not start generator if fuel level < 50%"
   - Duration: 60 seconds

3. **Step 3**: "Check generator oil level"
   - Warning: "Low oil can cause engine damage"
   - Duration: 60 seconds

4. **Step 4**: "Ensure transfer switch in OFF position"
   - Warning: "Never backfeed utility grid"
   - Duration: 30 seconds

5. **Step 5**: "Start generator and let warm up for 3 minutes"
   - Warning: "Do not load generator during warm-up period"
   - Duration: 180 seconds

6. **Step 6**: "Verify generator voltage and frequency"
   - Warning: "Must be 120V ±5%, 60Hz ±0.5Hz"
   - Duration: 60 seconds

7. **Step 7**: "Switch transfer switch to GENERATOR position"
   - Warning: "Ensure smooth transfer, monitor for voltage spikes"
   - Duration: 60 seconds

8. **Step 8**: "Verify load transfer and generator stability"
   - Warning: "Do not exceed 80% generator capacity"
   - Duration: 120 seconds

9. **Step 9**: "Set Aircela to run-time limited mode (generator efficiency)"
   - Warning: "Aircela draws significant current; manage runtime"
   - Duration: 60 seconds

10. **Step 10**: "Document generator start in maintenance log"
    - Warning: ""
    - Duration: 60 seconds

**Total Estimated Time**: 1200 seconds (20 minutes)

---

## Creating Data Table Structs in UE

If the C++ structs (`FPhaseDefinition`, `FStandardOperatingProcedure`) are not recognized during CSV import, you may need to:

### Option 1: Use C++ Structs (Recommended)

1. Ensure project compiles successfully with C++ headers
2. Restart UE Editor
3. Structs should appear in "Struct" dropdown during Data Table import

### Option 2: Create Blueprint Structs

If C++ structs are not available:

1. **Content Browser** → Right-click → **Blueprints** → **Structure**
2. Name: `BP_PhaseDefinition`
3. Add variables matching C++ struct:
   - `Phase` (EHomesteadPhase enum — you may need to create enum first)
   - `PhaseName` (String)
   - `Description` (String)
   - `VisibleObjectTags` (Array of Names)
   - `StreamedLevels` (Array of Names)
4. Save struct
5. Repeat for `BP_StandardOperatingProcedure` and `BP_SOPStep`

### Creating Enums

**EHomesteadPhase enum**:
1. Right-click → **Blueprints** → **Enumeration**
2. Name: `EHomesteadPhase`
3. Add enumerators:
   - `Phase0` (Display Name: "Phase 0 - Minimal Containers")
   - `Phase1` (Display Name: "Phase 1 - Workshop & Rack")
   - `Phase2` (Display Name: "Phase 2 - Tiny Home & Orchard")
   - `Phase3` (Display Name: "Phase 3 - Greenhouse & Swales")
   - `Phase4` (Display Name: "Phase 4 - Perimeter & Deterrence")
   - `Phase5` (Display Name: "Phase 5 - Full Build-out")
4. Save

---

## Using Data Tables in Blueprints

### Phase Manager Example

In `BP_US_HomesteadPhaseManager`:

1. **Class Defaults**:
   - Set **Phase Data Table** variable to `DT_PhaseDefinitions`

2. **Initialize() function**:
   - Load rows from `PhaseDataTable` using **Get Data Table Row Names**
   - For each row, call **Get Data Table Row**
   - Store in `PhaseDefinitions` array

3. **SetCurrentPhase() function**:
   - Query `PhaseDefinitions` array for selected phase
   - Apply visibility based on `VisibleObjectTags`
   - Stream in/out levels based on `StreamedLevels`

### SOP Manager Example

In `BP_US_SOPManager`:

1. **Class Defaults**:
   - Set **SOP Data Table** variable to `DT_SOPs`

2. **LoadSOPData() function**:
   - Load rows from `SOPDataTable`
   - Store in `SOPDatabase` map (SOPId → SOP struct)

3. **GetSOPsForObject() function**:
   - Iterate through `SOPDatabase`
   - Filter where `LinkedObjectIds` contains the queried ObjectId
   - Return matching SOPs

---

## Future Data Tables

As you progress through phases, create additional data tables:

- **DT_ScenarioDefinitions**: Scenario simulations (Phase F)
- **DT_TelemetryEndpoints**: Telemetry data sources (Phase F)
- **DT_AnnotationCategories**: Predefined annotation categories (Phase D)

---

## Notes

- CSV files use pipe (`|`) as array separator because commas are the CSV delimiter
- After import, you'll need to manually convert pipe-separated strings to proper arrays in UE
- Consider writing a custom CSV importer Blueprint utility if you have many complex data tables
- Keep CSV files in version control; they're text-based and diff-friendly

---

**Last Updated**: 2025-11-16
**Related**: `US_HomesteadPhaseManager.h`, `US_SOPManager.h`, `phase_a_blueprint_guide.md`
