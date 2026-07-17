#ifndef PDFREADER_H
#define PDFREADER_H

#include <string>

// Відкриває PDF,
// знаходить ІПН,
// повертає його у вигляді рядка.
std::string extractIpn(const std::string& pdfFile);

#endif