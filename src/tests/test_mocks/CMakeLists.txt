add_library(test_mocks-lib INTERFACE)

target_compile_options(test_mocks-lib INTERFACE -Werror -Wall -Wextra -pedantic)
target_include_directories(test_mocks-lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_mocks-lib INTERFACE transmission-lib)
