add_library(S3D
3D.h
3D.cpp
camera.h
camera.cpp
gameObject.h
matrix.h
matrix.cpp
polyhedron.h
polyhedron.cpp
Scene.h
Scene.cpp
Globals.h
)

target_include_directories(S3D
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
)