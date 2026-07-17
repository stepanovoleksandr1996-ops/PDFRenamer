cmake_minimum_required(VERSION 3.16)

project(PDFRenamer)

#======================================================
# C++20
#======================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Windows build selected")

#======================================================
# Шляхи до заголовків
#======================================================

include_directories(

    ../include
    ../gui

)

#======================================================
# Створення EXE
#======================================================

add_executable(PDFRenamer

    ../src/main.cpp

    ../gui/MainWindow.cpp
    ../gui/ProcessingWorker.cpp

    ../src/PdfReader.cpp
    ../src/FileScanner.cpp
    ../src/PdfProcessor.cpp
    ../src/PdfWorker.cpp

    ../src/CsvReader.cpp
    ../src/ExcelConverter.cpp

    ../src/Renamer.cpp
    ../src/Utils.cpp

    ../src/ResultWriter.cpp

)