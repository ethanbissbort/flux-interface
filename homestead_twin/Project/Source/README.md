# Homestead Twin C++ Source Files

This directory contains C++ header stub files for the Homestead Twin Unreal Engine project.

## Purpose

These stub files define the class structure and API for core framework classes, subsystems, actors, and components. They serve as:

1. **Documentation**: Each class is thoroughly documented with responsibilities and implementation notes
2. **Blueprint base classes**: These C++ classes can be extended in Blueprints
3. **API reference**: Defines the public interface for each system
4. **Development guide**: Shows what needs to be implemented in each phase

## Current Status

**All files are STUBS** — they define the interface but do not contain implementation (`.cpp` files).

For Phase A (Bootstrap), you can choose to:
- **Implement in Blueprints**: Extend these classes in Blueprint (recommended for rapid prototyping)
- **Implement in C++**: Add corresponding `.cpp` files with implementation (for performance-critical code)

## Directory Structure

```
Source/
├── HomesteadTwin/
│   ├── Core/                 # Core framework classes
│   │   ├── GI_HomesteadTwin.h
│   │   ├── GM_HomesteadTwin.h
│   │   ├── PC_Desktop.h
│   │   ├── PC_VR.h
│   │   ├── Pawn_Desktop.h
│   │   └── Pawn_VR.h
│   ├── Subsystems/           # Game Instance Subsystems
│   │   ├── US_HomesteadPhaseManager.h
│   │   ├── US_SOPManager.h
│   │   ├── US_AnnotationManager.h
│   │   ├── US_TelemetryManager.h (future)
│   │   └── US_ScenarioManager.h (future)
│   ├── Actors/               # Actor classes
│   │   ├── A_HomesteadObject.h
│   │   └── A_Annotation.h
│   ├── Components/           # Component classes
│   │   ├── U_InteractableComponent.h
│   │   ├── U_SOPComponent.h
│   │   └── U_TelemetryComponent.h (future)
│   ├── HomesteadTwin.Build.cs
│   ├── HomesteadTwin.h
│   └── README.md (this file)
└── HomesteadTwinEditor/      (optional, for editor extensions)
```

## Compilation

### Prerequisites

- Unreal Engine 5.3 or later installed
- Visual Studio 2022 (Windows) or Xcode (Mac)
- C++ development tools

### Generate Project Files

From the `homestead_twin/Project/` directory:

**Windows**:
```bash
# Right-click on HomesteadTwin.uproject → "Generate Visual Studio project files"
# Or use command line:
"%UE5_PATH%\Engine\Build\BatchFiles\Build.bat" HomesteadTwinEditor Win64 Development -Project="C:\path\to\HomesteadTwin.uproject" -WaitMutex -FromMsBuild
```

**Mac**:
```bash
# Right-click on HomesteadTwin.uproject → "Generate Xcode project files"
```

### Build

**Option 1: Build from Unreal Editor**
1. Open `HomesteadTwin.uproject` in Unreal Editor
2. If prompted to rebuild, click "Yes"
3. Editor will compile C++ code automatically

**Option 2: Build from IDE**
1. Open generated `.sln` (Visual Studio) or `.xcworkspace` (Xcode)
2. Set configuration to "Development Editor"
3. Build the solution
4. Launch editor from IDE or open `.uproject`

**Option 3: Build from command line**

Windows:
```bash
"%UE5_PATH%\Engine\Build\BatchFiles\Build.bat" HomesteadTwinEditor Win64 Development -Project="C:\path\to\HomesteadTwin.uproject"
```

Mac/Linux:
```bash
$UE5_PATH/Engine/Build/BatchFiles/Mac/Build.sh HomesteadTwinEditor Mac Development -Project="/path/to/HomesteadTwin.uproject"
```

## Implementation Approaches

### Approach 1: Pure Blueprint (Recommended for Phase A)

**Pros**: Fast iteration, no compilation, visual scripting
**Cons**: Less performant for complex logic, harder to version control

**Steps**:
1. Open UE Editor
2. Create Blueprint class extending C++ base (e.g., `BP_GI_HomesteadTwin` extends `UGI_HomesteadTwin`)
3. Implement Blueprint events (marked `BlueprintImplementableEvent` in headers)
4. Override functions in Blueprint
5. Assign Blueprint classes in project settings/game mode

### Approach 2: C++ Implementation

**Pros**: Better performance, type safety, version control friendly
**Cons**: Slower iteration (requires compilation)

