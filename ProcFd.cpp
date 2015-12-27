#include <unistd.h>
#include <regex>
#include "ProcFd.h"

vector<const char *> ProcFd::getSocketsInode() {
    vector<const char *> symLinksContent = getSymlinksContent();
    vector<const char *> socketInodes = extractSocketInodes(symLinksContent);

    return socketInodes;
}

vector<const char *> ProcFd::getSymlinksContent() {
    char directoryName[BUFSIZ];
    sprintf(directoryName, "/proc/%s/fd", pid);

    DIR* directory = opendir(directoryName);
    if (directory == NULL) {
        exit(1);
    }

    struct dirent* symlink;
    vector<const char*> symlinksContent;

    while (symlink = readdir(directory)) {
        char symlinkName[BUFSIZ];
        sprintf(symlinkName, "/proc/%s/fd/%s", pid, symlink->d_name);

        char symlinkContent[BUFSIZ];
        readlink(symlinkName, symlinkContent, sizeof(symlinkContent));

        symlinksContent.push_back(strdup(symlinkContent));
    }

    closedir(directory);

    return symlinksContent;
}

vector<const char *> ProcFd::extractSocketInodes(vector<const char *> symlinksContent) {
    regex socketInodeRegex("socket:\\[([0-9]+)\\]");
    cmatch match;

    vector<const char*> socketInodes;
    vector<const char*>::iterator symlinksIterator = symlinksContent.begin();
    while(symlinksIterator != symlinksContent.end()) {

        if (regex_search(*symlinksIterator, match, socketInodeRegex)) {
            socketInodes.push_back(match[1].str().c_str());
            printf("%s\n", match[1].str().c_str());
        }

        symlinksIterator++;
    }

    return socketInodes;
}
