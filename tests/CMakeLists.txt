
add_executable(test_rational test_rational.cpp)
target_include_directories(test_rational PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(test_variable test_variable.cpp)
target_include_directories(test_variable PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(test_term test_term.cpp)
target_include_directories(test_term PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(test_sparse_polynomial test_sparse_polynomial.cpp)
target_include_directories(test_sparse_polynomial PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_executable(test_operations test_operations.cpp)
target_include_directories(test_operations PRIVATE ${PROJECT_SOURCE_DIR}/include)