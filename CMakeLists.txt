cmake_minimum_required(VERSION 3.10)

project(SH_ALG VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable( SH_ALG ${PROJECT_SOURCE_DIR}/example.cc )

target_include_directories( 	SH_ALG PUBLIC
								"${PROJECT_SOURCE_DIR}/include" )
