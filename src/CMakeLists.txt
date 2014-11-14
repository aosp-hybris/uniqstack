pkg_check_modules(SYSTEMD libsystemd REQUIRED)

include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

set(SOURCES
  main.cpp
  shellapplication.cpp)

add_executable(copycat ${SOURCES} ${RESOURCES})
qt5_use_modules(copycat Quick Gui)
target_link_libraries(
  copycat
  ${SYSTEMD_LIBRARIES})

install(
  TARGETS copycat
  RUNTIME DESTINATION ${CMAKE_INSTALL_SBINDIR})
