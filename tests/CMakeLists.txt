find_package(PkgConfig)
pkg_check_modules(SODIUM libsodium REQUIRED)

add_executable(test_runner
    unit.c
    test_manifest.c
    test_hash.c
    test_link.c
    test_det.c
    ${CMAKE_SOURCE_DIR}/examples/external/cSHAKE128-tiny/SP800-185.c
    ${CMAKE_SOURCE_DIR}/examples/external/cSHAKE128-tiny/KeccakSponge.c
    ${CMAKE_SOURCE_DIR}/examples/external/cSHAKE128-tiny/KeccakP-1600-inplace32BI.c
)

target_include_directories(test_runner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/examples/external/cSHAKE128-tiny
)
target_compile_options(test_runner PRIVATE -Werror=double-promotion)
target_link_libraries(test_runner drip ${SODIUM_LIBRARIES})

add_test(NAME unit_tests COMMAND test_runner)
