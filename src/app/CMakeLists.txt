add_executable(${PROJECT_NAME} main.cpp)

include_directories(/usr/local/include)
add_subdirectory(transmission_capture)
add_subdirectory(file_logger)

execute_process(COMMAND brew --prefix pcapplusplus OUTPUT_VARIABLE PCAPPLUSPLUS_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE)

find_library(PCAPPLUSPLUS_LIB NAMES Pcap++ PATHS /usr/local/lib NO_DEFAULT_PATH)
find_library(PACKETPLUSPLUS_LIB NAMES Packet++ PATHS /usr/local/lib NO_DEFAULT_PATH)
find_library(COMMONPLUSPLUS_LIB NAMES Common++ PATHS /usr/local/lib NO_DEFAULT_PATH)
find_library(LIBPCAP_LIB NAMES pcap)
find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
find_library(SYSTEMCONFIGURATION_FRAMEWORK SystemConfiguration)

target_link_libraries(${PROJECT_NAME} ${PCAPPLUSPLUS_LIB} ${PACKETPLUSPLUS_LIB} ${COMMONPLUSPLUS_LIB} ${LIBPCAP_LIB}
                        ${COREFOUNDATION_FRAMEWORK} ${SYSTEMCONFIGURATION_FRAMEWORK}
                        transmission-lib
                        logger-lib)

target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -pedantic)