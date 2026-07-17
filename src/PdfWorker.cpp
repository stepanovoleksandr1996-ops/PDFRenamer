//======================================================
// PdfWorker.cpp
//
// Модуль обробки одного PDF.
//
//======================================================

#include "PdfWorker.h"

#include "PdfReader.h"
#include "Renamer.h"

//======================================================
// Обробити один PDF.
//
//======================================================

void processPdf(
    PdfInfo& pdf,
    const std::string& folder,
    const std::unordered_map<
        std::string,
        std::string>& excelTable)
{
    //----------------------------------------------
    // Зчитати ІПН
    //----------------------------------------------

    pdf.ipn = extractIpn(pdf.fullPath);

    //----------------------------------------------
    // ІПН не знайдено
    //----------------------------------------------

    if (pdf.ipn.empty())
    {
        if (moveToNotFound(pdf.fullPath))
        {
            pdf.status = "NOT_FOUND";
            pdf.resultPath =
                "Не знайдено/" +
                pdf.fileName;
        }
        else
        {
            pdf.status = "ERROR";
        }

        return;
    }

    //----------------------------------------------
    // Пошук ІПН
    //----------------------------------------------

    auto it = excelTable.find(pdf.ipn);

    if (it == excelTable.end())
    {
        if (moveToNotFound(pdf.fullPath))
        {
            pdf.status = "NOT_FOUND";
            pdf.resultPath =
                "Не знайдено/" +
                pdf.fileName;
        }
        else
        {
            pdf.status = "ERROR";
        }

        return;
    }

    //----------------------------------------------
    // Знайдено ПІБ
    //----------------------------------------------

    pdf.foundInExcel = true;
    pdf.newFileName = it->second;

    //----------------------------------------------
    // Перейменування
    //----------------------------------------------

    if (renamePdf(
            pdf.fullPath,
            folder,
            pdf.newFileName))
    {
        pdf.status = "RENAMED";

        pdf.resultPath =
            pdf.newFileName +
            ".pdf";
    }
    else
    {
        if (moveToDuplicates(
                pdf.fullPath,
                pdf.newFileName))
        {
            pdf.status = "DUPLICATE";

            pdf.resultPath =
                "Повтори/" +
                pdf.newFileName +
                "/" +
                pdf.fileName;
        }
        else
        {
            pdf.status = "ERROR";
        }
    }
}