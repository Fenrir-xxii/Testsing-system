#include "Encrypter.h"


void Encrypter::encrypt()
{
	
	std::fstream fin;
	std::fstream fout;

	fin.open(file, std::fstream::in);
	fout.open("encrypt.txt", std::fstream::out);

	while (fin >> std::noskipws >> c) {
		int temp = (c + this->keyCrypter);
		fout << (char)temp;
	}

	fin.close();
	fout.close();
}

void Encrypter::decrypt()
{
	std::fstream fin;
	std::fstream fout;
	fin.open("encrypt.txt", std::fstream::in);
	fout.open("decrypt.txt", std::fstream::out);

	while (fin >> std::noskipws >> c) {

		// Remove the key from the
		// character
		int temp = (c - this->keyCrypter);
		fout << (char)temp;
	}

	fin.close();
	fout.close();
}

void Encrypter::setKeyCrypter(int key)
{
	this->keyCrypter = key;
}

void Encrypter::setFileName(std::string fileName)
{
	this->file = fileName;
}

