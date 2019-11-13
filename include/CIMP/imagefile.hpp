#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include "CIMP/img.hpp"
#include <string>

namespace cp
{
    enum ImageWriteType
    {
        BITMAP_24_BIT,
        BITMAP_32_BIT,
        BITMAP_8_BIT,
        PNG_24_BIT
    };

    enum ImageReadType
    {
        ANY_IMAGE,
        BITMAP_IMAGE,
        PNG_IMAGE
    };

    // abstract class (interface) for writing image files
    class ImageFile: public Img
    {
    private:
        bool flagIsOpen;

    public:

        /// @brief initialize cp::Img with array of pixel data
        /// @param pixelDataInput: pointer to dynamic array of pixels
        /// @param colorDepth: color depth of image, allowed values are 24
        /// and 32 for 24bit and 32bit respectively. All other values will
        /// be ignored
        /// @param width: width of image in pixels
        /// @param height: height of image in pixels
        ImageFile(uint8_t* pixelDataInput, int colorDepth, int width, int height);

        /// @brief initialize with a cp::Img object
        /// @param img: cp::Img object
        ImageFile(const Img &img);

        ImageFile(const char *path, ImageReadType);

        ImageFile(std::string path, ImageReadType);

        virtual ~ImageFile();

        /// @brief check if cp::ImageFile is initialized successfully
        bool isOpen();

        /// @brief write image to file
        /// @param path: path to write image to
        void writeToFile(const char* path, ImageWriteType);

        /// @brief write image to file
        /// @param path: path to write image to
        void writeToFile(std::string path, ImageWriteType);
    };
}


#endif // IMAGEFILE_H