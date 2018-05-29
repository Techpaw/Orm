cmake_minimum_required(VERSION 3.8)
project(orm)
add_definitions("-std=c++14")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(INCLUDE_DIR include)

set(HEADER_FILES
    ${INCLUDE_DIR}/orm/statements/aggregate_function_statement.hpp
    ${INCLUDE_DIR}/orm/statements/all.hpp
    ${INCLUDE_DIR}/orm/statements/case_statement.hpp
    ${INCLUDE_DIR}/orm/statements/comparison_operator.hpp
    ${INCLUDE_DIR}/orm/statements/conditional_statement.hpp
    ${INCLUDE_DIR}/orm/statements/else_statement.hpp
    ${INCLUDE_DIR}/orm/statements/end_statement.hpp
    ${INCLUDE_DIR}/orm/statements/field.hpp
    ${INCLUDE_DIR}/orm/statements/field_statement.hpp
    ${INCLUDE_DIR}/orm/statements/function_statement.hpp
    ${INCLUDE_DIR}/orm/statements/group_by_statement.hpp
    ${INCLUDE_DIR}/orm/statements/group_statement.hpp
    ${INCLUDE_DIR}/orm/statements/insert_statement.hpp
    ${INCLUDE_DIR}/orm/statements/join_statement.hpp
    ${INCLUDE_DIR}/orm/statements/limit_statement.hpp
    ${INCLUDE_DIR}/orm/statements/literal_statement.hpp
    ${INCLUDE_DIR}/orm/statements/node.hpp
    ${INCLUDE_DIR}/orm/statements/offset_statement.hpp
    ${INCLUDE_DIR}/orm/statements/on_statement.hpp
    ${INCLUDE_DIR}/orm/statements/order_statement.hpp
    ${INCLUDE_DIR}/orm/statements/select_statement.hpp
    ${INCLUDE_DIR}/orm/statements/statement.hpp
    ${INCLUDE_DIR}/orm/statements/then_statement.hpp
    ${INCLUDE_DIR}/orm/statements/update_statement.hpp
    ${INCLUDE_DIR}/orm/statements/when_statement.hpp
    ${INCLUDE_DIR}/orm/statements/where_statement.hpp
    ${INCLUDE_DIR}/orm/connection.hpp
    ${INCLUDE_DIR}/orm/constants.hpp
    ${INCLUDE_DIR}/orm/exceptions.hpp
    ${INCLUDE_DIR}/orm/table.hpp
)
set(SOURCE_FILES main.cpp)
add_executable(orm ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(orm PRIVATE ${INCLUDE_DIR})
conan_target_link_libraries(orm)