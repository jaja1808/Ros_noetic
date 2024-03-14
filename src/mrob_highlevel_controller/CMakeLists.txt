cmake_minimum_required(VERSION 3.0.2)
project(mrob_highlevel_controller)

add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp  sensor_msgs  geometry_msgs  visualization_msgs std_srvs
)
find_package(Eigen3 REQUIRED)

catkin_package(
 INCLUDE_DIRS include ${EIGEN3_INCLUDE_DIR}
 LIBRARIES mrob_highlevel_controller
 CATKIN_DEPENDS roscpp
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)
# adding the Libraries used in my nodes
add_library(${PROJECT_NAME}_core
  src/HighlevelController.cpp
  src/SetBoolClient.cpp
  src/ImuClient.cpp
)

add_dependencies(${PROJECT_NAME}_core ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# adding executables for my cpp files
add_executable(${PROJECT_NAME}_node src/node.cpp)
add_executable(${PROJECT_NAME}_service1 src/Service.cpp)
add_executable(${PROJECT_NAME}_service2 src/imuNode.cpp)

# adding the target executable names for the nodes
set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME controller PREFIX "")
set_target_properties(${PROJECT_NAME}_service1 PROPERTIES OUTPUT_NAME vel_command PREFIX "")
set_target_properties(${PROJECT_NAME}_service2 PROPERTIES OUTPUT_NAME imu_based_command PREFIX "")

add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# target libraries 
target_link_libraries(${PROJECT_NAME}_core ${catkin_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_node ${PROJECT_NAME}_core)
target_link_libraries(${PROJECT_NAME}_service1 ${PROJECT_NAME}_core)
target_link_libraries(${PROJECT_NAME}_service2 ${PROJECT_NAME}_core)