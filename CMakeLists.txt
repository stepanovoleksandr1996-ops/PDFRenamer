cmake_minimum_required(VERSION 3.16)

project(PDFRenamer)

if(CMAKE_CROSSCOMPILING)
    include(cmake/WindowsQt.cmake)
endif()

#======================================================
# C++20
#======================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#======================================================
# Qt
#======================================================

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)


find_package(Qt5 REQUIRED COMPONENTS Widgets)

#======================================================
# Poppler
#======================================================

#
# Linux
#
# Використовуємо системний Poppler через pkg-config.
#
# Windows
#
# Надалі будемо використовувати бібліотеки,
# що лежать всередині Runtime/Poppler.
#

if(WIN32)

    message(STATUS "Building Windows Portable version")

    #
    # Каталог Runtime/Poppler.
    #
    set(POPPLER_ROOT
        "${CMAKE_SOURCE_DIR}/Runtime/Poppler")

    include_directories(

        include
        gui

        "${POPPLER_ROOT}/include"
    )

    link_directories(

        "${POPPLER_ROOT}/lib"
    )

else()

    message(STATUS "Building Linux version")

    find_package(PkgConfig REQUIRED)

    pkg_check_modules(
        POPPLER
        REQUIRED
        poppler-cpp)

    include_directories(

        include
        gui

        ${POPPLER_INCLUDE_DIRS}
    )

    link_directories(

        ${POPPLER_LIBRARY_DIRS}
    )

endif()

#======================================================
# Виконуваний файл
#======================================================

add_executable(PDFRenamer

    #--------------------------------------------------
    # Точка входу
    #--------------------------------------------------

    src/main.cpp

    #--------------------------------------------------
    # GUI
    #--------------------------------------------------

    gui/MainWindow.cpp
    gui/ProcessingWorker.cpp

    #--------------------------------------------------
    # Ядро
    #--------------------------------------------------

    src/PdfReader.cpp
    src/FileScanner.cpp
    src/PdfProcessor.cpp
    src/PdfWorker.cpp

    src/CsvReader.cpp
    src/ExcelConverter.cpp

    src/Renamer.cpp
    src/Utils.cpp

    src/ResultWriter.cpp
)

#======================================================
# Бібліотеки
#======================================================

if(WIN32)

    target_link_libraries(

        PDFRenamer

        Qt5::Widgets

        poppler-cpp
    )

else()

    target_link_libraries(

        PDFRenamer

        Qt5::Widgets

        ${POPPLER_LIBRARIES}
    )

endif()