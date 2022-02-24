#include "LetterWheels.h"
#include <chrono>
#include <fstream>
#include <exception>

LetterWheels::LetterWheels(const std::string& wheelFile, const Dictionary& dictionary) throw (std::invalid_argument) : dict(dictionary) {
	std::ifstream wheel_file;
	wheel_file.open(wheelFile);

	if (wheel_file.fail()) {
		throw std::invalid_argument("no wheel file available: " + wheelFile);
	}

	std::string line;
	std::getline(wheel_file, line);
	std::getline(wheel_file, line);

	int count = 0;
	while (std::getline(wheel_file, line)) {
		std::vector<char> single_wheel;
		for (int i = 0; i < line.size(); ++i) {
			single_wheel.emplace_back(tolower(line[i]));
		}
		wheels.emplace_back(single_wheel);
	}

	if (wheels.size() == 0) {
		throw std::invalid_argument("no wheels in file: " + wheelFile);
	}
}

/*
For cleaner method function, I decided to store the currentCombination and
finalWords vectors as part of the class. Another implementation would be to
pass by reference into each method call.
*/

void LetterWheels::FindWordsFromWheel(int wheel_index) {

	if (wheel_index == wheels.size()) {
		return;
	}

	const std::vector<char>& current_wheel = wheels[wheel_index];
	for (auto it = current_wheel.begin(); it < current_wheel.end(); it++) {
		currentCombination += (*it);

		// If words could exist, move to next wheel
		if (dict.CheckWordsCouldExist(currentCombination)) {
			if (currentCombination.size() >= s_MinWordSize && dict.CheckWordExists(currentCombination)) {
				finalWords.emplace_back(currentCombination);
			}

			FindWordsFromWheel(wheel_index + 1);
		}
		currentCombination.pop_back();
	}
}

std::vector<std::string> LetterWheels::FindWords() {
	if (finalWords.size() > 0) {
		finalWords.clear();
	}

	currentCombination.clear();
	for (int i = 0; i <= wheels.size() - s_MinWordSize; i++) {
		FindWordsFromWheel(i);
		currentCombination.clear();
	}

	return finalWords;

}