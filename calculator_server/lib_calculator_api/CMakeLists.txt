project(lib_calculator_api)

add_thrift_api(${PROJECT_NAME}
    Calculator
    CALCULATOR_API_TARGETS
    CALCULATOR_API_SOURCES
    CALCULATOR_API_HEADERS
    CALCULATOR_API_INCLUDE_DIRS
)

add_library(${PROJECT_NAME} ${CALCULATOR_API_SOURCES} ${CALCULATOR_API_HEADERS})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CALCULATOR_API_INCLUDE_DIRS}
)

add_dependencies(${PROJECT_NAME} ${CALCULATOR_API_TARGETS})

target_link_libraries(${PROJECT_NAME} ${COMMON_LIBS})

#add_custom_command(TARGET ${PROJECT_NAME}
#    PRE_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy ${CALCULATOR_API_HEADERS} ${CMAKE_SOURCE_DIR}/calculator_client/lib_network_api/include/network_api/generated/
#    COMMAND ${CMAKE_COMMAND} -E copy ${CALCULATOR_API_SOURCES} ${CMAKE_SOURCE_DIR}/calculator_client/lib_network_api/src/generated/
#    COMMENT "Copying generated C++ thrift api network files to the thrift client"
#)

# Expose includes to other subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)