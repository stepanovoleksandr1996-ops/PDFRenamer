#ifndef PDFPROCESSOR_H
#define PDFPROCESSOR_H

#include <functional>
#include <string>
#include <vector>

#include "PdfInfo.h"

//------------------------------------------------------
// Callback.
//
// Викликається після обробки кожного PDF.
//
// current - номер поточного файлу.
// total   - загальна кількість PDF.
// info    - результат обробки.
//
// Якщо callback == nullptr,
// ніяких повідомлень не надсилається.
//
//------------------------------------------------------

using ProgressCallback =
    std::function<void(
        int current,
        int total,
        const PdfInfo& info)>;

//------------------------------------------------------
// Обробити папку.
//
// folder
// excelFile
// callback
//------------------------------------------------------

std::vector<PdfInfo> processFolder(
    const std::string& folder,
    const std::string& excelFile,
    ProgressCallback callback = nullptr);

#endif