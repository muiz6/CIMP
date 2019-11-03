#ifndef BMP_H
#define BMP_H

#include "CIMP/img.hpp"
#include <cstdint>
#include <string>

// to avoid extra struct padding in file
#pragma pack(push, 1)

namespace cp
{
    /// @brief class to read/write bitmap images
    class Bmp: public cp::Img
    {
    private:

        // Bmp file header data - 14 bytes
        struct BmpHeader
        {
            // byte no 0 & 1
            char fileType[2];

            // size of bmp file
            // byte 2 to 5
            uint32_t fileSize;

            // byte 6 to 9
            uint32_t reserved;

            // byte 10 to 13
            uint32_t pixelDataOffset;
        } bmpHeader;

        // Bmp information header - 40 bytes
        struct BmpInfoHeader
        {
            // byte 14 to 17, hex value: 28
            uint32_t headerSize;
            int32_t bmpWidth;
            int32_t bmpHeight;

            int16_t colorPlaneCount;

            // in bits, value = 24 for color bitmaps
            int16_t colorDepth;

            // value = 0 for BI_RGB compression i.e. no compression
            uint32_t compressionMethod;

            // in bytes
            uint32_t imageSize;

            // in pixel per metre
            uint32_t horizontalResolution;

            // in pixel per metre
            uint32_t verticalResolution;

            // no of color table entries
            uint32_t colorCount;
            uint32_t impColorCount;
        } bmpInfoHeader;

        uint8_t* colorTable = NULL;

    public:

        /// @brief Create blank Bmp from scratch
        /// @param width: width of bmp
        /// @param height: height of bmp
        Bmp(int width, int height);

        /// @brief Create Bmp from existing bmp image file
        /// @param path: path of bmp image, do write extension as well
        Bmp(const char* path);

        /// @brief Create Bmp from existing bmp image file
        /// @param path: path of bmp image, do write extension as well
        Bmp(std::string path);

        /// @brief Create Bmp from array of pixel data
        /// @param pixelData: pointer to array of pixel data in RGB sequence,
        /// must be thrice the size of product of width and height for 24bit Bmp
        /// i.e arr[width * height * 3]
        /// @param colorDepth: colorDepth of Image in bits, 24bit for RGB
        /// and 32bit for RGBA, all other values will be ignored
        /// @param width: width of bitmap in pixels
        /// @param height: height of bitmap in pixels
        Bmp(uint8_t* pixelData, int colorDepth, int width, int height);

        /// @brief create Bmp from cp::Img object
        /// @param img: object of cp::Img class
        Bmp(cp::Img &img);

        /// destructor
        ~Bmp();

        /// @brief set bit depth - default is 96 dpi
        /// @param dpi: desired bit depth of bmp in dots per inch
        void setDotDensity(int dpi);

        void write8BitBmp(const char* path);

        /// @brief write 24bit bmp
        /// @param path: path to store file
        void write24BitBmp(const char* path);

        /// @brief write 24bit bmp
        /// @param path: path to store file
        void write24BitBmp(std::string path);

        /// @brief write 32bit bmp
        /// @param path: path to store file
        void write32BitBmp(const char* path);

        /// @brief write 32bit bmp
        /// @param path: path to store file
        void write32BitBmp(std::string path);
    };
}

// sets struct padding back to default
#pragma pack(pop)

#endif // BMP_H