
#ifndef _STORY_H_
#define _STORY_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cstdio>
#include <fstream>
#include <cstdlib>

#include "page.h"
#include "cyoa.h"

class Story {
private:
    std::string directory;
    unsigned numPages;
    std::vector<Page> availablePages;
    std::set<unsigned> reachablePages;
    int winPage;
public:
    // Default constructor
    Story() { }

    // Constructor
    Story(const char * dir);

    // Copy constructor
    Story(const Story & rhs);

    // getPages: initialize the pages and put them into
    //      availablePages
    void getPages();

    // verifyPages: verify that the pages are valid; exit with
    //      failure status if not
    void verifyPages();

    // displayStory: show the story and interact with the reader
    void displayStory();

    // printUnreachable: print the number of pages that are not
    //      reachable
    void printUnreachable();

    // getWinWay: find a way to win
    void getPrev(bool reachableCheck);

    // printWinWay: print the win method
    void printWinWay();
};

#endif
