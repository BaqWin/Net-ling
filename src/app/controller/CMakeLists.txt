add_library(controller-lib controller.cpp)

target_compile_options(controller-lib PRIVATE -Werror -Wall -Wextra -pedantic)
target_link_libraries(controller-lib PRIVATE transmission-lib)
target_include_directories(controller-lib PUBLIC .)
