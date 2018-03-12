cmake_minimum_required(VERSION 2.8)

project(squares)
file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} -lsfml-graphics -lsfml-window -lsfml-system)
