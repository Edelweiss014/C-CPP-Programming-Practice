SOURCES=$(wildcard *.cpp)
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98


all: $(PROGS)
cyoa-step1: cyoa-step1.cpp cyoa.cpp page.cpp
	g++ $(CPPFLAGS) -o cyoa-step1 cyoa-step1.cpp cyoa.cpp page.cpp
cyoa-step2: cyoa-step2.cpp cyoa.cpp page.cpp story.cpp
	g++ $(CPPFLAGS) -o cyoa-step2 cyoa-step2.cpp cyoa.cpp page.cpp story.cpp
cyoa-step3: cyoa-step3.cpp cyoa.cpp page.cpp story.cpp
	g++ $(CPPFLAGS) -o cyoa-step3 cyoa-step3.cpp cyoa.cpp page.cpp story.cpp
cyoa-step4: cyoa-step3.cpp cyoa.cpp page.cpp story.cpp
	g++ $(CPPFLAGS) -o cyoa-step4 cyoa-step4.cpp cyoa.cpp page.cpp story.cpp

clean:
	rm cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4 *~ *.o


