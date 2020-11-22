
#ifndef _PAGE_H_
#define _PAGE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <map>

// an enum to define the type of navigation
enum navi_t { WIN, LOSE, CHOICES };

// choices: in each element: rank, pair<nextPageNum, choiceContent>
//      rank: starts from 1
typedef std::map<unsigned, std::pair<unsigned, std::string> > choices_t;

class Page {
private:
    unsigned num;
    std::string text;
    bool exist;
    navi_t navi;
    choices_t choices;
    int prev;
    int choiceToHere;
public:
    // Default constructor
    Page() : num(0), text(), exist(false), navi(CHOICES), choices(), prev(-1), choiceToHere(-1) { }

    // Constructor
    Page(std::string & filename);

    // Constructor
    Page(std::string & directory, unsigned pageNum);

    // Copy constructor
    Page(const Page & rhs) : num(rhs.num), text(rhs.text), exist(rhs.exist),
                            navi(rhs.navi), choices(rhs.choices), prev(rhs.prev),
                            choiceToHere(-1) { }

    // Assignment operator
    Page & operator= (const Page & rhs);

    // Destructor
    ~Page() {}

    // initPage: initialization of pageFile and choices
    void initPage(std::string & filename);

    void getText(std::ifstream & pageFile);

    // getNavi: set the navi according to the content of files
    void getNaviChoices(std::ifstream & pageFile);

    // addSingleChoice: read a line, add the information to 
    //      choices
    void addSingleChoice(std::string & line, unsigned rank);

    // isExist: help to check whether the file exists
    bool isExist() const;

    // printText: print the text of the story
    void printText();

    // printWinLose: print the result of the story; should only
    //      be called when navi is either WIN or LOSE
    void printWinLose();

    // printWinLose: print the result of the story; should only
    //      be called when navi is CHOICES
    void printChoices();

    // printPage: print the content of a page
    void printPage();

    // getChoices: get the choices
    const choices_t & getChoices() const;

    // getNavi: get the navigation type
    navi_t getNavi() const;

    // setPrev: set the prev page
    void setPrevAndChoice(int thisPrev, int thisChoice);

    // getPrev: get the prev page num
    int getPrev() const;

    // getChoice: get the prev page num
    int getChoice() const;
};

#endif
