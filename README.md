# dronecan_dsdl

已生成的 XRobot/LibXR DroneCAN 模块。

Generated XRobot/LibXR DroneCAN module.

## DSDL 类型 / DSDL Types

- `uavcan.equipment.esc.RawCommand`
- `uavcan.equipment.esc.Status`
- `uavcan.protocol.dynamic_node_id.Allocation`

## 模块布局 / Module Layout

- `dronecan_dsdl.hpp`: 稳定 XRobot 模块入口，只转发到 `generated/dronecan_dsdl.hpp`。
- `dronecan_dsdl.hpp`: stable XRobot module entry that forwards to `generated/dronecan_dsdl.hpp`.
- `generated/dronecan_dsdl.hpp`: 生成的 XRobot Application facade，包含 manifest、模块运行逻辑和 using 别名。
- `generated/dronecan_dsdl.hpp`: generated XRobot Application facade with manifest, runtime logic, and using aliases.
- `generated/dronecan_dsdl_dsdl_detail.hpp`: DSDL 编解码公共 helper。
- `generated/dronecan_dsdl_dsdl_detail.hpp`: shared helpers for generated DSDL codecs.

## DSDL Headers

- `uavcan_equipment_esc_raw_command.hpp`: `uavcan.equipment.esc.RawCommand`
- `uavcan_equipment_esc_status.hpp`: `uavcan.equipment.esc.Status`
- `uavcan_protocol_dynamic_node_id_allocation.hpp`: `uavcan.protocol.dynamic_node_id.Allocation`

`module.yaml` 的 `dsdl` 列表只记录 `type`；生成头文件名由 DSDL 类型名按约定自动推导。
所有生成产物都在 `generated/` 子目录。

The `dsdl` list in `module.yaml` records only `type`; generated header names are
derived from DSDL type names by convention. All generated artifacts are kept
under the `generated/` subdirectory.

## XRobot 实例化示例 / XRobot Instantiation Example

在 `User/xrobot.yaml` 中实例化生成的 facade；`dronecan_core` 作为依赖由构建系统加入，不需要在这里单独实例化。

Instantiate the generated facade in `User/xrobot.yaml`. `dronecan_core` is added
as a dependency by the build and does not need a separate entry here.

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

## 自定义 DSDL / Custom DSDL

自定义 DSDL 时，把 DSDL 根命名空间目录作为 `generate` 的位置参数。
例如 `my_company.actuator.MyCommand` 对应的源文件通常放在：

```text
CustomDSDL/
  my_company/
    actuator/
      20000.MyCommand.uavcan
```

命令中应传入 `CustomDSDL/my_company`，并用 `--type my_company.actuator.MyCommand`
指定要生成的类型。如果自定义类型引用标准 `uavcan.*` 类型，保留 `--builtin-dsdl`。
如果有额外只用于依赖解析的 DSDL 根目录，可用 `-I` / `--lookup-dir` 添加。

```powershell
xr_dronecan_dsdlc generate `
  D:/Path/To/CustomDSDL/my_company `
  --builtin-dsdl `
  --type my_company.actuator.MyCommand `
  --module-name dronecan_dsdl `
  --class-name DroneCANDsdl `
  --root-namespace DroneCANGeneratedDsdl `
  --core-module-id CaFeZn/dronecan_core `
  --output D:/Codes/DroneCAN/dronecan_dsdl
```

For custom DSDL, pass the root namespace directory to `generate`. The directory
above is passed as `CustomDSDL/my_company`, while the type is selected with
`--type my_company.actuator.MyCommand`. Keep `--builtin-dsdl` when standard
`uavcan.*` dependencies are referenced, and use `-I` / `--lookup-dir` for extra
dependency-only DSDL roots.

该模块持有一个 `DroneCANCoreSupport::DroneCANNode`，通过 `OnMonitor()` 轮询，
并暴露类型化的发布、请求、响应方法，以及可选的接收传输回调。

The module owns a `DroneCANCoreSupport::DroneCANNode`, polls it from
`OnMonitor()`, and exposes typed publish/request/respond methods plus optional
callbacks for received transfers.

## LibXR Topic 同步发布 / LibXR Topic Publishing

每条已解码的 DroneCAN 消息会同步发布到对应的 RX LibXR Topic。向 TX Topic
发布同类型数据时，facade 会调用对应的 DroneCAN 类型化发布接口。Topic 数据
类型为 `LibXR::DroneCAN::TopicMessage<T>`，其中 `metadata` 保存传输元数据，
`message` 保存已解码的 DSDL 消息对象；TX Topic 使用 `metadata.priority`
作为发送优先级。

Each decoded DroneCAN message is synchronously published to its RX LibXR Topic.
Publishing the same payload type to a TX Topic makes the facade call the typed
DroneCAN publish API. The topic payload type is
`LibXR::DroneCAN::TopicMessage<T>`, where `metadata` contains the transfer
metadata and `message` contains the decoded DSDL object; TX Topics use
`metadata.priority` as the transfer priority.

| DSDL 类型 / DSDL type | RX Topic | TX Topic |
| --- | --- | --- |
| `uavcan.equipment.esc.RawCommand` | `/dronecan/uavcan/equipment/esc/RawCommand` | `/dronecan/tx/uavcan/equipment/esc/RawCommand` |
| `uavcan.equipment.esc.Status` | `/dronecan/uavcan/equipment/esc/Status` | `/dronecan/tx/uavcan/equipment/esc/Status` |
| `uavcan.protocol.dynamic_node_id.Allocation` | `/dronecan/uavcan/protocol/dynamic_node_id/Allocation` | `/dronecan/tx/uavcan/protocol/dynamic_node_id/Allocation` |
