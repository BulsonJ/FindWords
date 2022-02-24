#include <string>
#include <set>
#include <unordered_set>
#include <memory>
#include "Trie.h"

#pragma once

class Dictionary
{
public:
	Dictionary(const std::string& filename) throw ();

	bool CheckWordExists(const std::string& word) const;
	bool CheckWordsCouldExist(const std::string& word) const;

protected:
	static const int s_AlphabetSize = 26;
	static const int s_AlphabetStart = 97;

	std::unique_ptr<Trie<s_AlphabetSize, s_AlphabetStart>>root;

	static bool CheckValidWord(const std::string& word);


};




