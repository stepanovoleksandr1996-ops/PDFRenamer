#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string>
readCsv(const std::string& csvFile);

#endif