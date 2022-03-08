cmake_minimum_required(VERSION 3.0.0)
project(VD_NEW VERSION 0.1.0)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

include(CTest)
enable_testing()

include_directories(include)
include_directories(VUFS/include)

get_filename_component(src_path src ABSOLUTE)
file(GLOB src_file ${src_path}/*.cpp)
add_executable(${PROJECT_NAME} ${src_file})




# get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
# foreach(dir ${dirs})
#   message(STATUS "dir='${dir}'")
# endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE "include;")
target_link_libraries(${PROJECT_NAME} debug ${CMAKE_SOURCE_DIR}/VUFS/lib/x64/Debug/VUFS.lib)
target_link_libraries(${PROJECT_NAME} optimized ${CMAKE_SOURCE_DIR}/VUFS/lib/x64/Release/VUFS.lib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)