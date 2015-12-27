#include <unistd.h>
#include <regex>
#include "ProcFd.h"

vector<string> ProcFd::getSocketsInode() {
    vector<string> symLinksContent = getSymlinksContent();
    vector<string> socketInodes = extractSocketInodes(symLinksContent);

    return socketInodes;
}

vector<string> ProcFd::getSymlinksContent() {
    string directoryName = "/proc/" + pid + "/fd";

    DIR* directory = opendir(directoryName.c_str());
    if (directory == NULL) {
        exit(1);
    }

    struct dirent* symlink;
    vector<string> symlinksContent;

    while (symlink = readdir(directory)) {
        string symlinkName = "/proc/" + pid + "/fd/" + symlink->d_name;

        char symlinkContent[BUFSIZ];
        readlink(symlinkName.c_str(), symlinkContent, sizeof(symlinkContent));

        symlinksContent.push_back(strdup(symlinkContent));
    }

    closedir(directory);

    return symlinksContent;
}

vector<string> ProcFd::extractSocketInodes(vector<string> symlinksContent) {

    vector<string> socketInodes;

    for_each(symlinksContent.begin(), symlinksContent.end(), [&](string symlinkContent) {
        regex socketInodeRegex("socket:\\[([0-9]+)\\]");
        smatch match;

        if (regex_search(symlinkContent, match, socketInodeRegex)) {
            socketInodes.push_back(match[1].str().c_str());
        }
    });

    return socketInodes;
}
