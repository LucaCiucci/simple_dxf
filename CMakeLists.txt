
cmake_minimum_required(VERSION 3.20)

project(simple_dxf)

set(SIMPLE_DXF_MAIN_PROJECT OFF)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(SIMPLE_DXF_MAIN_PROJECT ON)
endif()

add_library(simple_dxf STATIC)

target_sources(
	simple_dxf
	PRIVATE
		src/dxf.cpp
)
target_include_directories(
	simple_dxf
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

set(SIMPLE_PDF_DXFPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/DxfPlate)

if(SIMPLE_DXF_MAIN_PROJECT)
message(STATUS "Building simple_dxf examples")
	add_subdirectory(examples)
endif()