
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
    bool hasWin;
    bool hasLose;
    std::vector<Page> availablePages;
    std::set<unsigned> reachablePages;
    int winPage;
public:
    // Default constructor
    Story() { }

    // Constructor
    Story(const char * dir);

    // getPages: initialize the pages and put them into
    //      availablePages
    void getPages();
    
    // markReferenced: helper function of vefifyPages; mark
    //      corresponding bool value as true if referenced
    void markReferenced(unsigned i, bool * verifyArr);

    void markWinLose(unsigned i);

    // verifyPages: verify that the pages are valid; exit with
    //      failure status if not
    void verifyPages();

    // displayStory: show the story and interact with the reader
    void displayStory();

    // printUnreachable: print the number of pages that are not
    //      reachable
    void printUnreachable();

    // getPrev: set the previous page by checking choices
    //      using a depth-first search
    void getPrev(bool reachableCheck);

    // printWinWay: print the win method
    void printWinWay();
};

#endif
