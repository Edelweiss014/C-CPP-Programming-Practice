
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <stack>

#include "story.h"

// Constructor:
// Parameter(s): a C-string "dir", which is the
//      directory
// Modifies: directory, availablePages
Story::Story(const char * dir) : directory(dir), numPages(0), winPage(-1) {
    getPages();
    reachablePages.insert(1);
}

// getPages: reads and stores the pages
// Modifies: availablePages
void Story::getPages() {
    unsigned i = 1;
    while (1) {
        Page thisPage(directory, i);
        // check whether the page is successfully read
        if (thisPage.isExist()) {
            availablePages.push_back(thisPage);
            numPages++;
        }
        else {
            if (i == 1) {
                notAvailErr();
            }
            else {
                break;
            }
        }
        i++;
    }
    return;
}

// verifyPages: verify that the pages are valid; exit with
//      failure status if not
void Story::verifyPages() {
    // verifyArr: to mark whether the pages are referenced
    bool * verifyArr = new bool[numPages];
    // initialize the arrays
    for (unsigned i = 0; i < numPages; i++) {
        verifyArr[i] = false;
    }
    for (unsigned i = 0; i < numPages; i++) {
        for (choices_t::const_iterator it = availablePages[i].getChoices().begin();
            it != availablePages[i].getChoices().end();
            ++it) {
            // it->second.first: the number of the referenced page
            if (it->second.first > numPages) {
                // references to an invalid page; failure
                delete[] verifyArr;
                formatErr();
            }
            // mark the page as referenced
            verifyArr[it->second.first - 1] = true;
        }
    }
    for (unsigned i = 1; i < numPages; i++) {
        if (verifyArr[i] == false) {
            // fails to reference some pages; failure
            delete[] verifyArr;
            formatErr();
        }
    }
    delete[] verifyArr;
    return;
}

// displayStory: show the story and interact with the reader
// Output(s): the story page by page, to stdout
void Story::displayStory() {
    unsigned currPage = 1;
    std::string nextRankStr;
    unsigned nextPage = 0;
    while (1) {
        availablePages[currPage - 1].printPage();
        // if wins or loses, exit with success
        if (availablePages[currPage - 1].getNavi() == WIN ||
            availablePages[currPage - 1].getNavi() == LOSE) {
            exit(EXIT_SUCCESS);
        }
        // otherwise, read a number from the user
        std::cin >> nextRankStr;
        // if the input is NaN
        while (!isAllDigits(nextRankStr) || 
        // or is not available
                availablePages[currPage - 1].getChoices().find(strToUnsign(nextRankStr)) 
                                    == availablePages[currPage - 1].getChoices().end()) {
            std::cout << "That is not a valid choice, please try again" << std::endl;
            std::cin >> nextRankStr;
        }
        unsigned nextRank = strToUnsign(nextRankStr);
        nextPage = availablePages[currPage - 1].getChoices().find(nextRank)->second.first;
        currPage = nextPage;
    }
    return;
}

// printUnreachable: print the number of pages that are not
//      reachable
// Output(s): number of unreachable pages, to stdout
void Story::printUnreachable() {
    for (unsigned i = 1; i <= numPages; i++) {
        if (reachablePages.find(i) == reachablePages.end()) {
            std::cout << "Page " << i << " is not reachable" << std::endl;
        }
    }
    return;
}

// getWinWay: find a way to win
// Output(s): win method, to stdout
void Story::getPrev(bool reachableCheck) {
    // stack1: pair<pageNum, choice made to reach here>
    std::stack<unsigned> stack1;
    availablePages[0].setPrevAndChoice(1, 0);
    reachablePages.insert(1);
    stack1.push(1);
    // using a depth-first search to find the path
    while (!stack1.empty()) {
        unsigned currPage = stack1.top();
        reachablePages.insert(currPage);
        stack1.pop();
        if (availablePages[currPage - 1].getNavi() == WIN && winPage == -1) {
            winPage = (int) currPage;
        }
        choices_t::const_iterator it = availablePages[currPage - 1].getChoices().begin();
        while (it != availablePages[currPage - 1].getChoices().end()) {
            // next page num: it->second.first
            if (availablePages[it->second.first - 1].getPrev() == -1) {
                availablePages[it->second.first - 1].setPrevAndChoice(currPage, it->first);
                stack1.push(it->second.first);
            }
            ++it;
        }
    }
    if (reachableCheck) {
        printUnreachable();
    }
    else {
        printWinWay();
    }
    return;
}

// printWinWay: print the win method
// Parameter(s): the winPage
// Output(s): win method, to stdout
void Story::printWinWay() {
    if (winPage == -1) {
        std::cout << "There is no way to win" << std::endl;
        return;
    }
    std::stack<unsigned> winPath;
    unsigned currPage = (unsigned) winPage;
    while (currPage != 1) {
        winPath.push(currPage);
        currPage = availablePages[currPage - 1].getPrev();
    }
    std::cout << "Page 1 ";
    while (!winPath.empty()) {
        currPage = winPath.top();
        winPath.pop();
        std::cout << "Choice " << availablePages[currPage - 1].getChoice() << std::endl;
        std::cout << "Page " << currPage << " ";
    }
    std::cout << "WIN" << std::endl;
    return;
}