#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <string>

bool isAnagram(const std::string &word1, const std::string &word2) {
    // words that aren't same length can't be anagrams
    if (word1.length() != word2.length()) {
        return false;
    }

    // try to falsify word2 contains all chars that are in word1
    for (char const c1 : word1) {
        // now look for c1 in c2
        bool foundChar = false;
		for (char const c2 : word2) {
            if (c1 == c2) {
                foundChar = true;
            }
        }

        if (foundChar == false) {
            return false;
        }
	}

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <FILE>" << std::endl;
        return 1;
    }

    std::string infileName = argv[1];

    std::ifstream infile;
    infile.open(infileName);
    if (!infile.is_open()) {
        std::cerr << "Could not open file " << infileName << std::endl;
        return 1;
    }


    std::unordered_set <std::string> words;
    std::string line;
    while (std::getline(infile, line)) {
        // skip commented
        if (line.rfind("#") == 0) {
            continue;
        }

        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        // skip blank
        if (line.empty()) {
            continue;
        }

        words.insert(line);
    }
    infile.close();


    // end init, start algo to return groups of anagram words
    std::unordered_set <std::string> handledWords;
    for (auto word : words) {
        if (handledWords.count(word) > 0) {
            continue;
        }

        std::vector<std::string> anagrams;
        anagrams.push_back(word);
        for (auto moreWord : words) {
            if (word == moreWord) {
                continue;
            }

            if (isAnagram(word, moreWord)) {
                anagrams.push_back(moreWord);
                handledWords.insert(moreWord);
            }
        }

        // show anagrams
        for (auto word : anagrams) {
            std::cout << word << ' ';
        }
        std::cout << std::endl;
    }
}