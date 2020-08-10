#cmake_minimum_required(VERSION 3.10)

#project(simCenterDprepro_proj)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(SOURCES simCenterDprepro.cpp)

#add_executable(simCenterDprepro ${SOURCES})

#install(TARGETS simCenterDprepro DESTINATION bin)

#add_executable(NAME simCenterDprepro
#               FILES simCenterDprepro.cpp)

cmake_minimum_required(VERSION 2.4)

project(simCenterDprepro.cpp)

add_executable(simCenterDprepro simCenterDprepro.cpp)