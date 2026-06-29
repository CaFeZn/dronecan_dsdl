# dronecan_dsdl

通用 XRobot/LibXR DroneCAN DSDL facade 模块。

Generic XRobot/LibXR DroneCAN DSDL facade module.

## Scope

`dronecan_dsdl` 作为通用模块仓库，只保存稳定模块入口、XRobot manifest、CMake
接入和生成器约定。具体 DSDL 类型、Topic、回调和编解码头文件由 DroneCAN DSDL
generator 针对使用该模块的项目生成。

As a generic module repository, `dronecan_dsdl` stores only the stable module
entry, XRobot manifest, CMake integration, and generator contract. Concrete DSDL
types, topics, callbacks, and codec headers are emitted by the DroneCAN DSDL
generator for each consuming project.

## Base Node

默认参数只描述基础 DroneCAN 节点实例：

- `node_id`
- `can_alias`
- `timebase_alias`
- `node_name`
- `node_status_period_ms`

这些参数足够让 `dronecan_core` 周期发布 `uavcan.protocol.NodeStatus`，也就是低频
节点健康/模式状态报文。`NodeStatus` 由 `DroneCANNode::Poll()` 发送，不需要作为
生成 DSDL handler 写进本模块仓库。

The default arguments describe only the base DroneCAN node instance. They are
enough for `dronecan_core` to publish `uavcan.protocol.NodeStatus`, the low-rate
node health/mode status message. `NodeStatus` is emitted by
`DroneCANNode::Poll()` and does not need a generated DSDL handler in this module
repository.

## XRobot Manifest

xrobot-org 官方工具从模块同名头文件里的 `MODULE MANIFEST V2` 读取模块元数据。
本模块的权威 manifest 位于 `dronecan_dsdl.hpp`。不要使用 `module.yaml` 作为
XRobot 模块规范文件。

The official xrobot-org tools read module metadata from `MODULE MANIFEST V2` in
the module header with the same name as the module directory. The authoritative
manifest for this module is in `dronecan_dsdl.hpp`. Do not use `module.yaml` as
the XRobot module metadata file.

## Generated Output

`generated/` 是应用项目的生成产物目录，已由本模块的 `.gitignore` 忽略。生成器在
构建前写入这些文件：

- `generated/dronecan_dsdl.hpp`: generated `LibXR::Application` facade
- `generated/dronecan_dsdl_dsdl_detail.hpp`: shared DSDL codec helpers
- `generated/uavcan_*.hpp`: generated DSDL type codecs

`generated/` is application-specific generator output and is ignored by this
module's `.gitignore`. The generator must populate it before firmware build.

## Repository Files

应当保存在通用 module 仓库里的文件：

- `.gitignore`
- `CMakeLists.txt`
- `README.md`
- `dronecan_dsdl.hpp`
- `info.cmake`
- `src/dronecan_dsdl_compile.cpp`

不应当保存在通用 module 仓库里的文件：

- `generated/`
- `module.yaml`
- `User/xrobot.yaml`
- 节点 ID、节点名、灯珠数量等项目参数
- DSDL 类型选择、生成开关和自定义 DSDL 根目录等生成器输入

Files that belong in the generic module repository are the stable integration
files listed above. Generated DSDL output, project configuration, board-specific
runtime values, and generator inputs belong to the consuming project.

## Project Configuration

`User/xrobot.yaml` 只在使用该模块的主工程里存在，用于配置运行时实例参数。例如：

```yaml
modules:
- id: dronecan_dsdl
  name: dronecan_dsdl
  constructor_args:
    node_id: 10
    can_alias: can0
    timebase_alias: timebase
    node_name: org.libxr.dronecan.generated
    node_status_period_ms: 1000
```

`User/xrobot.yaml` belongs to the consuming project and configures runtime
instance arguments only. DSDL type selection is handled by the DroneCAN DSDL
generator configuration or command line, not by the XRobot manifest.

## Generator Contract

生成器负责根据所选 DSDL 类型生成 facade。生成后的 facade 持有一个
`DroneCANCoreSupport::DroneCANNode`，在 `OnMonitor()` 中轮询节点，并为选中的
DSDL 类型暴露类型化 publish、Topic 和接收回调。

The generator creates the facade for the selected DSDL types. The generated
facade owns a `DroneCANCoreSupport::DroneCANNode`, polls it from `OnMonitor()`,
and exposes typed publish APIs, LibXR topics, and receive callbacks for selected
DSDL types.

自定义 DSDL 时，生成器输入应来自项目或生成脚本。例如 `my_company.light.SetColor`
通常来自：

```text
CustomDSDL/
  my_company/
    light/
      20000.SetColor.uavcan
```

示例命令：

```powershell
xr_dronecan_dsdlc generate `
  D:/Path/To/CustomDSDL/my_company `
  --builtin-dsdl `
  --type my_company.light.SetColor `
  --module-name dronecan_dsdl `
  --class-name DroneCANDsdl `
  --root-namespace DroneCANGeneratedDsdl `
  --core-module-id CaFeZn/dronecan_core `
  --output D:/Path/To/Project/Modules/dronecan_dsdl
```
