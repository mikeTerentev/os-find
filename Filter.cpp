#include <dirent.h>
#include "Filter.h"
#include <queue>
#include "Launcher.h"
using namespace std;

bool Filter::filter_size(struct stat& file_stat) {
    if (this->szMode == -100) {
        return true;
    } else if (this->szMode == 0) {
        return  this->size == file_stat.st_size;
    } else if (this->szMode == 1) {
        //cout<<file_stat.st_size << "||" << this->size << endl;
        return  this->size < file_stat.st_size;
    } else if (this->szMode == -1){
        return  this->size > file_stat.st_size;
    }
    throw runtime_error("invalid size filter mode : logic error");
}

bool Filter::filter_all(const string &filepath,const string &filename, struct stat& file_stat) {
    //cout<<filter_inode(file_stat) << " "<< filter_name(filename,file_stat) << " "<< filter_size(file_stat) << " "<< filter_nlinks(file_stat)<<endl;
    bool isMatched = filter_nlinks(file_stat) && filter_size(file_stat) && filter_name(filename, file_stat) && filter_inode(file_stat);
    if (!filename.empty() && isMatched) {
        vector<const char *> arguments;
        arguments.push_back(this->exec.c_str());
        arguments.push_back(filename.c_str());
        execLauncher.run(arguments);
        printInfo(file_stat,filepath);
    }
    return isMatched;
}
bool Filter::filter_nlinks(struct stat& file_stat) {
    return nlinks == -1 ? true : nlinks == file_stat.st_nlink;
}

bool Filter::filter_name(const std::string &name,struct stat& file_stat) {
    return this->exp_name.empty() ? true : (this->exp_name == name);
}

bool Filter::filter_inode(struct stat& file_stat) {
    return this->i_node == -1 ? true : this->i_node == file_stat.st_ino;
}

void Filter::printInfo(struct stat& file_stat, const string& filepath) {
    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << filepath<<endl;// << " | "
         /*<< "size : " << file_stat.st_size << " | "
         << "inode : " << file_stat.st_ino << " | "
         << "nLink : " << file_stat.st_nlink << endl;*/
    cout <<"-------------------------------------------------------------------------------------" << endl;
}