#pragma once
#include <memory>

/*
Reference for Trie structure:
https://www.techiedelight.com/cpp-implementation-trie-data-structure/

Trie structure was used to allow the program to quickly determine if a word can possibly exist.

Template class used to allow for different sizes of Trie to be created, depending on the alphabet size and
where the alphabet starts(in ASCII). 

I used this as I believe data structures are a helpful place to use templates,and this class should not 
need to be recompiled often. It does have the downside of needing to know the size and startof the alphabet
at compile time, but I thought this trade off was worth it.
*/

template
<uint32_t alphabetSize, uint32_t alphabetStart>
class Trie
{
public:

	void Insert(Trie* root, const std::string& word) {
		Trie* current = root;
		for (int i = 0; i < word.length(); i++) {
			if (current->children[word[i] - alphabetStart].get() == nullptr) {
				current->children[word[i] - alphabetStart] = std::make_unique<Trie>();
			}
			current = current->children[word[i] - alphabetStart].get();
		}
		current->end_of_word = true;
	}

	bool Lookup(const std::string& word) const {
		const Trie* current = this;
		for (int i = 0; i < word.length(); i++)
		{
			if (current->children[word[i] - alphabetStart].get() == nullptr) {
				return false;
			}
			current = current->children[word[i] - alphabetStart].get();
		}
		return current->end_of_word;
	}

	bool Prefix(const std::string& word) const {
		const Trie* current = this;

		for (int i = 0; i < word.length(); i++)
		{
			if (current->children[word[i] - alphabetStart] == nullptr) {
				return false;
			}
			current = current->children[word[i] - alphabetStart].get();
		}

		for (int i = 0; i < alphabetSize; i++) {
			if (current->children[i] != nullptr) {
				return true;
			}
		}
		return true;
	}
protected:
	std::unique_ptr<Trie> children[alphabetSize];
	bool end_of_word = false;
};

