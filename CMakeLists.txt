cmake_minimum_required(VERSION 3.10)
project(GameEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES platform/linux/game.cpp core/ui/window.cpp core/ui/renderer.cpp core/ui/text.cpp core/ui/font_paths.cpp src/2d/image.cpp core/misc/log.cpp core/misc/colors.cpp core/misc/split.cpp core/misc/fps.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE core/ui/include core/misc/include PRIVATE platform/linux PRIVATE src/2d/include PRIVATE src/3d/include)

# Imposes SDL2 as required
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 PRIVATE SDL2_ttf::SDL2_ttf PRIVATE SDL2_image::SDL2_image)

#target_compile_options(${PROJECT_NAME} PRIVATE -w)

# Add the font files to the build directory
add_custom_command(TARGET  ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/thirdparty/Roboto/static
	$<TARGET_FILE_DIR:${PROJECT_NAME}>/static
	COMMENT "Copying font assets to build output folder..."
)

# Add the image files to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/core/imgs
	$<TARGET_FILE_DIR:${PROJECT_NAME}>/imgs
	COMMENT "Copying imgs assets to build output folder..."
)

add_custom_target(run 
	COMMAND ${PROJECT_NAME} 
	DEPENDS ${PROJECT_NAME} 
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_custom_target(extra_clean 
	COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/logs 
	COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/*.tmp 
	COMMENT "Removing logs and temporary files...")
