project(AtxLoggerTest)

add_executable(AtxLoggerTest
    AtxLoggerTest.cpp
)

set(CMAKE_CXX_STANDARD 14)

target_include_directories(AtxLoggerTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(AtxLoggerTest PRIVATE AtxLogger)

set_target_properties(AtxLoggerTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
