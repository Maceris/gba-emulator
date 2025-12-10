# Interface

SET(INTERFACE_SOURCE_DIR ${INTERFACE_DIR}/src)
SET(INTERFACE_TEST_DIR ${INTERFACE_DIR}/test)
SET(IMGUI_PATH ${THIRD_PARTY_DIR}/imgui)
SET(GLFW_PATH ${THIRD_PARTY_DIR}/glfw)

SET(HEADER_FILES
  ${INTERFACE_HEADER_DIR}/brain/brain.h
  ${INTERFACE_HEADER_DIR}/brain/commands.h
  ${INTERFACE_HEADER_DIR}/brain/command_queue.h
  ${INTERFACE_HEADER_DIR}/brain/key_mapping.h
  ${INTERFACE_HEADER_DIR}/gui/gui.h
  ${INTERFACE_HEADER_DIR}/gui/key_binding.h
  ${INTERFACE_HEADER_DIR}/gui/settings.h
  ${INTERFACE_HEADER_DIR}/rendering/command_buffer.h
  ${INTERFACE_HEADER_DIR}/rendering/device.h
  ${INTERFACE_HEADER_DIR}/rendering/instance.h
  ${INTERFACE_HEADER_DIR}/rendering/pipeline.h
  ${INTERFACE_HEADER_DIR}/rendering/render.h
  ${INTERFACE_HEADER_DIR}/rendering/render_state.h
  ${INTERFACE_HEADER_DIR}/rendering/shader.h
  ${INTERFACE_HEADER_DIR}/rendering/swap_chain.h
  ${INTERFACE_HEADER_DIR}/rendering/window.h
)

SET(THIRD_PARTY_HEADERS
  ${IMGUI_PATH}/imconfig.h
  ${IMGUI_PATH}/imgui.h
  ${IMGUI_PATH}/imgui_internal.h
  ${IMGUI_PATH}/imstb_rectpack.h
  ${IMGUI_PATH}/imstb_textedit.h
  ${IMGUI_PATH}/imstb_truetype.h
  ${IMGUI_PATH}/backends/imgui_impl_glfw.h
  ${IMGUI_PATH}/backends/imgui_impl_vulkan.h
  ${IMGUI_PATH}/misc/cpp/imgui_stdlib.h
)

SET(SOURCE_FILES
  ${INTERFACE_SOURCE_DIR}/brain/brain.cpp
  ${INTERFACE_SOURCE_DIR}/brain/commands.cpp
  ${INTERFACE_SOURCE_DIR}/brain/command_queue.cpp
  ${INTERFACE_SOURCE_DIR}/brain/key_mapping.cpp
  ${INTERFACE_SOURCE_DIR}/gui/gui.cpp
  ${INTERFACE_SOURCE_DIR}/gui/key_binding.cpp
  ${INTERFACE_SOURCE_DIR}/gui/settings.cpp
  ${INTERFACE_SOURCE_DIR}/rendering/command_buffer.cpp
  ${INTERFACE_SOURCE_DIR}/rendering/device.cpp
  ${INTERFACE_SOURCE_DIR}/rendering/instance.cpp
  ${INTERFACE_SOURCE_DIR}/rendering/pipeline.cpp
  ${INTERFACE_SOURCE_DIR}/rendering/render.cpp
  ${INTERFACE_SOURCE_DIR}/rendering/render_state.cpp
  ${INTERFACE_SOURCE_DIR}/rendering/shader.cpp
  ${INTERFACE_SOURCE_DIR}/rendering/swap_chain.cpp
  ${INTERFACE_SOURCE_DIR}/rendering/window.cpp
)

SET(THIRD_PARTY_SOURCES
  ${IMGUI_PATH}/imgui.cpp
  ${IMGUI_PATH}/imgui_demo.cpp
  ${IMGUI_PATH}/imgui_draw.cpp
  ${IMGUI_PATH}/imgui_tables.cpp
  ${IMGUI_PATH}/imgui_widgets.cpp
  ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
  ${IMGUI_PATH}/backends/imgui_impl_vulkan.cpp
  ${IMGUI_PATH}/misc/cpp/imgui_stdlib.cpp
)

IF(WIN32)
  SET(THIRD_PARTY_HEADERS
    ${THIRD_PARTY_HEADERS}
    ${IMGUI_PATH}/backends/imgui_impl_win32.h
  )
  SET(THIRD_PARTY_SOURCES
    ${THIRD_PARTY_SOURCES}
    ${IMGUI_PATH}/backends/imgui_impl_win32.cpp
  )
