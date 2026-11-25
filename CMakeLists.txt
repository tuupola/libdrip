if(ESP_PLATFORM)
  set(DRIP_SRCS
        "src/det.c"
        "src/error.c"
        "src/hash.c"
        "src/link.c"
        "src/manifest.c"
        "src/wrapper.c"
    )

  if(NOT DRIP_DISABLE_JSON)
    list(APPEND DRIP_SRCS "src/json.c")
  endif()

  idf_component_register(
        SRCS ${DRIP_SRCS}
        INCLUDE_DIRS
            "include"
    )
  target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-error=format)

  if(DRIP_DISABLE_JSON)
    target_compile_definitions(${COMPONENT_LIB} PUBLIC DRIP_DISABLE_JSON)
  endif()

else()
  cmake_minimum_required(VERSION 3.30)
  project(libdrip LANGUAGES C)

  set(CMAKE_C_STANDARD 11)
  set(CMAKE_C_STANDARD_REQUIRED ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_custom_target(compile_commands_symlink ALL
          COMMAND ${CMAKE_COMMAND} -E create_symlink
                  ${CMAKE_BINARY_DIR}/compile_commands.json
                  ${CMAKE_SOURCE_DIR}/compile_commands.json
          DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
          COMMENT "Creating compile_commands.json symlink"
          WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      )
  endif()

  option(DRIP_BUILD_EXAMPLES "Build example programs" OFF)
  option(DRIP_BUILD_TESTS "Build unit tests" OFF)
  option(DRIP_DISABLE_JSON "Exclude JSON serialization" OFF)

  set(DRIP_SRCS
        src/error.c
        src/hash.c
        src/link.c
        src/manifest.c
        src/det.c
        src/wrapper.c
    )

  if(NOT DRIP_DISABLE_JSON)
    list(APPEND DRIP_SRCS src/json.c)
  endif()

  add_library(drip ${DRIP_SRCS})

  target_include_directories(drip PUBLIC include)
  target_compile_options(drip PRIVATE -Wall -Wextra -Wdouble-promotion)

  if(DRIP_DISABLE_JSON)
    target_compile_definitions(drip PUBLIC DRIP_DISABLE_JSON)
  endif()

  include(GNUInstallDirs)

  install(TARGETS drip
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

  install(DIRECTORY include/drip DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_custom_target(uninstall
          COMMAND echo "Removing ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/drip"
          COMMAND rm -rf ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/drip
          COMMAND echo "Removing ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/libdrip*"
          COMMAND rm -f ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/libdrip*
      )
  endif()

  if(DRIP_BUILD_EXAMPLES)
    add_subdirectory(examples)
  endif()

  if(DRIP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
  endif()

endif()
