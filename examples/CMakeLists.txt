add_executable(example_cli cli/example_cli.c)
target_link_libraries(example_cli drip rid)

add_executable(det_generate det/det_generate.c)
target_link_libraries(det_generate drip rid)

find_package(PkgConfig)
if(PkgConfig_FOUND)
  pkg_check_modules(SODIUM libsodium)
  if(SODIUM_FOUND)
    add_executable(example_auth auth/example_auth.c)
    target_link_libraries(example_auth drip rid ${SODIUM_LIBRARIES})
    target_include_directories(example_auth PRIVATE ${SODIUM_INCLUDE_DIRS})

    add_executable(example_sign manifest/example_sign.c)
    target_link_libraries(example_sign drip ${SODIUM_LIBRARIES})
    target_include_directories(example_sign PRIVATE ${SODIUM_INCLUDE_DIRS})

    add_executable(example_verify manifest/example_verify.c)
    target_link_libraries(example_verify drip ${SODIUM_LIBRARIES})
    target_include_directories(example_verify PRIVATE ${SODIUM_INCLUDE_DIRS})

    add_executable(example_link link/example_link.c)
    target_link_libraries(example_link drip ${SODIUM_LIBRARIES})
    target_include_directories(example_link PRIVATE ${SODIUM_INCLUDE_DIRS})
  endif()
endif()

include(FetchContent)
FetchContent_Declare(
    librid
    GIT_REPOSITORY https://github.com/tuupola/librid.git
    GIT_TAG master
)
FetchContent_MakeAvailable(librid)
