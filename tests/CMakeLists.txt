find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories(${TEST_SOURCE_DIR}/src)
include_directories(${Boost_INCLUDE_DIRS})

add_definitions(-DBOOST_TEST_DYN_LINK)
