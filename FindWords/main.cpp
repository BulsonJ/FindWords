#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>
#include <memory>

#include "Dictionary.h"
#include "LetterWheels.h"

int main(int argc, char* argv[]) {

	if (argc != 3) {
		std::cout << "No wheel and/or dictionary files specified" << std::endl;
		std::cout << "Correct usage: find_words.exe wheels.txt dictionary.txt" << std::endl;
		exit(1);
	}

	// Load files and generate all possible words

	std::unique_ptr<Dictionary> dict;
	auto dictionaryLoadStart = std::chrono::high_resolution_clock::now();
	try {
		dict = std::make_unique<Dictionary>(argv[2]);
	}
	catch (std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
		exit(1);
	}
	auto dictionaryLoadEnd = std::chrono::high_resolution_clock::now();

	auto wheelLoadStart = std::chrono::high_resolution_clock::now();
	std::unique_ptr<LetterWheels> wheels;
	try {
		wheels = std::make_unique<LetterWheels>(argv[1], *dict);
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
		exit(1);
	}
	auto wheelLoadEnd = std::chrono::high_resolution_clock::now();

	auto wordGenStart = std::chrono::high_resolution_clock::now();
	std::vector<std::string> word_combinations = wheels->FindWords();
	auto wordGenEnd = std::chrono::high_resolution_clock::now();

	// Output results

	for (auto it = word_combinations.begin(); it != word_combinations.end(); it++) {
		std::string str = *it;
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		std::cout << str << std::endl;
	}

	std::cout << "Found " << word_combinations.size() << " words." << std::endl;

	auto textOutput = [](const std::string& label, const std::chrono::duration<float, std::milli>& time)
	{
		std::cout << label << time.count() << "ms" << std::endl; 
	};

	textOutput("Time to load dictionary & put into trie:", dictionaryLoadEnd - dictionaryLoadStart);
	textOutput("Time to load wheels:", wheelLoadEnd - wheelLoadStart);
	textOutput("Time to find words:", wordGenEnd - wordGenStart);
	textOutput("Total time:", wordGenEnd - dictionaryLoadStart);


	return 0;
}


