add_library(type-lib rule_type.cpp)

target_compile_options(type-lib PRIVATE -Werror -Wall -Wextra -pedantic)
target_link_libraries(type-lib PUBLIC)
target_include_directories(type-lib PUBLIC .)
