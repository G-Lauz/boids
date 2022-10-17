# INCLUDE_FOLDER(FOLDER, SOURCES, HEADERS)
MACRO(INCLUDE_FOLDER)
    FOREACH(_header ${ARGV2})
        SET(INSTALL_HEADERS "${INSTALL_HEADERS}" 
                            "${ARGV0}/include/${_header}"
        )
    ENDFOREACH()

    FOREACH(_source ${ARGV1})
        SET(SRC_FILES "${SRC_FILES}" 
                      "${CMAKE_CURRENT_SOURCE_DIR}/${ARGV0}/src/${_source}"
        )
    ENDFOREACH()

ENDMACRO()
