#include <iostream>
#include <vector>
#include <sstream>
#include "Filter.h"
#include "Visitor.h"

using namespace std;

void getMessage(exception &e, const string &m) {
    cerr << m << " : " << e.what() << endl;

}

int strToInt(const string &text) {
    int number;
    istringstream iss(text);
    if (iss >> number) {
        if (!iss.good()) {
            return number;
        } else {
            throw runtime_error("Can't convert string to int");
        }
    } else {
        throw runtime_error("Can't convert string to int");
    }
}

vector<string> split_line(const string &line) {
    istringstream iss(line);
    vector<string> results(istream_iterator<string>{iss},
                           istream_iterator<string>());
    return results;
};
const string GREETINGS = "-size \n"+ "+size  set\n" +
                         "-exec  \n"+
                         "-name  set name of file \n"+
                         "-inum  set inum"+
                         "-nlinks set number of hardlinks";

void parseArg(int i, Filter &finder, const string &type, const string &value) {
    if (type == "-inum") {
        try {
            finder.setI_node(strToInt(value));
        } catch (runtime_error &e) {
            getMessage(e, "Invalid argument to -num" + value);
            throw e;
        }
    } else if (type == "-name") {
        finder.setName(value);
    } else if (type == "-size") {
        switch (value[0]) {
            case ('+'):
                finder.setSzMode(1);
                break;
            case ('-'):
                finder.setSzMode(-1);
                break;
            case ('='):
                finder.setSzMode(0);
                break;
            default:
                throw runtime_error("Invalid argument to -num " + value);
        }
        try {
            finder.setSize(strToInt(value.substr(1)));
        } catch (runtime_error &e) {
            cerr << e.what() << endl;
            throw runtime_error("Invalid argument to -size " + value);
        }
    } else if (type == "-nlinks") {
        try {
            finder.setNlinks(strToInt(value));
        } catch (runtime_error &e) {
            cerr << e.what() << endl;
            throw runtime_error("Invalid argument to -nlinks " + value);
        }
    } else if (type == "-exec") {
        finder.setExec(value);
    } else {
        throw runtime_error("Invalid token : " + type);
    }
}

void printWelcomeMessage() {
    cout << GREETINGS << endl;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cerr << "invalid arguments : use -help for information" << endl;
        return -1;
    }
    vector<std::string> args(argv + 1, argv + argc);
    if (args[0] == "-help") {
        cout << GREETINGS;
    }
    Filter filter;
    Visitor visitor(const_cast<char *>(args[0].data()));
    for (int i = 1; i < args.size(); i = i + 2) {
        if (i + 1 < args.size()) {
            try {
                parseArg(i, filter, args[i], args[i + 1]);
            } catch (exception &e) {
                getMessage(e, "command not found");
            }
        }
    }
    visitor.process(filter);
    return 0;
}