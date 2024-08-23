add_library(test_utils-lib test_utils.cpp)

target_compile_options(test_utils-lib PRIVATE -Werror -Wall -Wextra -pedantic)
target_include_directories(test_utils-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_utils-lib PRIVATE)
