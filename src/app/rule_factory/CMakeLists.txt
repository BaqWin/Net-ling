add_library(rules-lib rule_factory.cpp)

target_compile_options(rules-lib PRIVATE -Werror -Wall -Wextra -pedantic)
target_link_libraries(rules-lib PUBLIC type-lib)
target_include_directories(rules-lib PUBLIC .)
