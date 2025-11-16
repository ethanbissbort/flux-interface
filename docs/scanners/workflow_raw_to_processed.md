# Workflow: Raw Scan to Processed Assets

## Directory Structure

- Raw scans:
  - `data/scans/raw/<area>/YYYY-MM-DD_area_detail_vN/`
- Processed for Unreal:
  - `data/scans/processed/for_ue5/<area>/area_detail_1to1_vN.fbx`
- Processed for CAD/printing:
  - `data/scans/processed/for_cad/<category>/object_1to1_vN.(stl|step)`

## Steps

1. Capture raw data with the handheld scanner.
2. Clean, align, and decimate in vendor software (or Blender/MeshLab).
3. Export:
   - FBX/OBJ for Unreal Engine.
   - STL/STEP for CAD/printing.
4. Place processed files into the appropriate `processed` folders.
5. Import FBX into Unreal under `Content/Scans/...`.
