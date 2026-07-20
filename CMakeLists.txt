cmake_minimum_required(VERSION 3.16)

project(PDFRenamer)

# GitHub Actions збирає безпосередньо під Windows,
# тому додаткове налаштування Qt для кроскомпіляції не потрібне.

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
# Poppler (Linux + Windows через pkg-config)
#======================================================

find_package(PkgConfig REQUIRED)

pkg_check_modules(
    POPPLER
    REQUIRED
    poppler-cpp
)

message(STATUS "Poppler include: ${POPPLER_INCLUDE_DIRS}")
message(STATUS "Poppler libs: ${POPPLER_LIBRARIES}")

include_directories(

    include
    gui

    ${POPPLER_INCLUDE_DIRS}
)

link_directories(

    ${POPPLER_LIBRARY_DIRS}
)

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
    src/Settings.cpp

    src/Renamer.cpp
    src/Utils.cpp

    src/ResultWriter.cpp
)

#======================================================
# Бібліотеки
#======================================================

target_link_libraries(

    PDFRenamer

    Qt5::Widgets

    ${POPPLER_LIBRARIES}
)