#include "readeriterator.h"
#include <string>
#include <sstream>
#include <vector>

ReaderIterator::ReaderIterator(const std::string filePath)
{
    infile = new std::ifstream(filePath);
    std::cout << "File is open at start: " << infile->is_open() << std::endl;
    //if(!infile->good()) throw "Can`t open file.";
    MoveNext();
}

ReaderIterator::~ReaderIterator()
{
    if(infile != nullptr)
    {
        std::cout << "Closing infile." << std::endl;
        infile->close();
        delete infile;
    }
}

void ReaderIterator::MoveNext()
{
    //std::cout << "File is open: " << infile->is_open() << std::endl;
    if (infile->is_open())
    {
        //std::cout << "Line?" << std::endl;
        std::string line;
        if (getline(*infile, line))
        {
            //std::cout << line << std::endl;
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> words;
            while (std::getline(ss, item, ' ')) {
              words.push_back(item);
            }

            if(words.size() != 5)
            {
                currentPlaneInfo = nullptr;
                throw "words count != 5";
            }

            currentPlaneInfo = new PlaneInfo();
            currentPlaneInfo->timeMs = std::stoll(words[0]);
            currentPlaneInfo->radius = std::stod(words[1]);
            currentPlaneInfo->height = std::stod(words[2]);
            currentPlaneInfo->velocity = std::stod(words[3]);
            currentPlaneInfo->index = std::stoi(words[4]);
//            std::cout << "Plane info: "
//                      << currentPlaneInfo->timeMs << " "
//                      << currentPlaneInfo->radius << " "
//                      << currentPlaneInfo->height << " "
//                      << currentPlaneInfo->velocity << " "
//                      << currentPlaneInfo->index
//                      << std::endl;
        }
        else {
            std::cout << "Can't get line." << std::endl;
            currentPlaneInfo = nullptr;
        }
    }
    else {
        currentPlaneInfo = nullptr;
    }
}

bool ReaderIterator::HasValue()
{
    return currentPlaneInfo!=nullptr;
}

PlaneInfo *ReaderIterator::GetCurrent()
{
    return currentPlaneInfo;
}

