
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

std::ostream & operator << (std::ostream & s, std::vector<std::string> v) {
    std::vector<std::string>::iterator it = v.begin();
    while (it != v.end()) {
        s << *it << std::endl;
        ++it;
    }
    return s;
}

int main(int argc, char ** argv) {
    if (argc == 1) {
        std::vector<std::string> v;
        std::string str;
        while (!std::cin.eof()) {
            std::getline(std::cin, str);
            v.push_back(str);
        }
        std::sort(v.begin(), v.end());
        std::cout << v;
        v.clear();
    }
    else {
        for (size_t i = 1; i < argc; i++) {
            std::ifstream myFile;
            std::vector<std::string> v;
            myFile.open(argv[i], std::fstream::in);
            if (myFile.fail()) {
                std:: cerr << "Erro opening file" << std::endl;
                return EXIT_FAILURE;
            }
            std::string str;
            while (!myFile.eof()) {
                std::getline(myFile, str);
                v.push_back(str);
            }
            std::sort(v.begin(), v.end());
            std::cout << v;
            v.clear();
            myFile.close();
        }
        
    }
    return EXIT_SUCCESS;
}
