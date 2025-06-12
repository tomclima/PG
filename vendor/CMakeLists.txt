add_subdirectory(ObjReader)

add_library(vendor INTERFACE)
target_link_libraries(vendor INTERFACE ObjReader)
