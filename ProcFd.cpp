#include <unistd.h>
#include <regex>
#include <dirent.h>
#include "ProcFd.h"

vector<string> ProcFd::getSocketInodeList() {
    auto socketInodeList = retrieveSocketsInode();

    return socketInodeList;
}

vector<string> ProcFd::retrieveSocketsInode() {
    string directoryName = "/proc/" + pid + "/fd";

    DIR* directory = opendir(directoryName.c_str());
    if (directory == NULL) {
        perror(string(directoryName + " does not exist").c_str());
        exit(1);
    }

    vector<string> socketInodeList;
    socketInodeList.reserve(100);

    while (struct dirent* symlink = readdir(directory)) {
        string symlinkName = "/proc/" + pid + "/fd/" + symlink->d_name;

        char symlinkContent[BUFSIZ];
        if (readlink(symlinkName.c_str(), symlinkContent, sizeof(symlinkContent)) != -1) {
            string socketInode = extractSocketInode(symlinkContent);
            if (socketInode.size() != 0) {
                socketInodeList.push_back(socketInode);
            }
        }
    }

    closedir(directory);

    return socketInodeList;
}

string ProcFd::extractSocketInode(string symlinkContent) {
    regex socketInodeRegex("socket:\\[([0-9]+)\\]");
    smatch match;

    string socketInode;
    if (regex_search(symlinkContent, match, socketInodeRegex)) {
        socketInode = match[1].str().c_str();
    }

    return socketInode;
}
