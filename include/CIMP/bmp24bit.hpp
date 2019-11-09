#ifndef BMP24BIT_H
#define BMP24BIT_H

#include "CIMP/bmp.hpp"
#include <cstdint>

namespace cp
{
    class Bmp24Bit: public Bmp
    {
    public:
        Bmp24Bit(uint8_t* pixelData, int colorDepth, int width, int height);

        /// @brief write 24bit bmp
        /// @param path: path to store file
        void writeToFile(const char *path) override;

        /// @brief write 24bit bmp
        /// @param path: path to store file
        void writeToFile(std::string path) override;
    };
}

#endif // BMP24BIT_H