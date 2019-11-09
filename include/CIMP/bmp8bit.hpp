#ifndef BMP8BIT_H
#define BMP8BIT_H

#include "CIMP/bmp.hpp"

namespace cp
{
    class Bmp8Bit: public Bmp
    {
    public:
        Bmp8Bit(uint8_t* pixelData, int colorDepth, int width, int height);

        /// @brief write 8bit bmp
        /// @param path: path to store file
        void writeToFile(const char *path) override;

        /// @brief write 8bit bmp
        /// @param path: path to store file
        void writeToFile(std::string path) override;
    };
}

#endif // BMP8BIT_H