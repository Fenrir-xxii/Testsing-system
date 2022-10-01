#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class FileCryptor 
{
	int shift = 20;
public:
	void cryptDirectory(const fs::path& dir);
	void decryptDirectory(const fs::path& dir);
	void crypt(const fs::path& file);
	void decrypt(fs::path cryptedFile);
};