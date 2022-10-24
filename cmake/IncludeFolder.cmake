MACRO(INCLUDE_FOLDER)
    FOREACH(_header ${HEADERS})
        SET(INSTALL_HEADERS "${INSTALL_HEADERS}"
                            "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/include/${_header}"
        )
    ENDFOREACH()

    FOREACH(_source ${SOURCES})
        SET(SRC_FILES "${SRC_FILES}"
                      "${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}/src/${_source}"
        )
    ENDFOREACH()

ENDMACRO()
