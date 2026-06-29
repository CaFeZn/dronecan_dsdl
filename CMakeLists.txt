target_include_directories(xr PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/generated
)

target_sources(xr PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/dronecan_dsdl_compile.cpp
)
