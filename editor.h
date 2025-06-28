#pragma once
#include "utility.h"
using namespace std;

class editor {
private:
    vector<string> lines;
    int cursorRow;
    int cursorCol;

    string toUpperCase(const std::string& str) {
        string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
    string toLowerCase(const std::string& str) {
        string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    vector<string> splitIntoWords(const std::string& line) {
        std::vector<std::string> words;
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            words.push_back(word);
        }
        return words;
    }
    unordered_map<char, int> getCharFrequency(const std::string& word) {
        std::unordered_map<char, int> freq;
        for (char c : word) {
            if (std::isalpha(c)) { // Consider only alphabets
                freq[std::tolower(c)]++;
            }
        }
        return freq;
    }
    bool canFormWord(const std::unordered_map<char, int>& baseFreq, const std::string& word) {
        auto wordFreq = getCharFrequency(word);
        for (auto it = wordFreq.begin(); it != wordFreq.end(); ++it) {
            char charKey = it->first;
            int count = it->second;

            if (baseFreq.find(charKey) == baseFreq.end() || baseFreq.at(charKey) < count) {
                return false;
            }
        }
        return true;
    }
public:
    editor();

    void insertChar(char ch);       // Insert a character at the current cursor position    
    void insertNewLine();           // Insert a new line at the current cursor position
    void toUpperCurrentWord();      // Convert the current word to uppercase
    void toLowerCurrentWord();      // Convert the current word to lowercase
    void replaceFirst(const std::string& oldWord, const std::string& newWord);      // Find and replace the first occurrence of a word
    void replaceAll(const std::string& oldWord, const std::string& newWord);        // Find and replace all occurrences of a word
    int  substringCount(const std::string& sub);                                    // Count occurrences of a substring
    void findWord(const std::string& word, bool caseSensitive = true);              // Find and print a word (case-sensitive)
    void printDocument() const;
    void saveToFile(const std::string& filename) const;

    void insertWord(const std::string& str);
    void insertSentence(const std::string& str);

    void replaceFromCursor(const std::string& oldWord, const std::string& newWord, bool forward = true, bool all = false);
    void findSentence(const std::string& sen, bool caseSensitive = true);

    void addLine(const std::string& line);
    int countSpecialCharacters();
    int sentenceCount();
    int paragraphCount();

    double AvgWordLength();
    int FindLargestWordLength();
    int FindSmallestWordLength();

    void AddPrefixtoWord(const string& word, const string& toAppend);
    void AddPostfixtoWord(const string& word, const string& toAppend);
    int countSubstringOccurrences(const std::string& substring);

    pair<string, int> findWordGameChampion();
};