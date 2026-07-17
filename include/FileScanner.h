#ifndef FILESCANNER_H
#define FILESCANNER_H

#include <string>
#include <vector>

#include "PdfInfo.h"

// Шукає всі PDF у зазначеній папці
// та повертає список знайдених файлів.
std::vector<PdfInfo> scanPdfFiles(const std::string& folder);

#endif