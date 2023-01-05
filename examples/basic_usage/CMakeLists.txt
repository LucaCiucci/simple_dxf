

add_executable(example_basic_usage main.cpp)

target_link_libraries(example_basic_usage PRIVATE simple_dxf)

add_custom_command(TARGET example_basic_usage POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${SIMPLE_PDF_DXFPLATE_DIR} $<TARGET_FILE_DIR:example_basic_usage>/DxfPlate/
)