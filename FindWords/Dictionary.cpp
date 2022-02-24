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

	root = std::make_unique<TrieNode>();

	std::string text;
	while (std::getline(english_dictionary, text)) {
		if (CheckValidWord(text)) {
			throw std::invalid_argument("non alpha characters in dictionary file");
		}
		TrieInsert(text);
	}

	if (root == nullptr) {
		throw std::invalid_argument("no words in dictionary: " + filename);
	}
}

bool Dictionary::CheckWordsCouldExist(const std::string& word) const {
	return TriePrefix(word);
}

bool Dictionary::CheckWordExists(const std::string& word) const {
	return TrieLookup(word);
}

bool Dictionary::CheckValidWord(const std::string& word) {
	// Not most robust string checking, but placed into function to allow for easier refactoring.
	return word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos;
}

/*
Reference for Trie structure:
https://www.techiedelight.com/cpp-implementation-trie-data-structure/

Trie structure was used to allow the program to quickly determine if a word can possibly exist.
Could be moved to a more generic Trie class/struct in the future.
*/


void Dictionary::TrieInsert(const std::string& word) {
	TrieNode* current = root.get();
	for (int i = 0; i < word.length(); i++) {
		if (current->children[word[i] - s_AlphabetStart].get() == nullptr) {
			current->children[word[i] - s_AlphabetStart] = std::make_unique<TrieNode>();
		}
		current = current->children[word[i] - s_AlphabetStart].get();
	}
	current->end_of_word = true;
}

bool Dictionary::TrieLookup(const std::string& word) const {
	TrieNode* current = root.get();
	for (int i = 0; i < word.length(); i++)
	{
		if (current->children[word[i] - s_AlphabetStart].get() == nullptr) {
			return false;
		}
		current = current->children[word[i] - s_AlphabetStart].get();
	}
	return current->end_of_word;
}

bool Dictionary::TriePrefix(const std::string& word) const {
	TrieNode* current = root.get();

	for (int i = 0; i < word.length(); i++)
	{
		if (current->children[word[i] - s_AlphabetStart] == nullptr) {
			return false;
		}
		current = current->children[word[i] - s_AlphabetStart].get();
	}

	for (int i = 0; i < s_AlphabetSize; i++) {
		if (current->children[i] != nullptr) {
			return true;
		}
	}
	return true;
}




