#include <iostream>
#include "file.h"
#include "directory.h"
#include "dos.h"
#include "editor.h"
using namespace std;

void dirTest() {
    directory* root = new directory("root");
    directory* subdir1 = new directory("subdir1");
    directory* subdir2 = new directory("subdir2");
    directory* subdir3 = new directory("subdir3");

    root->addFile(new file("file1.txt"));
    root->addFile(new file("file2.txt"));

    file* fudge = new file("hawahawa.txt");
    file* banana = new file("file3.txt");
    subdir1->addFile(banana);
    subdir1->addFile(fudge);
    subdir1->remFile(fudge);
    subdir1->remFile(banana);

    subdir2->addFile(new file("file5.txt"));
    subdir2->addFile(new file("blahblah.txt"));

    subdir3->addFile(new file("anda.txt"));
    subdir3->addFile(new file("aandaay.txt"));

    // Adding subdirectories to the root directory
    root->addSubDirectory(subdir1);
    root->addSubDirectory(subdir2);
    root->addSubDirectory(subdir3);
    root->delSubDirectory(subdir2);

    // Displaying the tree structure
    root->tree();

    cout << endl;
    if (subdir3->find_file_with_name("asjanda.txt")) {
        cout << "hehe";
    }
    else {
        cout << "ugh";
    }
}
void dosTest() {
    dos myDos; // Create an instance of the dos class

    cout << "Testing DOS class functionality:\n";

    // Test root directory
    myDos.pwd(); // Should print "V:\>"
    cout << endl;

    // Test creating directories
    myDos.mkdir("Dir1");
    myDos.mkdir("Dir2");
    myDos.pwd(); // Still should be "V:\>"
    cout << endl;

    // Test changing directories
    myDos.cd("Dir1");
    myDos.pwd(); // Should print "V:\Dir1"
    cout << endl;

    // Test creating files
    myDos.createFile("file1.txt");
    myDos.createFile("file2.txt");
    myDos.dir(); // Should list "file1.txt", "file2.txt"

    // Test returning to parent directory
    myDos.cd_to_parent();
    myDos.pwd(); // Should print "V:\>"
    cout << endl;

    // Test creating a nested directory
    myDos.cd("Dir2");
    myDos.mkdir("NestedDir");
    myDos.cd("NestedDir");
    myDos.pwd(); // Should print "V:\Dir2\NestedDir"
    cout << endl;

    // Test deleting a file
    myDos.cd_root();
    myDos.cd("Dir1");
    myDos.deleteFile("file1.txt");
    myDos.dir(); // Should list only "file2.txt"

    // Test listing directories and files with dir command
    myDos.cd_root();
    myDos.dir(); // Should list "Dir1", "Dir2"

    // Test displaying the directory tree
    myDos.Tree(); // Should display the structure of all directories and files

    // Test help command
    myDos.help(); // Should display available commands
}


void p() {
    cout << "===================================================================================================" << endl;
}

void editorTest() {
    editor doc;

    doc.insertChar('H');
    doc.insertChar('e');
    doc.insertChar('l');
    doc.insertChar('l');
    doc.insertChar('o');
    doc.insertNewLine();
    doc.insertChar('W');
    doc.insertChar('o');
    doc.insertChar('r');
    doc.insertChar('l');
    doc.insertChar('d');

    doc.printDocument();
    cout << "===========" << endl;

    doc.toUpperCurrentWord();
    doc.printDocument();
    cout << "===========" << endl;

    doc.toLowerCurrentWord();
    doc.printDocument();
    cout << "===========" << endl;

    doc.replaceFirst("Hello", "hi");
    doc.printDocument();
    cout << "===========" << endl;

    doc.replaceAll("l", "L");
    doc.printDocument();
    cout << "===========" << endl;

    cout << endl << endl;
    std::cout << "substring 'l' occurs " << doc.substringCount("l") << " times." << std::endl;

    string strtofind = "hi";
    doc.findWord(strtofind, false);

    string strtofind2 = "world";

    doc.findWord(strtofind2, true);

    string strtofind3 = "worLd";
    doc.findWord(strtofind3, true);
    cout << endl << endl;
    //doc.saveToFile("t1.txt");

    doc.insertSentence(" and this is history class");
    doc.printDocument();
    cout << "===========" << endl;

    doc.replaceFromCursor("hi", "hello", false, true);
    doc.printDocument();
    cout << "===========" << endl;

    doc.replaceFromCursor("history", "maths", false, true);
    doc.printDocument();
    cout << "===========" << endl;

    doc.findSentence("this is maths class", false);

    //cout << "===================================================================================================" << endl;
    //p();
    //doc.insertSentence("Hideaway\n\n Come on, baby\nWe’ll make it alright\nBring your speaker & a bottle of white\nWe’ll go walking in Marina like last time\nTo the beaches that nobody else likes \n\n\n& you’ll put your arms around me\n& take me back into that hideaway\n& you’ll give your love into me\n& take me back into that hideaway\n\nNow the sun’s out, we’re feeling its sweet light\nWaves are crashing, they’re flying those long kites\n& I can see it, I can see where our lives go\nSee us sailing across so many oceans…");
    
  
}

void editorPart2() {
    editor doc;

    cout << "-----------------------------  NEW FILE TEXT ----------------------------" << endl << endl;
    doc.insertSentence("Hello, world! This is a test.");
    doc.addLine("Another abc sentence is here.");
    doc.addLine("");
    doc.addLine("");
    doc.addLine("abc is the word to change.");
    doc.addLine("Find the largest and smallest words.");
    doc.addLine("^$@ and _+");

    doc.printDocument();
    p();

    // Average Word Length
    double avgLength = doc.AvgWordLength();
    std::cout << "\nAverage word length: " << avgLength << std::endl;

    // Largest Word Length
    int largestWord = doc.FindLargestWordLength();
    std::cout << "Largest word length: " << largestWord << std::endl;

    // Smallest Word Length
    int smallestWord = doc.FindSmallestWordLength();
    std::cout << "Smallest word length: " << smallestWord << std::endl;

    // Count lines
    int lineCount = doc.sentenceCount();
    std::cout << "Line count (based on periods): " << lineCount << std::endl;

    // Count paragraphs
    int paragraphCount = doc.paragraphCount();
    std::cout << "Paragraph count (based on double empty lines): " << paragraphCount << std::endl;

    cout << "special char count: " << doc.countSpecialCharacters() << endl;


    p();
    cout << endl;
    editor ed;

    // Adding lines
    ed.addLine("encyclopaedia example cycle pod clad");
    ed.addLine("contains many different words.");

    // Word-Game Champion
    auto champion = ed.findWordGameChampion();
    std::cout << "Word-Game Champion: " << champion.first << " (can form " << champion.second << " words)" << std::endl;

}

int main() {
   // dirTest();
  //  dosTest();

    editorTest();
   // editorPart2();
	return 0;
}