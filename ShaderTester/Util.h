#pragma once
#include <string>
#include <fstream>

inline bool Exists(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}