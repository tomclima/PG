add_library(tests)

target_sources(tests PRIVATE 
./libVector.hpp 
)

target_link_libraries(tests PRIVATE Vector)

target_include_directories(tests PUBLIC .)