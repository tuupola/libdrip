if(ESP_PLATFORM)
  idf_component_register(
        SRCS "src/manifest.c"
        INCLUDE_DIRS "include"
    )
else()
  cmake_minimum_required(VERSION 3.10)
  project(libdrip LANGUAGES C)

  set(CMAKE_C_STANDARD 99)
  set(CMAKE_C_STANDARD_REQUIRED ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  add_custom_target(compile_commands_symlink ALL
        COMMAND ${CMAKE_COMMAND} -E create_symlink
                ${CMAKE_BINARY_DIR}/compile_commands.json
                ${CMAKE_SOURCE_DIR}/compile_commands.json
        DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
        COMMENT "Creating compile_commands.json symlink"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

  option(DRIP_BUILD_EXAMPLES "Build example programs" OFF)
  option(DRIP_BUILD_TESTS "Build unit tests" OFF)

  add_library(drip
        src/hash.c
        src/manifest.c
    )

  target_include_directories(drip PUBLIC include)
  target_compile_options(drip PRIVATE -Wall -Wextra -Wdouble-promotion)

  include(GNUInstallDirs)

  install(TARGETS drip
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

  install(DIRECTORY include/drip DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  add_custom_target(uninstall
        COMMAND echo "Removing ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/drip"
        COMMAND rm -rf ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}/drip
        COMMAND echo "Removing ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/libdrip*"
        COMMAND rm -f ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/libdrip*
    )

  if(DRIP_BUILD_EXAMPLES)
    add_subdirectory(examples)
  endif()

  if(DRIP_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
  endif()
endif()
