cmake_minimum_required(VERSION 3.10)
project(CHATCLIENT C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

include_directories(include)

add_executable(chatclient
    src/main.c
    src/client.c
    src/config.c
)

enable_testing()
find_package(GTest REQUIRED)

add_executable(runTests
    test/test_client.cpp
    src/client.c
)

target_include_directories(runTests PRIVATE include)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)

add_test(NAME ClientTests COMMAND runTests)

# Coverage target
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

add_custom_target(coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND ${LCOV_PATH} --capture --directory . --output-file coverage.info --ignore-errors mismatch
    COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' '*/test/*' --output-file coverage.info
    COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage-report
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests and generating coverage report"
)


