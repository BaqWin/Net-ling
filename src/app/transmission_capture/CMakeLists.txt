add_library(transmission-lib transmission_capture.cpp)

target_compile_options(transmission-lib PRIVATE -Werror -Wall -Wextra -pedantic)
target_link_libraries(transmission-lib PUBLIC controller-lib)
target_include_directories(transmission-lib PUBLIC .)
