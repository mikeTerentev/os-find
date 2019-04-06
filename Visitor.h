//
// Created by Михаил Терентьев on 2019-04-01.
//

#ifndef OS_FIND_VISITER_H
#define OS_FIND_VISITER_H

using namespace std;

#include <string>
#include "Filter.h"

class Visitor {
public:
    explicit Visitor(char* path){
        this->path = path;
    }
    void process(Filter& filter);
private:
    char* path;
    struct stat getStat(const std::string &file_name);
    bool isBackLink(char const *filename);
};


#endif //OS_FIND_VISITER_H
