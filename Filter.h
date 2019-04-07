//
// Created by Михаил Терентьев on 2019-04-01.
//

#ifndef OS_FIND_FINDER_H
#define OS_FIND_FINDER_H

#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include "Launcher.h"
using namespace std;

class Filter {
public:

    void setI_node(int i_node) {
        this->i_node = i_node;
    }

    void setName(const std::string &name) {
        this->exp_name = name;
    }

    void setSize(int size) {
        this->size = size;
    }

    void setSzMode(int sizeGroup) {
        this->szMode = sizeGroup;
    }

    void setNlinks(int nlinks) {
        this->nlinks = nlinks;
    }

    void setExec(const string &exec) {
        this->exec = exec;
    }

    bool filter_all(const string &filepath,const string &filename, struct stat& file_stat);

    bool filter_nlinks(struct stat& file_stat);

    bool filter_size(struct stat& file_stat);

    bool filter_name(const std::string &name,struct stat& file_stat);

    bool filter_inode(struct stat& file_stat);

private:
    Launcher execLauncher;
    int i_node = -1;
    string exp_name = "";
    int size = -1;
    int szMode = -100;
    int nlinks = -1;
    string exec = "";

    void printInfo(struct stat& file_stat, const string& filepath);
};

#endif //OS_FIND_FINDER_H
