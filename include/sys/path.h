/**
 * @file path.h
 * @author Zejie Du (duzejie@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>

#ifdef _MSC_VER
#include <direct.h>
#else
#include <unistd.h>
#endif

char *pwd()
{
    char *buffer;
#ifdef _MSC_VER //|| _WIN32
    buffer = _getcwd(NULL, 0);
#else //__GNUC__  _UNIX  linux
    buffer = getcwd(NULL, 0);
#endif
    if ((buffer) == NULL)
    {
        perror("getcwd error");
    }
    return buffer;
}

//----------------------------------------------------------------------------

#include <string>
#include <vector>
#include <cstring> // for strcat()

#ifdef _MSC_VER //|| _WIN32
#include <io.h>
#else              //__GNUC__  _UNIX  linux
#include <sys/stat.h>
#include <sys/types.h>
//#include <unistd.h>
#include <dirent.h>
#endif

bool listFiles(std::string dirIn, std::vector<std::string> &files, std::vector<std::string> &dirs);

#ifdef _MSC_VER //|| _WIN32

bool listFiles(std::string dirIn, std::vector<std::string> &files, std::vector<std::string> &dirs)
{
    files.clear();
    dirs.clear();
    char dir[500];
    if (dirIn=="")
    {
        return false;
    }
    
    if (dirIn == ".")
    {
        dirIn = "./";
    }

    if (dirIn[dirIn.size() - 1] != '\\')
    {
        dirIn = dirIn + "\\";
    }

    dirIn = dirIn + "*.*";
    intptr_t handle;
    _finddata_t findData;

    handle = _findfirst(dirIn.c_str(), &findData);
    if (handle == -1)
    {
        printf("Failed to find first file!\n");
        return false;
    }

    do
    {
        if (findData.attrib & _A_SUBDIR && strcmp(findData.name, ".") //== 0
            && strcmp(findData.name, "..")                            //== 0
            )                                                         // 是否是子目录并且不为"."或".."
        {
            //cout << findData.name << "\t<dir>\n";
            dirs.push_back(findData.name);
        }

        else if (strcmp(findData.name, ".")      //== 0
                 && strcmp(findData.name, "..")) //== 0
        {
            //cout << findData.name << "\t" << findData.size << endl;
            files.push_back(findData.name);
        }

    } while (_findnext(handle, &findData) == 0);

    //cout << "Done!\n";
    _findclose(handle);
    return true;
}

#else //__GNUC__  _UNIX  linux

bool listFiles(std::string path, std::vector<std::string> &files, std::vector<std::string> &dirs)
{
    DIR *dir;
    struct dirent *ptr;
    if ((dir = opendir(path.c_str())) == NULL)
    {
        perror("Open dri error...");
        return false;
    }

    while ((ptr = readdir(dir)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        else if (ptr->d_type == 8) //file
            files.push_back(ptr->d_name);
        else if (ptr->d_type == 10) //link file
            continue;
        else if (ptr->d_type == 4)
        {
            dirs.push_back(ptr->d_name); //dir
            //std::string path = dirIn;
            //getAllFiles(path+"/"+ptr->d_name,files);
            ;
        }
    }
    closedir(dir);
    return true;
}

#endif
