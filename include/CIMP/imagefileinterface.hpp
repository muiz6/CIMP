#ifndef IMAGEFILEINTERFACE_H
#define IMAGEFILEINTERFACE_H

#include <string>

namespace cp
{
    class ImageFileInterface
    {
    public:
        virtual ~ImageFileInterface();

        virtual void writeToFile(const char* path) = 0;

        void writeToFile(std::string path);
    };
}

#endif // IMAGEFILEINTERFACE_H