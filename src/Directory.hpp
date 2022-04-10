
#ifndef DIRECTORY
#define DIRECTORY

#ifdef __APPLE__
#include <dirent.h>
#endif

#include <string>
#include <vector>

struct Directory
{
    // returns a vector containing all of the items inside of the directory 'path'.
    // if 'path' is a file or not a valid directory then it will return an empty vector
    static std::vector<std::string> list_dir(std::string path)
    {
        std::vector<std::string> result;

        #ifdef __APPLE__
        {
            // reading directory code taken from online documentation on dirent.h
            // https://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html
            DIR *dirp = opendir(path.c_str());
            
            struct dirent *dp;
            while ((dp = readdir(dirp))) {
                std::string name(dp->d_name, dp->d_namlen);
                if (name == "." || name == ".." || name == ".DS_Store") {
                    continue;
                }
                result.push_back(name);
            }
        
            if (dirp) {
                closedir(dirp);
            }
            return result;
            
        }
        #endif
        #ifdef WIN32
        {
            // not yet implemented
        }
        #endif

        return result;
    }
};

#endif