set(UT_SOURCES 
    unit_tests/controller/controller_tests.cpp
    unit_tests/transmission_capture/transmission_capture_tests.cpp
    unit_tests/file_logger/file_logger_tests.cpp
    unit_tests/rule_factory/rule_factory_tests.cpp
)

set(IT_SOURCES 
    integration_tests/integration_tests.cpp
)

include(GoogleTest)

add_subdirectory(test_utils)
add_subdirectory(test_mocks)

add_executable(${PROJECT_NAME}-unit-tests ${UT_SOURCES})
add_executable(${PROJECT_NAME}-integration-tests ${IT_SOURCES})

target_include_directories(${PROJECT_NAME}-unit-tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/test_mocks
)

target_compile_options(${PROJECT_NAME}-unit-tests PRIVATE -Werror -Wall -Wextra -pedantic)
target_compile_options(${PROJECT_NAME}-integration-tests PRIVATE -Werror -Wall -Wextra -pedantic)

set(COMMON_LIBS
    GTest::gtest_main
    controller-lib
    test_utils-lib
)

set(UNIT_TEST_LIBS
    GTest::gmock_main
    logger-lib
    rules-lib
    transmission-lib
    ${PCAPPLUSPLUS_LIB}
    ${PACKETPLUSPLUS_LIB}
    ${COMMONPLUSPLUS_LIB}
    ${LIBPCAP_LIB}
)

target_link_libraries(${PROJECT_NAME}-unit-tests PRIVATE ${COMMON_LIBS} ${UNIT_TEST_LIBS})

target_link_libraries(${PROJECT_NAME}-integration-tests PRIVATE ${COMMON_LIBS} ${UNIT_TEST_LIBS})

set(CTEST_BINARY_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(NAME ${PROJECT_NAME}-unit-tests COMMAND ${PROJECT_NAME}-unit-tests WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
