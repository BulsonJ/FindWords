#include <string>
#include <set>
#include <unordered_set>
#include <memory>

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

	struct TrieNode {
		std::unique_ptr<TrieNode> children[Dictionary::s_AlphabetSize];
		bool end_of_word = false;
	};

	std::unique_ptr<TrieNode> root;

	void trie_insert(const std::string& word);
	bool trie_lookup(const std::string& word) const;
	bool trie_prefix(const std::string& word) const;
};




