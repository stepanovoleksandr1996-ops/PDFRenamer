#ifndef EXCELCONVERTER_H
#define EXCELCONVERTER_H

#include <string>

// Конвертує Excel (.xlsx) у CSV.
// Повертає true при успіху.
bool convertExcelToCsv(const std::string& excelFile,
                       const std::string& csvFile);

#endif