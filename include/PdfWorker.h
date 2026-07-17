#ifndef PDFWORKER_H
#define PDFWORKER_H

#include <string>
#include <unordered_map>

#include "PdfInfo.h"

//======================================================
// PdfWorker
//
// Обробляє ОДИН PDF.
//
// Виконує:
//
// • читання ІПН;
// • пошук у Excel;
// • перейменування;
// • перенесення у Повтори;
// • перенесення у Не знайдено.
//
// Після виконання структура PdfInfo
// повністю заповнена.
//
//======================================================

//------------------------------------------------------
// Обробити один PDF.
//
// pdf        - інформація про PDF.
// folder     - папка з PDF.
// excelTable - таблиця:
//
//      ІПН -> Назва PDF.
//
//------------------------------------------------------
void processPdf(
    PdfInfo& pdf,
    const std::string& folder,
    const std::unordered_map<
        std::string,
        std::string>& excelTable);

#endif