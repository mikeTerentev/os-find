
//
// Created by Михаил Терентьев on 2019-04-05.
//
#ifndef OS_FIND_EXECR_CPP
#define OS_FIND_EXECR_CPP

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <sstream>
#include <unistd.h>
using namespace std;

class Launcher{
public:
    char ** convert(vector<char *>& vector) {
        char** arr = new char* [vector.size() + 1];
        arr[vector.size()] = nullptr;
        for (size_t i = 0; i < vector.size(); ++i) {
            arr[i] = vector[i];
        }
        return arr;
    }

    void printErrorMessage(const string &message){
        cerr <<  message + " : "<< strerror(errno) << endl;
    }

    void printStatus(int status) {
        cout << "exit code : " << WEXITSTATUS(status) << endl;
    }
    void run(const vector<char *>& args){
        pid_t pid = fork();
        if(pid == 0) { //child
            if (execve(args[0], args.data(), nullptr) == -1) {
                printErrorMessage("execution error");
                exit(-1);
            }
        } else if(pid > 0){ //par
            int status;
            if (waitpid(pid, &status, 0) != -1) {
                printStatus(status);
            } else {
                printErrorMessage("Error occurred during execution");
            }
        } else {
            printErrorMessage("Folk error");
        }
    }

    void launch(const vector<const char *> &args1) {
        vector<char *> arg_real;
        arg_real.reserve(args1.size());
        for (const char *chars : args1) {
            arg_real.push_back(const_cast<char *>(chars));
        }
        arg_real.push_back(nullptr);
        run(arg_real);
    }
};

#endif //OS_FIND_EXECR_H