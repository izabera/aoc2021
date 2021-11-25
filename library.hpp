#pragma once
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s, const std::string& delim = " \t\n");
std::vector<std::string> split(const std::string& s, char delim = ' ');
