add_library(logger-lib file_logger.cpp)

target_compile_options(logger-lib PRIVATE -Werror -Wall -Wextra -pedantic)
target_link_libraries(logger-lib PRIVATE)
target_include_directories(logger-lib PUBLIC .)
