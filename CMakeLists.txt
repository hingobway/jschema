cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(jschema)

add_executable(app)

include(include/nlohmann_json.cmake)
include(include/jsoncons.cmake)

target_sources(app PRIVATE
  src/main.cpp
)

target_link_libraries(app PRIVATE
  nlohmann_json
  jsoncons
)
