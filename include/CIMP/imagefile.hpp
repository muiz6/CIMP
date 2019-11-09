#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <string>

namespace cp
{
    // abstract class (interface) for writing image files
    class ImageFile
    {
    public:
        virtual ~ImageFile();

        /// @brief write image to file
        /// @param path: path to write image to
        virtual void writeToFile(const char* path) = 0;

        /// @brief write image to file
        /// @param path: path to write image to
        void writeToFile(std::string path);
    };
}


#endif // IMAGEFILE_H