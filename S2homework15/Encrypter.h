#pragma once
#include <string>
#include <fstream>

class Encrypter
{
	int keyCrypter;
	std::string file;
	char c;
public:
	void encrypt();
	void decrypt();
	void setKeyCrypter(int key);
	void setFileName(std::string fileName);
};



