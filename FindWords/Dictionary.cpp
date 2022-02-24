#include <fstream>
#include <algorithm>
#include <exception>
#include "Dictionary.h"

Dictionary::Dictionary(const std::string& filename) throw (std::invalid_argument) {
	std::ifstream english_dictionary;
	english_dictionary.open(filename);

	if (english_dictionary.fail()) {
		throw std::invalid_argument("no dictionary file available: " + filename);
	}

	root = std::make_unique<Trie<s_AlphabetSize, s_AlphabetStart>>();

	std::string text;
	while (std::getline(english_dictionary, text)) {
		if (CheckValidWord(text)) {
			throw std::invalid_argument("non alpha characters in dictionary file");
		}
		root->Insert(text);
	}

	if (root == nullptr) {
		throw std::invalid_argument("no words in dictionary: " + filename);
	}
}

bool Dictionary::CheckWordsCouldExist(const std::string& word) const {
	return root->Prefix(word);
}

bool Dictionary::CheckWordExists(const std::string& word) const {
	return root->Lookup(word);
}

bool Dictionary::CheckValidWord(const std::string& word) {
	// Not most robust string checking, but placed into function to allow for easier refactoring.
	return word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos;
}