ENDIF()

SET(TEST_FILES
  ${INTERFACE_TEST_DIR}/main.cpp
  ${INTERFACE_TEST_DIR}/gui/key_binding_test.cpp
)

INCLUDE_DIRECTORIES(BEFORE
  ${INTERFACE_HEADER_DIR}/
  ${COMMON_HEADER_DIR}/
  ${BOOST_DIR}/
  ${IMGUI_PATH}/
  ${IMGUI_PATH}/backends
  ${IMGUI_PATH}/misc/cpp
  ${GLFW_PATH}/include
  ${GBA_LIBRARY_OUTPUT_DIRECTORY}
)

SOURCE_GROUP(TREE ${INTERFACE_HEADER_DIR} PREFIX "include" FILES ${HEADER_FILES})
SOURCE_GROUP(TREE ${INTERFACE_SOURCE_DIR} PREFIX "src" FILES ${SOURCE_FILES})
SOURCE_GROUP(third_party PREFIX "third_party" FILES ${THIRD_PARTY_HEADERS} ${THIRD_PARTY_SOURCES})

FIND_PACKAGE(Vulkan REQUIRED COMPONENTS glslc)
FIND_PROGRAM(glslc_executable NAMES glslc HINTS Vulkan::glslc)

ADD_LIBRARY(InterfaceLibrary
  ${HEADER_FILES}
  ${THIRD_PARTY_HEADERS}
  ${GBA_LIBRARY_OUTPUT_DIRECTORY}/revision.h
  
  ${SOURCE_FILES}
  ${THIRD_PARTY_SOURCES}
)

TARGET_USE_COMMON_OUTPUT_DIRECTORY(InterfaceLibrary)
TARGET_LINK_LIBRARIES(InterfaceLibrary Emulator Common Vulkan::Vulkan glfw)

ADD_EXECUTABLE(Interface
  ${HEADER_FILES}
  ${THIRD_PARTY_HEADERS}
  ${GBA_LIBRARY_OUTPUT_DIRECTORY}/revision.h
  
  ${INTERFACE_SOURCE_DIR}/main.cpp
)

TARGET_USE_COMMON_OUTPUT_DIRECTORY(Interface)
TARGET_LINK_LIBRARIES(Interface InterfaceLibrary)

SET(SHADER_SOURCE_DIR ${RESOURCE_PATH}/shaders)
SET(RESOURCE_BINARY_DIR ${CONFIGURATION_BINARY_DIR}/resources)
SET(SHADER_BINARY_DIR ${RESOURCE_BINARY_DIR}/shaders)

FILE(GLOB SHADERS
  ${SHADER_SOURCE_DIR}/*.vert
  ${SHADER_SOURCE_DIR}/*.frag
  ${SHADER_SOURCE_DIR}/*.comp
  ${SHADER_SOURCE_DIR}/*.geom
  ${SHADER_SOURCE_DIR}/*.tesc
  ${SHADER_SOURCE_DIR}/*.tese
  ${SHADER_SOURCE_DIR}/*.mesh
  ${SHADER_SOURCE_DIR}/*.task
  ${SHADER_SOURCE_DIR}/*.rgen
  ${SHADER_SOURCE_DIR}/*.rchit
  ${SHADER_SOURCE_DIR}/*.rmiss
)

FOREACH(source IN LISTS SHADERS)
  GET_FILENAME_COMPONENT(FILENAME ${source} NAME)
  ADD_CUSTOM_COMMAND(
    COMMAND
    ${glslc_executable}
      # -MD -MF ${SHADER_BINARY_DIR}/${FILENAME}.d
      -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
      ${source}
    OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
    DEPENDS ${source}
    COMMENT "Compiling shader ${FILENAME}"
  )
  LIST(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
ENDFOREACH()

ADD_CUSTOM_TARGET(shaders ALL DEPENDS ${SPV_SHADERS})

enable_testing()

ADD_EXECUTABLE(interface_test
  ${HEADER_FILES}
  ${THIRD_PARTY_HEADERS}
  ${GBA_LIBRARY_OUTPUT_DIRECTORY}/revision.h
  
  ${TEST_FILES}
)

TARGET_USE_COMMON_OUTPUT_DIRECTORY(interface_test)

TARGET_LINK_LIBRARIES(interface_test
  GTest::gtest_main
  GTest::gtest
  InterfaceLibrary
  Common
)

gtest_discover_tests(interface_test)
