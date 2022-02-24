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
		bool contains_non_alpha = text.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos;
		if (contains_non_alpha) {
			throw std::invalid_argument("non alpha characters in dictionary file");
		}
		trie_insert(text);
	}

	if (root == nullptr) {
		throw std::invalid_argument("no words in dictionary: " + filename);
	}
}

bool Dictionary::CheckWordsCouldExist(const std::string& word) const {
	return trie_prefix(word);
}

bool Dictionary::CheckWordExists(const std::string& word) const {
	return trie_lookup(word);
}

void Dictionary::trie_insert(const std::string& word) {
	TrieNode* current = root.get();
	for (int i = 0; i < word.length(); i++) {
		if (current->children[word[i] - s_AlphabetStart].get() == nullptr) {
			current->children[word[i] - s_AlphabetStart] = std::make_unique<TrieNode>();
		}
		current = current->children[word[i] - s_AlphabetStart].get();
	}
	current->end_of_word = true;
}

bool Dictionary::trie_lookup(const std::string& word) const {
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

bool Dictionary::trie_prefix(const std::string& word) const {
	TrieNode* current = root.get();
	// For each letter, iterate through the trie
	for (int i = 0; i < word.length(); i++)
	{
		if (current->children[word[i] - s_AlphabetStart] == nullptr) {
			return false;
		}
		current = current->children[word[i] - s_AlphabetStart].get();
	}

	// Check if there are any nodes attached to last node of word
	for (int i = 0; i < s_AlphabetSize; i++) {
		if (current->children[i] != nullptr) {
			return true;
		}
	}
	return true;
}




