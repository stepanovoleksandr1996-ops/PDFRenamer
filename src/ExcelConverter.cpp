//======================================================
// ExcelConverter.cpp
//
// Конвертація Excel (.xlsx) у CSV UTF-8.
//
// Підтримує:
//
// Linux:
//     використовує libreoffice із PATH.
//
// Windows Portable:
//     автоматично шукає
//     Runtime/LibreOffice/program/soffice.exe
//     поруч із PDFRenamer.exe.
//
//======================================================

#include "ExcelConverter.h"

#include <QCoreApplication>
#include <QDir>

#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

//------------------------------------------------------
// Повертає команду запуску LibreOffice
//------------------------------------------------------
static std::string getLibreOfficeCommand()
{
#ifdef _WIN32

    /*
     * Portable-версія.
     *
     * Очікується структура:
     *
     * PDFRenamer.exe
     * Runtime/
     *     LibreOffice/
     *         program/
     *             soffice.exe
     */

    QString appDir = QCoreApplication::applicationDirPath();

    QString soffice =
            appDir +
            "/Runtime/LibreOffice/program/soffice.exe";

    return "\"" + soffice.toStdString() + "\"";

#else

    /*
     * Linux.
     *
     * Використовується системний LibreOffice.
     */

    return "libreoffice";

#endif
}

bool convertExcelToCsv(const std::string& excelFile,
                       const std::string& csvFile)
{
    //--------------------------------------------------
    // Перевірити існування Excel
    //--------------------------------------------------

    if (!fs::exists(excelFile))
        return false;

    fs::path excelPath(excelFile);

    //--------------------------------------------------
    // Формування команди
    //--------------------------------------------------

    std::string command =
        getLibreOfficeCommand() +
        " --headless "
        "--convert-to "
        "\"csv:Text - txt - csv (StarCalc):44,34,76\" "
        "\"" + excelFile + "\" "
        "--outdir "
        "\"" + excelPath.parent_path().string() + "\"";

    //--------------------------------------------------
    // Запуск LibreOffice
    //--------------------------------------------------

    if (std::system(command.c_str()) != 0)
        return false;

    //--------------------------------------------------
    // Перевірити створення CSV
    //--------------------------------------------------

    fs::path generated =
        excelPath.parent_path() /
        (excelPath.stem().string() + ".csv");

    if (!fs::exists(generated))
        return false;

    //--------------------------------------------------
    // Якщо потрібно —
    // копіюємо під необхідним ім'ям
    //--------------------------------------------------

    if (generated != fs::path(csvFile))
    {
        fs::copy_file(
            generated,
            csvFile,
            fs::copy_options::overwrite_existing);
    }

    return true;
}