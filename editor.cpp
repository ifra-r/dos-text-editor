#include "editor.h"
using namespace std;

editor::editor() : cursorRow(0), cursorCol(0) {
    lines.emplace_back("");
}

// Insert a character at the current cursor position
void editor::insertChar(char ch) {
    if (lines.empty()) lines.emplace_back("");
    if (cursorRow >= lines.size()) cursorRow = lines.size() - 1;
    if (cursorCol > lines[cursorRow].size()) cursorCol = lines[cursorRow].size();
    lines[cursorRow].insert(cursorCol, 1, ch);
    cursorCol++;
}

// Insert a new line at the current cursor position
void editor::insertNewLine() {
    std::string& currentLine = lines[cursorRow];
    std::string newLine = currentLine.substr(cursorCol);
    currentLine.erase(cursorCol);
    lines.insert(lines.begin() + cursorRow + 1, newLine);
    cursorRow++;
    cursorCol = 0;
}

// Convert the current word to uppercase
void editor::toUpperCurrentWord() {
    if (lines.empty()) return;
    std::string& currentLine = lines[cursorRow];
    if (cursorCol > currentLine.size()) return;

    int start = cursorCol;
    while (start > 0 && std::isalnum(currentLine[start - 1])) start--;
    int end = cursorCol;
    while (end < currentLine.size() && std::isalnum(currentLine[end])) end++;

    std::string word = currentLine.substr(start, end - start);
    currentLine.replace(start, end - start, toUpperCase(word));
}

// Convert the current word to lowercase
void editor::toLowerCurrentWord() {
    if (lines.empty()) return;
    std::string& currentLine = lines[cursorRow];
    if (cursorCol > currentLine.size()) return;

    int start = cursorCol;
    while (start > 0 && std::isalnum(currentLine[start - 1])) start--;
    int end = cursorCol;
    while (end < currentLine.size() && std::isalnum(currentLine[end])) end++;

    std::string word = currentLine.substr(start, end - start);
    currentLine.replace(start, end - start, toLowerCase(word));
}

// Find and replace the first occurrence of a word
void editor::replaceFirst(const std::string& oldWord, const std::string& newWord) {
    for (auto& line : lines) {
        size_t pos = line.find(oldWord);
        if (pos != std::string::npos) {
            line.replace(pos, oldWord.length(), newWord);
            return;
        }
    }
}

// Find and replace all occurrences of a word
void editor::replaceAll(const std::string& oldWord, const std::string& newWord) {
    for (auto& line : lines) {
        size_t pos;
        while ((pos = line.find(oldWord)) != std::string::npos) {
            line.replace(pos, oldWord.length(), newWord);
            cursorCol = cursorCol - oldWord.length() + newWord.length();
            if (cursorCol > line.length())
                cursorCol = line.length();
        }
    }    
}

// Count occurrences of a substring
int editor::substringCount(const std::string& sub) {
    int count = 0;
    for (const auto& line : lines) {
        size_t pos = 0;
        while ((pos = line.find(sub, pos)) != std::string::npos) {
            count++;
            pos += sub.length();
        }
    }
    return count;
}

// Find and print a word (case-sensitive)
void editor::findWord(const std::string& _word, bool caseSensitive) {
    const string& word = _word;
    const string& wordLowCase = toLowerCase(word);
    bool isFound = false;
    for (size_t i = 0; i < lines.size(); ++i) {
        std::string line = lines[i];
        size_t pos;
        if (caseSensitive)
             pos = line.find(word);
        else if (!caseSensitive)
             pos = line.find(word);
        if (pos != std::string::npos) {
            std::cout << "\"" << word << "\" Found at line " << i + 1 << std::endl;
            isFound = true;
        }
    }
    if (isFound == false)
        cout << "\"" << word << "\" not found" << endl;
}

// Print the document
void editor::printDocument() const {

    if (cursorRow < 0 || cursorRow >= lines.size()) {
        std::cerr << "Invalid cursor position!" << std::endl;
        return;
    }

    for (int i = 0; i < lines.size(); ++i) {
        if (i == cursorRow) {
            if (cursorCol < 0 || cursorCol > lines[i].length()) {
                std::cerr << "Invalid cursor column!" << std::endl;
                return;
            }
            std::cout << lines[i].substr(0, cursorCol) << "|" << lines[i].substr(cursorCol) << std::endl;
        }
        else {
            std::cout << lines[i] << std::endl;
        }
    }
}
// Save document to a file
void editor::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    for (const auto& line : lines) {
        outFile << line << "\n";
    }
    outFile.close();
}

