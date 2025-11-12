add_library(jsoncons INTERFACE)

target_include_directories(jsoncons SYSTEM INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/jsoncons/include
)
