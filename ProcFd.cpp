#include <unistd.h>
#include <regex>
#include <dirent.h>
#include "ProcFd.h"

vector<string> ProcFd::getSocketInodeList() {
    auto symLinksContent = getSymlinksContent();
    auto socketInodeList = extractSocketsInode(symLinksContent);

    return socketInodeList;
}

vector<string> ProcFd::getSymlinksContent() {
    string directoryName = "/proc/" + pid + "/fd";

    DIR* directory = opendir(directoryName.c_str());
    if (directory == NULL) {
        perror(string(directoryName + " does not exist").c_str());
        exit(1);
    }

    vector<string> symlinkContentList;

    while (struct dirent* symlink = readdir(directory)) {
        string symlinkName = "/proc/" + pid + "/fd/" + symlink->d_name;

        char symlinkContent[BUFSIZ];
        if  (readlink(symlinkName.c_str(), symlinkContent, sizeof(symlinkContent)) != -1) {
            symlinkContentList.push_back(string(symlinkContent));
        }
    }

    closedir(directory);

    return symlinkContentList;
}

vector<string> ProcFd::extractSocketsInode(vector<string> symlinkContentList) {
    vector<string> socketInodeList;

    for (auto symlinkContent: symlinkContentList) {
        regex socketInodeRegex("socket:\\[([0-9]+)\\]");
        smatch match;

        if (regex_search(symlinkContent, match, socketInodeRegex)) {
            socketInodeList.push_back(match[1].str().c_str());
        }
    }

    return socketInodeList;
}
