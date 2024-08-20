add_library(rules-lib filter_factory.cpp berkeley_rule.cpp)

target_compile_options(rules-lib PRIVATE -Werror -Wall -Wextra -pedantic)
target_link_libraries(rules-lib PUBLIC)
target_include_directories(rules-lib PUBLIC .)
