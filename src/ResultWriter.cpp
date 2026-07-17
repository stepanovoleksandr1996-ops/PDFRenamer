//======================================================
// ResultWriter.cpp
//
// Запис журналу роботи.
//
// Portable-версія:
//
// Усі журнали тепер автоматично зберігаються у:
//
// Data/Logs/
//
// Незалежно від того, який шлях передали у writeResult().
//
// Це дозволяє переносити всю папку програми на флешці
// або інший ПК без зміни налаштувань.
//
//======================================================

#include "ResultWriter.h"

#include <fstream>

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

void writeResult(
    const std::string& fileName,
    const std::vector<PdfInfo>& pdfFiles)
{
    //--------------------------------------------------
    // Каталог програми
    //--------------------------------------------------
    QString appDir = QCoreApplication::applicationDirPath();

    //--------------------------------------------------
    // Створюємо Data/Logs якщо їх ще немає.
    //--------------------------------------------------
    QDir dir(appDir);

    dir.mkpath("Data");
    dir.mkpath("Data/Logs");

    //--------------------------------------------------
    // Беремо лише ім'я файлу.
    //
    // Якщо передали:
    //
    // logs/result.csv
    //
    // або
    //
    // C:/Temp/result.csv
    //
    // то буде використано тільки:
    //
    // result.csv
    //--------------------------------------------------
    QFileInfo info(QString::fromStdString(fileName));

    QString resultFile =
            appDir
            + "/Data/Logs/"
            + info.fileName();

    //--------------------------------------------------
    // Відкриваємо файл.
    //--------------------------------------------------
    std::ofstream file(resultFile.toStdString());

    if (!file.is_open())
        return;

    //--------------------------------------------------
    // Заголовок CSV
    //--------------------------------------------------
    file
        << "IPN,"
        << "Old File,"
        << "Result,"
        << "Status\n";

    //--------------------------------------------------
    // Дані
    //--------------------------------------------------
    for (const auto& pdf : pdfFiles)
    {
        file
            << pdf.ipn
            << ",\""
            << pdf.fileName
            << "\",\""
            << pdf.resultPath
            << "\","
            << pdf.status
            << "\n";
    }

    file.close();
}