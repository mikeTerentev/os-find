//
// Created by Михаил Терентьев on 2019-04-01.
//
#include <sys/types.h>
#include <dirent.h>
#include <queue>
#include <iostream>
#include "Visitor.h"
#include "Filter.h"

using namespace std;
#define f first
#define s second

void Visitor::process(Filter & filter) {
    queue<pair<DIR *, string>> queue;
    queue.push(std::make_pair(opendir(path), string(path)));
    if (queue.front().f == nullptr) {
        throw runtime_error("Invalid directory");
    }
    while (!queue.empty()) {
        auto curdir = queue.front();
        queue.pop();
        if (curdir.f == nullptr) {
            cerr << "Can't process " + curdir.s + ": access denied" << endl;
            continue;
        }
        while (auto item = readdir(curdir.f)) {
            auto filename = item->d_name;
            if (item->d_type == DT_REG) {
                string filepath = curdir.s + '/' + filename;
                auto fileStat = getStat(filepath);
                filter.filter_all(filepath,filename, fileStat);
            } else if (item->d_type == DT_DIR) {
                if (isBackLink(filename)) {
                    continue;
                }
                string nxt = curdir.s + "/" + filename;
                queue.emplace(opendir(nxt.c_str()), nxt);
            }

        }
    }
}

bool Visitor::isBackLink(char const *filename) {
    return (strcmp(filename, ".") == 0) || (strcmp(filename, "..") == 0);
}

struct stat Visitor::getStat(const std::string &file_name) {
    struct stat file_stats{};
    stat(file_name.c_str(), &file_stats);
    return file_stats;
}
