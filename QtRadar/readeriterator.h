#ifndef READERITERATOR_H
#define READERITERATOR_H

#include "planeinfo.h"
#include "string"
#include <iostream>
#include <fstream>



class ReaderIterator
{
public:
    ReaderIterator(const std::string path = "data.txt");
    ~ReaderIterator();
    void MoveNext();
    bool HasValue();
    PlaneInfo* GetCurrent();
private:
    PlaneInfo* currentPlaneInfo;
    std::ifstream* infile;
};

#endif // READERITERATOR_H
