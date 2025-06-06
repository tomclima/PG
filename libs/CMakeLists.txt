add_library(include INTERFACE)

add_subdirectory(Prism)
target_link_libraries(include INTERFACE Prism)
