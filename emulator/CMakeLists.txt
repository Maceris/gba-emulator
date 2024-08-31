# Emulator

SET(EMULATOR_SOURCE_DIR ${EMULATOR_DIR}/src)
SET(EMULATOR_TEST_DIR ${EMULATOR_DIR}/test)

SET(HEADER_FILES
  ${EMULATOR_HEADER_DIR}/audio/apu.h
  ${EMULATOR_HEADER_DIR}/board/advanced_game_boy.h
  ${EMULATOR_HEADER_DIR}/board/bus.h
  ${EMULATOR_HEADER_DIR}/cartridge/advance_game_pak.h
  ${EMULATOR_HEADER_DIR}/cartridge/color_game_pak.h
  ${EMULATOR_HEADER_DIR}/cartridge/game_pak.h
  ${EMULATOR_HEADER_DIR}/cpu/cpu.h
  ${EMULATOR_HEADER_DIR}/cpu/cpu_constants.h
  ${EMULATOR_HEADER_DIR}/memory/memory_constants.h
  ${EMULATOR_HEADER_DIR}/memory/memory_types.h
  ${EMULATOR_HEADER_DIR}/video/ppu.h
)

SET(THIRD_PARTY_HEADERS

)

SET(SOURCE_FILES
  ${EMULATOR_SOURCE_DIR}/cpu/cpu.cpp
)

SET(TEST_FILES
  ${EMULATOR_TEST_DIR}/cpu/cpu_test.cpp
)

INCLUDE_DIRECTORIES(BEFORE
  ${EMULATOR_HEADER_DIR}/
  ${BOOST_DIR}/
)

SOURCE_GROUP(TREE ${EMULATOR_HEADER_DIR} PREFIX "include" FILES ${HEADER_FILES})
SOURCE_GROUP(TREE ${EMULATOR_SOURCE_DIR} PREFIX "src" FILES ${SOURCE_FILES})
SOURCE_GROUP(TREE ${EMULATOR_TEST_DIR} PREFIX "test" FILES ${TEST_FILES})

ADD_LIBRARY(Emulator
  ${HEADER_FILES}
  ${THIRD_PARTY_HEADERS}
  
  ${SOURCE_FILES}
)

TARGET_USE_COMMON_OUTPUT_DIRECTORY(Emulator)

TARGET_LINK_LIBRARIES(Emulator Common)

enable_testing()

ADD_EXECUTABLE(emulator_test
  ${HEADER_FILES}
  
  ${TEST_FILES}
)

TARGET_USE_COMMON_OUTPUT_DIRECTORY(emulator_test)

TARGET_LINK_LIBRARIES(emulator_test
  GTest::gtest_main
  GTest::gtest
  Emulator
  Common
)

gtest_discover_tests(emulator_test)
