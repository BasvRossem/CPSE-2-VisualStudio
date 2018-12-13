#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <map>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cmath>

void fileToVector(std::ifstream & myFile, std::vector<char> & myVector) {
	char currentChar;
	while (!myFile.eof()) {
		myFile.get(currentChar);
		myVector.push_back(currentChar);
	}
}

bool customIsAlpha(char c) {
	std::locale loc;
	if (std::isalpha(c, loc)) {
		return true;
	}
	return false;
}

void makeVectorLowercase(std::vector<char> & myVector) {
	for (unsigned int i = 0; i < myVector.size(); i++) {
		if (customIsAlpha(myVector[i])) {
			myVector[i] = tolower(myVector[i]);
		}
	}
}

void countAll(std::vector<char> & myVector, std::map<std::string, int> & wordMap, std::map<char, int> & letterMap) {
	std::string myWordString = "";
	for (char & character : myVector) {
		if (customIsAlpha(character)) {
			myWordString.push_back(character);
			if (letterMap.find(character) == letterMap.end()) {
				letterMap[character] = 1;
			}
			else {
				letterMap[character] += 1;
			}
		}
		else if (myWordString.size() > 0) {
			if (wordMap.find(myWordString) == wordMap.end()) {
				wordMap[myWordString] = 1;
			}
			else {
				wordMap[myWordString] += 1;
			}
			myWordString = "";
		}
	}
}

std::map<std::string, int> countWords(std::vector<char> & bibleVector) {
	std::string myString = "";
	std::map<std::string, int> myMap;
	for (auto character : bibleVector) {
		
		if (customIsAlpha(character)) {
			myString.push_back(character);
		}
		else if (myString.size() > 0){
			if (myMap.find(myString) == myMap.end()) {
				myMap[myString] = 1;
			}
			else {
				myMap[myString] += 1;
			}
			myString = "";
		}

	}
	
	return myMap;
}

template<typename T>
std::vector<std::pair<T, int>> mapToSortedVector(std::map<T, int> & myMap) {
	std::vector<std::pair<T, int>> myVector(myMap.size());
	std::partial_sort_copy(myMap.begin(),
		myMap.end(),
		myVector.begin(),
		myVector.end(),
		[](std::pair<T, int> const& left,
			std::pair<T, int> const& right)
	{
		return left.second > right.second;
	});
	return myVector;
}

void coutMapAndVectorOfSameSize(std::map<char, int> & myMap, std::vector<std::pair<char, int>> & myVector) {
	int iteration = 0;
	int maxValue = myVector[0].second;
	std::string maxString = std::to_string(maxValue);
	int spacing = maxString.size() + 6;
	std::cout << maxValue << std::endl;
	std::cout << maxString.size() << std::endl;
	std::cout << spacing << std::endl;

	for (auto const & element : myMap) {
		std::ostringstream mapStream;
		mapStream
			<< "{ "
			<< element.first
			<< ", "
			<< element.second;
		std::string mapString = mapStream.str();
		mapString.append(spacing - mapString.length(), ' ');
		mapString.append(1, '}');
		mapString.append(spacing + 5 - mapString.length(), ' ');

		std::ostringstream vectorStream;
		vectorStream
			<< "{ "
			<< myVector[iteration].first
			<< ", "
			<< myVector[iteration].second;
		std::string vectorString = vectorStream.str();
		vectorString.append(spacing - vectorString.length(), ' ');
		vectorString.append(1, '}');

		std::cout << mapString;
		std::cout << vectorString;
		std::cout << std::endl;
		iteration++;
	}
}

int main(){
	
	std::vector<char> bibleVector = {};
	std::ifstream bibleFile;
	bibleFile.open("bible2.txt");
	fileToVector(bibleFile, bibleVector);
	bibleFile.close();

	int amountOfCharacters = bibleVector.size();
	int amountOfLines = std::count(bibleVector.begin(), bibleVector.end(), '\n');
	int amountOfAlphabet = std::count_if(bibleVector.begin(), bibleVector.end(), customIsAlpha);
	
	makeVectorLowercase(bibleVector);


	std::map<char, int> letterCount;
	std::map<std::string, int> mapOfWords;
	
	

	countAll(bibleVector, mapOfWords, letterCount);
	

	std::vector<std::pair<char, int>> alphabetByValues = mapToSortedVector(letterCount);
	std::vector<std::pair<std::string, int>> wordsByValues = mapToSortedVector(mapOfWords);
	

	std::cout << "Part 1)" << "Done" << std::endl;
	std::cout << "Part 2)" << amountOfCharacters << std::endl;
	std::cout << "Part 3)" << amountOfLines << std::endl;
	std::cout << "Part 4)" << amountOfAlphabet << std::endl;
	std::cout << "Part 5)" << "Done" << std::endl;
	std::cout << "Part 6)" << "Done" << std::endl;
	std::cout << "Part 7)" << std::endl;
	coutMapAndVectorOfSameSize(letterCount, alphabetByValues);
	std::cout << "Part 8)" << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout
			<< "{ "
			<< wordsByValues[i].first
			<< ", "
			<< wordsByValues[i].second
			<< " }"
			<< std::endl;
	}

	system("pause");
	return 0;

	/*Use this to time function
	clock_t time_req = clock();
	fuction to time
	time_req = clock() - time_req;
	std::cout << "Using pow function, it took " << (float)time_req / CLOCKS_PER_SEC << " seconds" << std::endl;*/
}