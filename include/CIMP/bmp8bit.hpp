#ifndef BMP8BIT_H
#define BMP8BIT_H

#include "CIMP/bmp.hpp"
#include "CIMP/imagefileinterface.hpp"

namespace cp
{
    class Bmp8Bit: public Bmp, public ImageFileInterface
    {
    public:

        /// @brief Create blank Bmp from scratch
        /// @param width: width of bmp
        /// @param height: height of bmp
        Bmp8Bit(int width, int height);

        /// @brief Create Bmp from existing bmp image file
        /// @param path: path of bmp image, do write extension as well
        Bmp8Bit(const char* path);

        /// @brief Create Bmp from array of pixel data
        /// @param pixelData: pointer to array of pixel data in RGB sequence,
        /// must be thrice the size of product of width and height for 24bit Bmp
        /// i.e arr[width * height * 3]
        /// @param colorDepth: colorDepth of Image in bits, 24bit for RGB
        /// and 32bit for RGBA, all other values will be ignored
        /// @param width: width of bitmap in pixels
        /// @param height: height of bitmap in pixels
        Bmp8Bit(uint8_t* pixelData, int colorDepth, int width, int height);

        /// @brief initialize by cp::Img object
        /// @param img: object of cp::Img class
        Bmp8Bit(const Img &img);

        /// @brief write 8bit bmp
        /// @param path: path to store file
        void writeToFile(const char *path) override;
    };
}

#endif // BMP8BIT_H