void editor::insertWord(const std::string& str) {
    //insertChar(' ');    //space before word
    for (char ch : str)
        insertChar(ch);
}
void editor::insertSentence(const std::string& str) {
    for (char ch : str)
        insertChar(ch);
}
// Find and replace from the current cursor position
void editor::replaceFromCursor(const std::string& oldWord, const std::string& newWord, bool forward, bool all) {
    if (lines.empty() || oldWord.empty()) return;

    // Save the starting cursor position
    int originalRow = cursorRow;
    int originalCol = cursorCol;
    std::string& line = lines[cursorRow];
    do {
        if (cursorRow < 0 || cursorRow >= lines.size()) break; // Ensure cursorRow is within valid bounds
        //line = lines[cursorRow];

        // Ensure cursorCol is within the bounds of the current line
        if (cursorCol < 0 || cursorCol > line.length()) break;

        size_t pos = forward ? line.find(oldWord, cursorCol) : line.rfind(oldWord, cursorCol);

        if (pos != std::string::npos) {
            // Ensure it's a whole word match
            bool isWholeWord = true;
            if (pos > 0 && std::isalnum(line[pos - 1])) {
                isWholeWord = false; // Character before is alphanumeric
            }
            if (pos + oldWord.length() < line.length() && std::isalnum(line[pos + oldWord.length()])) {
                isWholeWord = false; // Character after is alphanumeric
            }

            if (isWholeWord) {
                // Replace the word
                line.replace(pos, oldWord.length(), newWord);
                cursorCol = cursorCol - oldWord.length() + newWord.length();        // update cursor pos cause paeen you changung wrds toh bera gark hojaye ga
                if (!all) break;                // Stop if only replacing the first match
            }
            else {
                // Skip past the current non-whole match
                cursorCol = forward ? pos + oldWord.length() : (pos > 0 ? pos - 1 : 0);
            }
        }
        else {
            // No match in the current line, move to the next/previous line
            cursorRow += forward ? 1 : -1;

            // Ensure cursorRow is within bounds of the line range
            if (cursorRow < 0 || cursorRow >= lines.size()) break;
            // Reset cursorCol for the next line, and ensure it's within the line's bounds
            cursorCol = forward ? 0 : lines[cursorRow].size();
        }
    } while (all);

    // Restore the cursor to its original position
    cursorRow = originalRow;
    cursorCol = originalCol;

    // If cursorCol exceeds line length, adjust the line length
    if (cursorCol > line.length()) {
        cursorCol = line.length();  // Ensure cursorCol doesn't exceed the new line length
    }
}
void editor::findSentence(const std::string& sen, bool caseSensitive) {
    findWord(sen, caseSensitive);
}

void editor::addLine(const std::string& line) {
    lines.push_back(line);
}
// Calculates the average word length in the text
double editor::AvgWordLength() {
    int totalLength = 0, wordCount = 0;
    for (const auto& line : lines) {
        auto words = splitIntoWords(line);
        for (const auto& word : words) {
            totalLength += word.length();
            wordCount++;
        }
    }
    return wordCount > 0 ? static_cast<double>(totalLength) / wordCount : 0.0;
}
int editor::FindLargestWordLength() {
    int maxLength = 0;
    for (const auto& line : lines) {
        auto words = splitIntoWords(line);
        for (const auto& word : words) {
            maxLength = max(maxLength, static_cast<int>(word.length()));
        }
    }
    return maxLength;
}
int editor::FindSmallestWordLength() {
    int minLength = INT_MAX;
    for (const auto& line : lines) {
        auto words = splitIntoWords(line);
        for (const auto& word : words) {
            minLength = min(minLength, static_cast<int>(word.length()));
        }
    }
    return minLength == INT_MAX ? 0 : minLength; // Return 0 if no words found
}
int editor::countSpecialCharacters() {
    int spCount = 0;
    for (const auto& line : lines) {  
        for (char c : line) {
            if (!isalnum(c) && !isspace(c))
                spCount++;
        }
    }
    return spCount;
}
int editor::sentenceCount() {
    int count = 0;
    for (const auto& line : lines) {
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '.')
                count++;
        }
    }
    return count;
}
int editor::paragraphCount() {
    //int count = 0;
    //for (const auto& line : lines) {
    //    for (int i = 0; i < line.length(); ++i) {
    //        if (i-1<line.length() && line[i] == '\n' && line[i+1] == '\n')
    //            count++;
    //    }
    //}
    int count = 0;
    bool inParagraph = false;
    for (const auto& line : lines) {
        if (line.empty()) {
            if (inParagraph) {
                count++;
                inParagraph = false;
            }
        }
        else {
            inParagraph = true;
        }
    }
    // Count the last paragraph if the text doesn't end with empty lines
    if (inParagraph) {
        count++;
    }
    return count;
}

void editor::AddPrefixtoWord(const string& word, const string& toAppend) {
    string newWord = toAppend + word;
    replaceAll(word, newWord);
    //replaceFromCursor(word, newWord, true, true);
    //replaceFromCursor(word, newWord, false, true);
}
void editor::AddPostfixtoWord(const string& word, const string& toAppend) {
    string newWord = word + toAppend;
    replaceAll(word, newWord);
    //replaceFromCursor(word, newWord, true, true);
    //replaceFromCursor(word, newWord, false, true);
}

int editor::countSubstringOccurrences(const std::string& substring) {
    int count = 0;
    for (const auto& line : lines) {
        size_t pos = 0;
        // Search for the substring in the line
        while ((pos = line.find(substring, pos)) != std::string::npos) {
            count++;
            pos += substring.length();  // Move past the last found occurrence
        }
    }
    return count;
}
pair<string,int> editor::findWordGameChampion() {
    std::unordered_set<std::string> allWords; // Store all words in all lines
    for (const auto& line : lines) {
        auto words = splitIntoWords(line);
        allWords.insert(words.begin(), words.end());
    }
    pair<string, int> bestWord{ "", 0 }; // Word and count of words it can form
    for (const auto& candidate : allWords) {
        int count = 0;
        auto baseFreq = getCharFrequency(candidate);
        for (const auto& word : allWords) {
            if (candidate != word && canFormWord(baseFreq, word)) {
                count++;
            }
        }
        if (count > bestWord.second) {
            bestWord = { candidate, count };
        }
    }
    return bestWord;
}