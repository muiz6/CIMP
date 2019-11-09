#ifndef BMP32BIT_H
#define BMP32BIT_H

#include "CIMP/bmp.hpp"

namespace cp
{
    class Bmp32Bit: public Bmp
    {
    public:
        Bmp32Bit(uint8_t* pixelData, int colorDepth, int width, int height);

        /// @brief write 32bit bmp
        /// @param path: path to store file
        void writeToFile(const char *path) override;

        /// @brief write 32bit bmp
        /// @param path: path to store file
        void writeToFile(std::string path) override;
    };
}

#endif // BMP32BIT_H