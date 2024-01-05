#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <fstream>
#include "file-utils.h"
#include <cassert>

using namespace std;

void read_file(string &dest, const char *filename)
{
    ifstream inStream(filename);
    if (inStream.is_open())
    {
        string line;
        while (getline(inStream, line))
        {
            dest += line;
            dest += "\n";
        }

        inStream.close();
    }
}

#endif