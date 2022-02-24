#pragma once
#include <vector>
#include <string>
#include "Dictionary.h"

class LetterWheels
{
public:
	LetterWheels(const std::string& wheelFile, const Dictionary& dictionary) throw ();

	std::vector<std::string> FindWords();
protected:
	const Dictionary& dict;
	static const int s_MinWordSize = 2;

	std::vector<std::vector<char>> wheels;

	std::string currentCombination;
	std::vector<std::string> finalWords;

	void FindWordsFromWheel(int wheel_index);
};

