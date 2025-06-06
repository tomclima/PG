add_library(Prism)

target_sources(Prism PRIVATE 
    src/vector.cpp
)

target_include_directories(Prism PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)