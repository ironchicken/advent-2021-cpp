find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories(${TEST_SOURCE_DIR}/src)
include_directories(${Boost_INCLUDE_DIRS})

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(
  SonarSweepTests SonarSweepTests.cpp
  )

target_link_libraries(
  SonarSweepTests
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  )

add_executable(
  DiveTests DiveTests.cpp
  )

target_link_libraries(
  DiveTests
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  )

add_executable(
  BinaryDiagnosticsTests BinaryDiagnosticsTests.cpp
  )

target_link_libraries(
  BinaryDiagnosticsTests
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  )

add_executable(
  GiantSquidTests GiantSquidTests.cpp
  )

target_link_libraries(
  GiantSquidTests
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  )

add_executable(
  HydrothermalVentureTests HydrothermalVentureTests.cpp
  )

target_link_libraries(
  HydrothermalVentureTests
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  )

add_executable(
  LanternfishTests LanternfishTests.cpp
  )

target_link_libraries(
  LanternfishTests
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  )

add_executable(
  PassagePathingTests PassagePathingTests.cpp
  )

target_link_libraries(
  PassagePathingTests
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  )
