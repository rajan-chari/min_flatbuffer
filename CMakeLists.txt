cmake_minimum_required(VERSION 3.0)
project(MyProject)
# Find the FlatBuffers package
find_package(flatbuffers REQUIRED)
# Add a custom command to generate code from the FlatBuffers schema
add_custom_command(
    OUTPUT generated_orange.h
    COMMAND ${FLATBUFFERS_COMPILER} -o ${CMAKE_CURRENT_SOURCE_DIR} --cpp ${CMAKE_CURRENT_SOURCE_DIR}/orange.fbs
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/orange.fbs
    COMMENT "Generating C++ code from FlatBuffers schema"
)
# Add the main executable
add_executable(MyExecutable main.cpp)
# Link the main executable with the generated code and FlatBuffers libraries
target_link_libraries(MyExecutable PRIVATE flatbuffers::flatbuffers)