cmake_minimum_required(VERSION 3.5)
project(cpp_mock_scenarios)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake_auto REQUIRED)
include(FindProtobuf REQUIRED)

ament_auto_find_build_dependencies()

ament_auto_add_library(cpp_scenario_node
  src/cpp_scenario_node.cpp
)
target_link_libraries(cpp_scenario_node
  ${PROTOBUF_LIBRARY}
  pthread
  sodium
  zmqpp
  zmq
)

ament_auto_add_executable(traffic_simulation_demo
  src/traffic_simulation_demo.cpp
)
target_link_libraries(traffic_simulation_demo cpp_scenario_node)

add_subdirectory(src/follow_front_entity)
add_subdirectory(src/collision)
add_subdirectory(src/lane_change)
add_subdirectory(src/merge)

install(
  DIRECTORY launch rviz
  DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()

