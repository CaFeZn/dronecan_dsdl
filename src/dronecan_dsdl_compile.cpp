#include "dronecan_dsdl.hpp"

/**
 * @brief Compile-time integration sentinel for the generated DroneCAN facade.
 * @brief 生成 DroneCAN facade 的编译期接入哨兵。
 *
 * This translation unit intentionally contains no runtime logic. It makes the
 * header-only DSDL module participate in normal firmware builds so interface
 * drift against libxr or dronecan_core fails at compile time.
 *
 * 本文件不包含运行时代码，仅用于让 header-only DSDL 模块参与固件构建；
 * 如果 libxr 或 dronecan_core 接口漂移，常规编译即可发现问题。
 */
