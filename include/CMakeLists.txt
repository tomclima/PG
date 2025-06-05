add_library(Vector)

target_sources(Vector PRIVATE 
../src/libVector/vector.cpp 

./libVector/vector.hpp 

)

target_include_directories(Vector PUBLIC .)