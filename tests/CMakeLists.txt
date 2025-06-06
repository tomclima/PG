add_library(tests)

target_sources(tests PRIVATE 
./VectorTest.hpp 
)

target_link_libraries(tests PRIVATE include)

target_include_directories(tests PUBLIC .)