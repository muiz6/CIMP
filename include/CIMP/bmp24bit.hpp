#ifndef BMP24BIT_H
#define BMP24BIT_H

#include "CIMP/bmp.hpp"
#include "CIMP/imagefileinterface.hpp"
#include <cstdint>

namespace cp
{
    /// @brief class to read/write bmp files
    class Bmp24Bit: public Bmp, public ImageFileInterface
    {
    public:

        /// @brief Create blank Bmp from scratch
        /// @param width: width of bmp
        /// @param height: height of bmp
        Bmp24Bit(int width, int height);

        /// @brief Create Bmp from existing bmp image file
        /// @param path: path of bmp image, do write extension as well
        Bmp24Bit(const char* path);

        /// @brief Create Bmp from array of pixel data
        /// @param pixelData: pointer to array of pixel data in RGB sequence,
        /// must be thrice the size of product of width and height for 24bit Bmp
        /// i.e arr[width * height * 3]
        /// @param colorDepth: colorDepth of Image in bits, 24bit for RGB
        /// and 32bit for RGBA, all other values will be ignored
        /// @param width: width of bitmap in pixels
        /// @param height: height of bitmap in pixels
        Bmp24Bit(uint8_t* pixelData, int colorDepth, int width, int height);

        Bmp24Bit(Img &img);

        /// @brief write 24bit bmp
        /// @param path: path to store file
        void writeToFile(const char *path) override;
    };
}

#endif // BMP24BIT_H