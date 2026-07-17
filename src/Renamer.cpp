//======================================================
// Renamer.cpp
//
// Усі операції з файлами.
//
//======================================================

#include "Renamer.h"

#include <filesystem>

namespace fs = std::filesystem;

//======================================================
// Перейменувати PDF.
//
// Якщо файл з такою назвою вже існує,
// функція нічого не робить.
//
// Повертає:
//
// true  - перейменовано.
//
// false - файл уже існує
//         або виникла помилка.
//======================================================
bool renamePdf(const std::string& oldFile,
               const std::string& folder,
               const std::string& newName)
{
    try
    {
        //----------------------------------------------
        // Початковий PDF
        //----------------------------------------------

        fs::path source(oldFile);

        //----------------------------------------------
        // Новий шлях
        //----------------------------------------------

        fs::path destination =
            fs::path(folder) /
            (newName + ".pdf");

        //----------------------------------------------
        // Якщо файл уже існує —
        // не перезаписувати.
        //----------------------------------------------

        if (fs::exists(destination))
            return false;

        //----------------------------------------------
        // Перейменувати PDF
        //----------------------------------------------

        fs::rename(source, destination);

        return true;
    }
    catch (...)
    {
        return false;
    }
}

//======================================================
// Перемістити PDF у Повтори.
//
// Структура:
//
// Повтори/
//      ПІБ/
//          файл.pdf
//
//======================================================
bool moveToDuplicates(const std::string& pdfFile,
                      const std::string& personName)
{
    try
    {
        fs::path source(pdfFile);

        fs::path duplicateFolder =
            source.parent_path() /
            "Повтори" /
            personName;

        fs::create_directories(duplicateFolder);

        fs::rename(
            source,
            duplicateFolder /
            source.filename());

        return true;
    }
    catch (...)
    {
        return false;
    }
}

//======================================================
// Перемістити PDF у
//
// Не знайдено/
//
//======================================================
bool moveToNotFound(const std::string& pdfFile)
{
    try
    {
        fs::path source(pdfFile);

        fs::path folder =
            source.parent_path() /
            "Не знайдено";

        fs::create_directories(folder);

        fs::rename(
            source,
            folder /
            source.filename());

        return true;
    }
    catch (...)
    {
        return false;
    }
}