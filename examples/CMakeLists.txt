include(FetchContent)
FetchContent_Declare(
    librid
    GIT_REPOSITORY https://github.com/tuupola/librid.git
    GIT_TAG master
)
FetchContent_MakeAvailable(librid)

add_executable(example_auth auth/example_auth.c)
target_link_libraries(example_auth drip rid)

if(PkgConfig_FOUND)
  pkg_check_modules(SODIUM libsodium)
  if(SODIUM_FOUND)
    target_link_libraries(example_auth ${SODIUM_LIBRARIES})
    target_include_directories(example_auth PRIVATE ${SODIUM_INCLUDE_DIRS})
  endif()
endif()
