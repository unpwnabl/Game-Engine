cmake_minimum_required(VERSION 3.10)
project(GameEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES platform/linux/game.cpp core/ui/window.cpp core/ui/renderer.cpp core/ui/text.cpp core/ui/font_paths.cpp src/2d/image.cpp src/2d/spritesheet.cpp src/misc/gameobj.cpp src/misc/resources.cpp src/misc/rigidbody.cpp src/2d/button.cpp src/2d/vector2d.cpp src/3d/vector3d.cpp core/misc/log.cpp core/misc/colors.cpp core/misc/split.cpp core/misc/fps.cpp core/misc/interpolation.cpp core/misc/mouse.cpp core/misc/events.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE core/ui/include PRIVATE core/misc/include PRIVATE platform/linux PRIVATE src/2d/include PRIVATE src/3d/include PRIVATE src/misc/include)

# Imposes SDL2 as required
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 PRIVATE SDL2_ttf::SDL2_ttf PRIVATE SDL2_image::SDL2_image)

#target_compile_options(${PROJECT_NAME} PRIVATE -Wreturn-type -Wconversion-null)

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

# Run
add_custom_target(run 
	COMMAND ${PROJECT_NAME} 
	DEPENDS ${PROJECT_NAME} 
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# Create an outside folder to run exe whenever
set(DIST_DIR "${CMAKE_SOURCE_DIR}/dist")

add_custom_target(bundle
    COMMENT "Creating distributable bundle in ${DIST_DIR}"
)

add_custom_command(TARGET bundle PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${DIST_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "${DIST_DIR}"
    COMMENT "Copying executable to ${DIST_DIR}"
)

add_custom_command(TARGET bundle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/thirdparty/Roboto/static"
        "${DIST_DIR}/static"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/core/imgs"
        "${DIST_DIR}/imgs"
    COMMENT "Copying asset directories to ${DIST_DIR}"
)

if(TARGET SDL2::SDL2)
    add_custom_command(TARGET bundle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2::SDL2> "${DIST_DIR}"
        COMMENT "Copying SDL2 runtime to ${DIST_DIR}"
    )
endif()

if(TARGET SDL2_ttf::SDL2_ttf)
    add_custom_command(TARGET bundle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2_ttf::SDL2_ttf> "${DIST_DIR}"
        COMMENT "Copying SDL2_ttf runtime to ${DIST_DIR}"
    )
endif()

if(TARGET SDL2_image::SDL2_image)
    add_custom_command(TARGET bundle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SDL2_image::SDL2_image> "${DIST_DIR}"
        COMMENT "Copying SDL2_image runtime to ${DIST_DIR}"
    )
endif()

add_dependencies(bundle ${PROJECT_NAME})

# Clean extra stuff
add_custom_target(extra_clean 
	COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/logs 
	COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/*.tmp 
	COMMENT "Removing logs and temporary files...")
