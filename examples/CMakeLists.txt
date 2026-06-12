add_executable(example_cli cli/example_cli.c)
target_link_libraries(example_cli drip rid)

add_executable(det_generate det/det_generate.c
    external/cSHAKE128-tiny/SP800-185.c
    external/cSHAKE128-tiny/KeccakSponge.c
    external/cSHAKE128-tiny/KeccakP-1600-inplace32BI.c
)
target_include_directories(det_generate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/cSHAKE128-tiny)
target_link_libraries(det_generate drip rid)

add_executable(det_verify det/det_verify.c
    external/cSHAKE128-tiny/SP800-185.c
    external/cSHAKE128-tiny/KeccakSponge.c
    external/cSHAKE128-tiny/KeccakP-1600-inplace32BI.c
)
target_include_directories(det_verify PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/cSHAKE128-tiny)
target_link_libraries(det_verify drip rid)

find_package(PkgConfig)
if(PkgConfig_FOUND)
  pkg_check_modules(SODIUM libsodium)
  if(SODIUM_FOUND)
    add_executable(example_auth auth/example_auth.c)
    target_link_libraries(example_auth drip rid ${SODIUM_LIBRARIES})
    target_include_directories(example_auth PRIVATE ${SODIUM_INCLUDE_DIRS})

    add_executable(manifest_sign manifest/manifest_sign.c)
    target_link_libraries(manifest_sign drip ${SODIUM_LIBRARIES})
    target_include_directories(manifest_sign PRIVATE ${SODIUM_INCLUDE_DIRS})

    add_executable(manifest_verify manifest/manifest_verify.c)
    target_link_libraries(manifest_verify drip ${SODIUM_LIBRARIES})
    target_include_directories(manifest_verify PRIVATE ${SODIUM_INCLUDE_DIRS})

    add_executable(link_verify link/link_verify.c)
    target_link_libraries(link_verify drip ${SODIUM_LIBRARIES})
    target_include_directories(link_verify PRIVATE ${SODIUM_INCLUDE_DIRS})
  endif()
endif()

include(FetchContent)
FetchContent_Declare(
    librid
    GIT_REPOSITORY https://github.com/tuupola/librid.git
    GIT_TAG master
)
FetchContent_MakeAvailable(librid)
