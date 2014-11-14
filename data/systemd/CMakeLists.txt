
set(SYSTEMD_LIB_INSTALL_DIR
  "/lib/systemd/system"
  CACHE PATH "Base directory for systemd target and service files")

install(
  FILES copycat.service
  DESTINATION ${SYSTEMD_LIB_INSTALL_DIR})
