#include "FileScanner.h"

#include <filesystem>

namespace fs = std::filesystem;

// Знайти всі PDF-файли у папці.
std::vector<PdfInfo> scanPdfFiles(const std::string& folder)
{
    std::vector<PdfInfo> files;

    // Перебрати всі об'єкти у папці
    for (const auto& entry : fs::directory_iterator(folder))
    {
        // Пропустити каталоги
        if (!entry.is_regular_file())
            continue;

        // Залишити лише PDF
        if (entry.path().extension() != ".pdf")
            continue;

        PdfInfo pdf;

        // Запам'ятати назву файлу
        pdf.fileName = entry.path().filename().string();

        // Запам'ятати повний шлях
        pdf.fullPath = entry.path().string();

        // Додати інформацію до списку
        files.push_back(pdf);
    }

    // Повернути список знайдених PDF
    return files;
}