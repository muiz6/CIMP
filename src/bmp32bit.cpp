#include "CIMP/bmp32bit.hpp"
#include <fstream>
using namespace cp;

Bmp32Bit::Bmp32Bit(int width, int height): Bmp (width, height) {}

Bmp32Bit::Bmp32Bit(const char *path): Bmp(path) {}

Bmp32Bit::Bmp32Bit(std::string path): Bmp(path) {}

Bmp32Bit::Bmp32Bit(uint8_t* pixelData, int colorDepth, int width, int height)
    : Bmp(pixelData, colorDepth, width, height) {}

void Bmp32Bit::writeToFile(const char *path)
{
    int width = bmpInfoHeader.bmpWidth;
    int height = bmpInfoHeader.bmpHeight;

    // according to 32bit color depth
    uint32_t size = width * height * 4;
    uint8_t *flip = new uint8_t[size], *bgr = new uint8_t[size];

    // conversion to bgr + 32bit
    if (colorDepth == 24)
    {
        for (unsigned int i = 0, j = 0; j < size; i += 3, j += 4)
        {
            bgr[j] = pixelData[i + 2];
            bgr[j + 1] = pixelData[i + 1];
            bgr[j + 2] = pixelData[i];
            bgr[j + 3] = 255;
        }
    }
    else if (colorDepth == 32)
    {
        for (unsigned int i = 0; i < size; i += 4)
        {
            bgr[i] = pixelData[i + 2];
            bgr[i + 1] = pixelData[i + 1];
            bgr[i + 2] = pixelData[i];
            bgr[i + 3] = pixelData[i + 3];
        }
    }

    // vertical flip for 32bit pixels
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                flip[(i + j * width) * 4 + k] = bgr[(i + (height - 1 - j) * width) * 4 + k];
            }
        }
    }

    std::ofstream fout(path, std::ios::binary);
    bmpHeader.fileSize = 54 + size;
    bmpHeader.pixelDataOffset = 54;
    fout.write((char*) &bmpHeader, sizeof(bmpHeader));
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.colorDepth = 32;
    fout.write((char*) &bmpInfoHeader, sizeof(bmpInfoHeader));
    fout.write((char*) flip, size);

    delete[] bgr;
    delete[] flip;

    fout.close();
}