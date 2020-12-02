
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <cstdlib>

#include "page.h"
#include "cyoa.h"

// Constructor:
// Parameter(s): the filename
// Modifies: all fields in the Page class (initialized)
Page::Page(std::string & filename) : num(0), text(), exist(true),
                        navi(NO_NAVI), choices(), prev(-1) {
    initPage(filename);
}

// Constructor: 
// Parameter(s): the directory name, the page number
// Modifies: all fields in the Page class (initialized)
Page::Page(std::string & directory, unsigned pageNum) : num(pageNum),
                                                        text(),
                                                        exist(true),
                                                        navi(NO_NAVI),
                                                        choices(),
                                                        prev(-1) {
    std::string filename = directory + "/" + "page" + unsignToStr(pageNum) + ".txt";
    initPage(filename);
}

// Assignment operator:
// Modifies: all fields in the Page class
Page & Page::operator= (const Page & rhs) {
    if (this != &rhs) {
        num = rhs.num;
        text = rhs.text;
        exist = rhs.exist;
        navi = rhs.navi;
        choices = rhs.choices;
        prev = rhs.prev;
    }
    return *this;
}

// initPage: check whether the file was successfully opened;
//      initialization of pageFile and choices
// Modifies: pageFile, navi, choices
void Page::initPage(std::string & filename) {
    std::ifstream pageFile;
    readFile(pageFile, filename.c_str());
    if (pageFile.fail()) {
        exist = false;
        return;
    }
    getNaviChoices(pageFile);
    if (navi == NO_NAVI) {
        formatErr("No navi available");
    }
    getText(pageFile);
    return;
}

// getText: read the text and put it into the text field
// Modifies: text
void Page::getText(std::ifstream & pageFile) {
    int c;
    while ((c = pageFile.get()) != EOF) {
        text += (char) c;
    }
    pageFile.close();
    return;
}


// getNavi: set the navi according to the content of files
// Modifies: navi, choices
void Page::getNaviChoices(std::ifstream & pageFile) {
    unsigned rank = 1;
    std::string line;
    while (std::getline(pageFile, line)) {
        if (rank == 1 && (line == "WIN" || line == "LOSE")) {
            // Check whether a page is win or lose
            if (line == "WIN") {
                navi = WIN;
            }
            else {
                navi = LOSE;
            }
            std::getline(pageFile, line);
            if (line[0] != '#') {
                formatErr();
            }
            return;
        }
        if (line[0] == '#') {
            return;
        }
        navi = CHOICES;
        addSingleChoice(line, rank);
        rank++;
    }
    return;
}

// addSingleChoice: read a line, add the information to 
//      choices
void Page::addSingleChoice(std::string & line, unsigned rank) {
    std::string::size_type colonPos = line.find(":");
    if (colonPos == line.npos) {
        formatErr();
    }
    std::string pageNumStr = line.substr(0, colonPos);
    if (!isAllDigits(pageNumStr)) {
        formatErr("Invalid choice");
    }
    std::string choiceContent = line.substr(colonPos + 1, line.size() - colonPos);
    unsigned pageNum = strToUnsign(pageNumStr);
    if (pageNum == 0) {
        formatErr("Zero choice num");
    }
    choices[rank] = std::make_pair(strToUnsign(pageNumStr), choiceContent);
    return;
}

// isExist: help to check whether the file exists
bool Page::isExist() const {
    return exist;
}

// printText: print the text of the story
// Output(s): the text of the story, to stdout
void Page::printText() {
    std::cout << text;
    return;
}

// printWinLose: print the result of the story; should only
//      be called when navi is either WIN or LOSE
// Output(s): win or lose message, to stdout
void Page::printWinLose() {
    if (navi == WIN) {
        std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else {
        std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    return;
}

// printWinLose: print the result of the story; should only
//      be called when navi is CHOICES
// Output(s): the choices, to stdout
void Page::printChoices() {
    std::cout << "What would you like to do?" << std::endl << std::endl;
    for (unsigned i = 1; i <= choices.size(); i++) {
        std::cout << " " << i << ". "
                        << choices.find(i)->second.second << std::endl;
    }
    return;
}

// printPage: print the content of a page
// Output(s): content of page, to stdout
void Page::printPage() {
    printText();
    std::cout << std::endl;
    if (navi == WIN || navi == LOSE) {
        printWinLose();
    }
    else {
        printChoices();
    }
    return;
}

// getChoices: get the choices
const choices_t & Page::getChoices() const {
    return choices;
}

// getNavi: get the navigation type
navi_t Page::getNavi() const {
    return navi;
}

// setPrev: set the prev page
// Parameter(s): the value that will be set to the prev field
// Modifies: prev
void Page::setPrevAndChoice(int thisPrev, int thisChoice) {
    prev = thisPrev;
    choiceToHere = thisChoice;
    return;
}

// getPrev: get the prev page num
int Page::getPrev() const {
    return prev;
}

// getChoice: get the prev page num
int Page::getChoice() const {
    return choiceToHere;
}