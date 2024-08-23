set(UT_SOURCES 
    unit_tests/controller/controller_tests.cpp
    unit_tests/transmission_capture/transmission_capture_tests.cpp
    unit_tests/file_logger/file_logger_tests.cpp
    unit_tests/rule_factory/rule_factory_tests.cpp
)

include(GoogleTest)

add_subdirectory(test_utils)
add_subdirectory(test_mocks)

add_executable(${PROJECT_NAME}-tests ${UT_SOURCES})

target_include_directories(${PROJECT_NAME}-tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/test_mocks
)

target_compile_options(${PROJECT_NAME}-tests PRIVATE -Werror -Wall -Wextra -pedantic)

target_link_libraries(${PROJECT_NAME}-tests PRIVATE
                                            GTest::gtest_main
                                            GTest::gmock_main
                                            ${PCAPPLUSPLUS_LIB}
                                            ${PACKETPLUSPLUS_LIB}
                                            ${COMMONPLUSPLUS_LIB}
                                            ${LIBPCAP_LIB}
                                            ${COREFOUNDATION_FRAMEWORK}
                                            ${SYSTEMCONFIGURATION_FRAMEWORK}
                                            controller-lib
                                            transmission-lib
                                            logger-lib
                                            rules-lib
                                            test_utils-lib
)

set(CTEST_BINARY_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_test(NAME ${PROJECT_NAME}-tests COMMAND ${PROJECT_NAME}-tests WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