**Steps**:
1. Create corresponding `.cpp` file for each `.h` stub
2. Implement virtual functions and logic
3. Compile project
4. Use C++ classes directly or extend in Blueprint

### Approach 3: Hybrid (Recommended for Production)

**Pros**: Best of both worlds
**Cons**: Requires understanding both systems

**Strategy**:
- **C++**: Core logic, data structures, performance-critical code
- **Blueprint**: UI, gameplay scripting, content-specific logic
- Use `BlueprintCallable` functions to expose C++ to Blueprints
- Use `BlueprintImplementableEvent` for Blueprint hooks

## Header File Guide

### Reading the Headers

Each header contains:

1. **Copyright notice**: Standard Fluxology copyright
2. **Class documentation**: `/** */` block describing purpose and responsibilities
3. **Public API**: Functions marked `UFUNCTION(BlueprintCallable/BlueprintPure)`
4. **Blueprint events**: Functions marked `BlueprintImplementableEvent`
5. **Properties**: Variables marked `UPROPERTY()` with access specifiers

### Key UFUNCTION Specifiers

- `BlueprintCallable`: Can be called from Blueprints
- `BlueprintPure`: Blueprint function with no side effects (const)
- `BlueprintImplementableEvent`: Implemented in Blueprint, called from C++
- `BlueprintNativeEvent`: Can be implemented in Blueprint or C++ (with `_Implementation` suffix)

### Key UPROPERTY Specifiers

- `EditAnywhere`: Editable in editor (details panel and Blueprint defaults)
- `BlueprintReadWrite`: Readable and writable from Blueprints
- `BlueprintReadOnly`: Readable but not writable from Blueprints
- `VisibleAnywhere`: Visible in editor but not editable

## Next Steps

### Phase A: Bootstrap & Foundation

1. **Create Blueprint classes** extending these C++ stubs:
   - `BP_GI_HomesteadTwin` (extends `UGI_HomesteadTwin`)
   - `BP_GM_HomesteadTwin` (extends `AGM_HomesteadTwin`)
   - `BP_PC_Desktop` (extends `APC_Desktop`)
   - `BP_PC_VR` (extends `APC_VR`)
   - `BP_Pawn_Desktop` (extends `APawn_Desktop`)
   - `BP_Pawn_VR` (extends `APawn_VR`)

2. **Configure Project Settings**:
   - Set `BP_GI_HomesteadTwin` as Game Instance class
   - Set `BP_GM_HomesteadTwin` as default Game Mode
   - Assign player controller and pawn classes

3. **Implement basic functionality**:
   - Desktop: WASD movement, mouse look, interaction raycast
   - VR: Teleport locomotion, motion controller setup, laser pointer

4. **Test**:
   - Launch in editor (desktop mode)
   - Launch in VR preview mode
   - Verify basic navigation works

### Future Phases

- **Phase B**: Implement Phase Manager subsystem
- **Phase D**: Implement interaction system and SOP manager
- **Phase F**: Implement telemetry and scenario managers

Refer to `ROADMAP.md` for detailed phase breakdown.

## Troubleshooting

### Compilation Errors

**Problem**: "Cannot open include file: '...'"
- **Solution**: Verify `HomesteadTwin.Build.cs` includes required modules
- Check that module dependencies are correct

**Problem**: "Unresolved external symbol"
- **Solution**: Add `.cpp` file with implementation, or use Blueprint implementation

### Runtime Errors

**Problem**: "Class not found"
- **Solution**: Ensure Blueprint classes are created and assigned in project settings

**Problem**: "Subsystem not initialized"
- **Solution**: Verify subsystem is registered in `GI_HomesteadTwin::Init()`

## Additional Resources

- **Unreal Engine C++ Documentation**: https://docs.unrealengine.com/5.3/en-US/ProgrammingAndScripting/
- **Subsystems Guide**: https://docs.unrealengine.com/5.3/en-US/programming-subsystems-in-unreal-engine/
- **Blueprint vs C++**: https://docs.unrealengine.com/5.3/en-US/blueprints-visual-scripting-in-unreal-engine/

## Notes

- All header files are thoroughly documented inline
- Follow naming conventions: C++ prefix (U/A/F/E) + descriptive name
- Prefer composition (components) over inheritance where possible
- Keep subsystems lightweight; delegate to actors/components for heavy logic

---

**Last Updated**: 2025-11-16
**Related Documents**: `../../docs/claude.md`, `../../ROADMAP.md`
