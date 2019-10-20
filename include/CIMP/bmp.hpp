#ifndef BMP_H
#define BMP_H

// #include <string>
#include <cstdint>
#include <vector>

// to avoid extra struct padding in file
#pragma pack(push, 1)

namespace cp
{
    class Bmp
    {
    private:

        // Bmp file header data - 14 bytes
        struct BmpHeader
        {
            // byt no 0 & 1
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

            uint32_t colorCount;
            uint32_t impColorCount;
        } bmpInfoHeader;

        uint8_t* pixelData;

        uint8_t* colorTable = NULL;

    public:

        /// @brief Create Bmp from scratch
        /// @param width: width of bmp
        /// @param height: height of bmp
        Bmp(int width, int height);

        /// @brief Create Bmp from existing bmp image file
        /// @param path: path of bmp image, do write extension as well
        Bmp(char* path);

        /// @brief Create Bmp from array of pixel data
        /// @param pixelData: pointer to array of pixel data in RGB sequence,
        /// must be thrice the size of product of width and height for 24bit Bmp
        /// i.e arr[width * height * 3]
        /// @param size: size of the array in bytes
        Bmp(uint8_t* pixelData, int size, int width, int height);

        /// @brief Create Bmp from vector of pixel data
        /// @param pixelDataInput: vector of pixel data in RGB sequence,
        /// must be thrice the size of product of width and height for 24bit Bmp
        /// i.e vec.size() = width * height * 3
        Bmp(std::vector<unsigned char> &pixelDataInput, int width, int height);

        /// destructor
        ~Bmp();

        /// @brief set bit depth - default is 96 dpi
        /// @param dpi: desired bit depth of bmp in dots per inch
        void setDotDensity(int dpi);

        /// @brief writes the bmp to file
        /// @param path: path of bmp image, do write .bmp extension as well
        void writeToFile(char* path);

        /// @brief set bit depth of bmp - default is 24 bit
        /// @param b: bit depth of the image allowed values are 8, 24 and
        /// 32 for 8bit, 24bit and 32bit bitmap respectively
        /// all other values will be ignored
        void setBitDepth(int b);

        /// @brief must be called when ur done with the Bmp to free memory
        void close();

        /// @return height of bmp image in pixels
        uint32_t getHeight();

        /// @return width of bmp image in pixels
        uint32_t getWidth();

        /// @return pointer to array of pixel data in RGB/RGBA sequence
        uint8_t* getPixelDataInt();

        /// @return pointer to array of pixel data in RGB/RGBA sequence
        unsigned char* getPixelDataChar();

        /// @return size of pixel data in bytes
        int size();

        /// @brief set 256 entry color tablefor 8bit bmp
        /// @param input: pointer to array of color table data in 32bit
        /// RGBA sequence , size of input must be 1024 bytes
        void setColorTable(uint8_t* input);
    };
}

// sets struct padding back to default
#pragma pack(pop)

#endif // BMP_H