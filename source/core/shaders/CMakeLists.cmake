SET(FOLDER "shaders")
SET(SOURCES "shader.cpp")
SET(HEADERS "shader.h")

INCLUDE(IncludeFolder)
INCLUDE_FOLDER()

FILE(COPY "${CMAKE_CURRENT_SOURCE_DIR}/shaders/simple-shaders" 
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/shaders"
)
