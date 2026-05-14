find_package(PkgConfig)
pkg_check_modules(SODIUM libsodium REQUIRED)

add_executable(test_runner
    unit.c
    test_manifest.c
    test_hash.c
)

target_include_directories(test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(test_runner PRIVATE -Werror=double-promotion)
target_link_libraries(test_runner drip ${SODIUM_LIBRARIES})

add_test(NAME unit_tests COMMAND test_runner)