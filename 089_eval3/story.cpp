
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
Story::Story(const char * dir) : directory(dir), numPages(0) {
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

// checkReachable: check whether the pages in the story are
//      reachable and fill in the reachable set
// Parameter(s): print: whether to print the check result
// Modifies: reachablePages
// Output(s): if print, print the result to stdout
void Story::checkReachable(bool print) {
    while (1) {
        bool changed = false;
        // check the elements in reachablePages
        std::set<unsigned>::iterator it = reachablePages.begin();
        while (it != reachablePages.end()) {
            // choices: availablePages[*it - 1].getChoices()
            // corresponding page: choices[i].second.first
            choices_t::const_iterator choice_it = availablePages[*it - 1].getChoices().begin();
            while (choice_it != availablePages[*it - 1].getChoices().end()) {
                if (reachablePages.find(choice_it->second.first) == reachablePages.end()) {
                    reachablePages.insert(choice_it->second.first);
                    changed = true;
                }
                ++choice_it;
            }
            ++it;
        }
        // if any changes happen, repeat
        if (!changed) {
            break;
        }
    }
    if (print) {
        printUnreachable();
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

// getWinPages: find pages that win and add them into the set
//      winPages
// Modifies: winPages
void Story::getWinPages() {
    std::set<unsigned>::iterator it = reachablePages.begin();
    while (it != reachablePages.end()) {
        if (availablePages[*it - 1].getNavi() == WIN) {
            winPages.insert(*it);
        }
        ++it;
    }
    if (winPages.size() == 0) {
        std::cout << "There is no way to win" << std::endl;
        exit(EXIT_FAILURE);
    }
    return;
}

// getWinWay: find a way to win
// Output(s): win method, to stdout
void Story::getWinWay() {
    // stack1: pair<pageNum, choice made to reach here>
    std::stack<unsigned> stack1;
    unsigned winPage = -1;
    availablePages[0].setPrevAndChoice(1, 0);
    stack1.push(1);
    // using a depth-first search to find the path
    while (!stack1.empty()) {
        unsigned currPage = stack1.top();
        stack1.pop();
        if (availablePages[currPage - 1].getNavi() == WIN) {
            winPage = currPage;
            break;
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
    printWinWay(winPage);
    return;
}

// printWinWay: print the win method
// Parameter(s): the winPage
// Output(s): win method, to stdout
void Story::printWinWay(unsigned winPage) {
    std::stack<unsigned> winPath;
    unsigned currPage = winPage;
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