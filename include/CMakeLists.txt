add_library(Point)

target_sources(Point PRIVATE 
../src/pointlib/point.cpp 

./pointlib/point.hpp 

)

target_include_directories(Point PUBLIC .)