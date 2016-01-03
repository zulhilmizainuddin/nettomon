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
        string error = directoryName + " does not exist";
        perror(error.c_str());
        exit(1);
    }

    struct dirent* symlink;
    vector<string> symlinkContentList;

    while (symlink = readdir(directory)) {
        string symlinkName = "/proc/" + pid + "/fd/" + symlink->d_name;

        char symlinkContent[BUFSIZ];
        readlink(symlinkName.c_str(), symlinkContent, sizeof(symlinkContent));

        symlinkContentList.push_back(string(symlinkContent));
    }

    closedir(directory);

    return symlinkContentList;
}

vector<string> ProcFd::extractSocketsInode(vector<string> symlinkContentList) {

    vector<string> socketInodeList;

    for_each(symlinkContentList.begin(), symlinkContentList.end(), [&](string symlinkContent) {
        regex socketInodeRegex("socket:\\[([0-9]+)\\]");
        smatch match;

        if (regex_search(symlinkContent, match, socketInodeRegex)) {
            socketInodeList.push_back(match[1].str().c_str());
        }
    });

    return socketInodeList;
}
