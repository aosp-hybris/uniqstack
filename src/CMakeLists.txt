pkg_check_modules(SYSTEMD libsystemd REQUIRED)

include_directories(${Qt5Gui_PRIVATE_INCLUDE_DIRS})

set(SOURCES
  main.cpp
  shellapplication.cpp)

add_executable(uniqstack ${SOURCES} ${RESOURCES})
qt5_use_modules(uniqstack Quick Gui)
target_link_libraries(
  uniqstack
  ${SYSTEMD_LIBRARIES})

install(
  TARGETS uniqstack
  RUNTIME DESTINATION ${CMAKE_INSTALL_SBINDIR})
