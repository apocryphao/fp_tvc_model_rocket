cmake_minimum_required(VERSION 3.28)

project(fp_software)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(control src/controller.cpp)
add_library(state src/state_estimator.cpp)

target_link_libraries(${PROJECT_NAME} control state)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/eigen-5.0.0)
target_include_directories(control PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/eigen-5.0.0)
target_include_directories(state PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/eigen-5.0.0)
