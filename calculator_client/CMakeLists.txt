project(calculator_client)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${lib_calculator_api_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    lib_calculator_api
)