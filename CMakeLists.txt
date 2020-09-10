cmake_minimum_required(VERSION 3.10)

project(nataf_gsa_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib_mat)

include_directories(lib_json lib_mat ${PROJECT_SOURCE_DIR})
set(SOURCES main.cpp my_gsa.cpp my_nataf.cpp my_readjson.cpp)
add_executable(nataf_gsa ${SOURCES})
target_link_libraries(nataf_gsa libmat)

install(TARGETS nataf_gsa DESTINATION bin)
