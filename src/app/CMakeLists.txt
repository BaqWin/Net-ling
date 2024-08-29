add_executable(${PROJECT_NAME} main.cpp)

include_directories(/usr/local/include)
add_subdirectory(controller)
add_subdirectory(transmission_capture)
add_subdirectory(file_logger)
add_subdirectory(rule_factory)
add_subdirectory(rule_type)

target_link_libraries(${PROJECT_NAME}
    controller-lib
    transmission-lib
    logger-lib
    rules-lib
    type-lib
    ${PCAPPLUSPLUS_LIB}
    ${PACKETPLUSPLUS_LIB}
    ${COMMONPLUSPLUS_LIB}
    ${LIBPCAP_LIB}
)

target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -pedantic)
