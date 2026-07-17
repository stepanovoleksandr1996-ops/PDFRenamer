#ifndef RESULTWRITER_H
#define RESULTWRITER_H

#include <string>
#include <vector>

#include "PdfInfo.h"

// Записує результати роботи програми у CSV.
void writeResult(const std::string& fileName,
                 const std::vector<PdfInfo>& pdfFiles);

#endif