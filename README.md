# flux-interface

A single-user Unreal Engine 5.x interface for the Fluxology Homestead — a 3D/VR "digital twin" of the property, containers, infrastructure, and tech stack.

## Structure

- `homestead_twin/` – Unreal Engine 5.x project for the Digital Homestead Twin.
- `data/` – 3D scan inputs/outputs, CAD models, textures, exports.
- `docs/` – Design documents, SOPs, telemetry specs.
- `tools/` – Helper scripts and workflows (Blender, mesh processing, etc.).

## Getting Started

1. Install Unreal Engine 5.x (matching the version you will use for `HomesteadTwin`).
2. Clone the repo:
   ```bash
   git clone https://github.com/ethanbissbort/flux-interface.git
   cd flux-interface
   ```
3. Open `homestead_twin/Project/HomesteadTwin.uproject` in Unreal once it has been created via the editor.
4. Build and run.

## Notes

- This repository is primarily for internal Fluxology use.
- Raw 3D scan data can be very large; by default, `data/scans/raw` is ignored by Git.
