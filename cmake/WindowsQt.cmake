#======================================================
#
# WindowsQt.cmake
#
# Підключення Qt для кроскомпіляції
# Linux -> Windows
#
# Використовується:
#
#   Host Qt
#       Runtime/QtHost
#
#   Target Qt
#       Runtime/QtSDK
#
#======================================================

#------------------------------------------------------
# Host Qt
#
# Використовується тільки для запуску:
#
#   moc
#   uic
#   rcc
#
# Працює під Linux.
#------------------------------------------------------

set(QT_HOST_ROOT
    "${PROJECT_SOURCE_DIR}/Runtime/QtHost/5.15.2/gcc_64")

#------------------------------------------------------
# Target Qt
#
# Використовується тільки для збірки EXE.
#
# DLL з цієї папки потраплять
# у Portable-версію.
#------------------------------------------------------

set(QT_TARGET_ROOT
    "${PROJECT_SOURCE_DIR}/Runtime/QtSDK/5.15.2/mingw81_64")

#------------------------------------------------------
# Host tools
#------------------------------------------------------

set(QT_MOC_EXECUTABLE
    "${QT_HOST_ROOT}/bin/moc"
    CACHE FILEPATH "")

set(QT_UIC_EXECUTABLE
    "${QT_HOST_ROOT}/bin/uic"
    CACHE FILEPATH "")

set(QT_RCC_EXECUTABLE
    "${QT_HOST_ROOT}/bin/rcc"
    CACHE FILEPATH "")

#------------------------------------------------------
# Windows Qt
#------------------------------------------------------

set(Qt5_DIR
    "${QT_TARGET_ROOT}/lib/cmake/Qt5")

set(CMAKE_PREFIX_PATH
    "${QT_TARGET_ROOT}")

message(STATUS "")
message(STATUS "========== Windows Qt ==========")
message(STATUS "Host Qt   : ${QT_HOST_ROOT}")
message(STATUS "Target Qt : ${QT_TARGET_ROOT}")
message(STATUS "================================")
message(STATUS "")