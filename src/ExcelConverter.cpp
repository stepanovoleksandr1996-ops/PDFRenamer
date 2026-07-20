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
// Windows:
//     1. Спочатку шукає Portable LibreOffice.
//     2. Якщо його немає — читає шлях із config.ini.
//
//======================================================

#include "ExcelConverter.h"
#include "Settings.h"

#include <QProcess>
#include <QStringList>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

//------------------------------------------------------
// Повертає команду запуску LibreOffice
//------------------------------------------------------

static std::string getLibreOfficeCommand()
{
#ifdef _WIN32

    //--------------------------------------------------
    // Спочатку шукаємо Portable LibreOffice
    //--------------------------------------------------

    QString appDir = QCoreApplication::applicationDirPath();

    QString portableLibreOffice =
            appDir +
            "/Runtime/LibreOffice/program/soffice.exe";

    if (QFileInfo::exists(portableLibreOffice))
    {
        return "\"" + portableLibreOffice.toStdString() + "\"";
    }

    //--------------------------------------------------
    // Якщо Portable немає —
    // читаємо config.ini
    //--------------------------------------------------

    QString savedPath = Settings::libreOfficePath();

    if (!savedPath.isEmpty() &&
        QFileInfo::exists(savedPath))
    {
        return "\"" + savedPath.toStdString() + "\"";
    }

    //--------------------------------------------------
    // LibreOffice не знайдений
    //--------------------------------------------------

    return "";

#else

    //--------------------------------------------------
    // Linux
    //--------------------------------------------------

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

    //--------------------------------------------------
    // Отримати команду запуску LibreOffice
    //--------------------------------------------------

    std::string libreOffice = getLibreOfficeCommand();

    if (libreOffice.empty())
        return false;

    fs::path excelPath(excelFile);

    //--------------------------------------------------
    // Запуск LibreOffice
    //--------------------------------------------------

// Запуск LibreOffice
//--------------------------------------------------

QString program = QString::fromStdString(getLibreOfficeCommand());

#ifdef _WIN32
program.remove('"');
#endif

QStringList arguments;

arguments << "--headless";

arguments << "--convert-to";
arguments << "csv:Text - txt - csv (StarCalc):44,34,76";

arguments << QString::fromStdString(excelFile);

arguments << "--outdir";
arguments << QString::fromStdString(excelPath.parent_path().string());

QProcess process;

process.start(program, arguments);

if (!process.waitForStarted())
    return false;

if (!process.waitForFinished(-1))
    return false;

if (process.exitStatus() != QProcess::NormalExit)
    return false;

if (process.exitCode() != 0)
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