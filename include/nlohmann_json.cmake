add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json SYSTEM INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/nlohmann_json/include
)
