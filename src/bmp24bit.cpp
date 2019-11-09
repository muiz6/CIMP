#include "CIMP/bmp24bit.hpp"
#include <fstream>
using namespace cp;

Bmp24Bit::Bmp24Bit(int width, int height): Bmp (width, height) {}

Bmp24Bit::Bmp24Bit(const char *path): Bmp(path) {}

Bmp24Bit::Bmp24Bit(std::string path): Bmp(path) {}

Bmp24Bit::Bmp24Bit(uint8_t* pixelData, int colorDepth, int width, int height)
    : Bmp(pixelData, colorDepth, width, height) {}

void Bmp24Bit::writeToFile(const char * path)
{
    int width = bmpInfoHeader.bmpWidth;
    int height = bmpInfoHeader.bmpHeight;

    // according to 24bit color depth
    uint32_t size = width * height * 3;
    uint8_t *flip = new uint8_t[size], *bgr = new uint8_t[size];

    // conversion to bgr + 24bit
    if (colorDepth == 24)
    {
        for (unsigned int i = 0; i < size; i += 3)
        {
            bgr[i] = pixelData[i + 2];
            bgr[i + 1] = pixelData[i + 1];
            bgr[i + 2] = pixelData[i];
        }
    }
    else if (colorDepth == 32)
    {
        for (unsigned int i = 0, j = 0; i < size; i += 3, j += 4)
        {
            bgr[i] = pixelData[j + 2];
            bgr[i + 1] = pixelData[j + 1];
            bgr[i + 2] = pixelData[j];
            // pixelData[j + 3] is ignored
        }
    }

    // vertical flip for 24bit pixels
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                flip[(i + j * width) * 3 + k] = bgr[(i + (height - 1 - j) * width) * 3 + k];
            }
        }
    }

    std::ofstream fout(path, std::ios::binary);
    bmpHeader.fileSize = 54 + size;
    bmpHeader.pixelDataOffset = 54;
    fout.write((char*) &bmpHeader, sizeof(bmpHeader));
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.colorDepth = 24;
    fout.write((char*) &bmpInfoHeader, sizeof(bmpInfoHeader));
    fout.write((char*) flip, size);

    delete[] flip;
    delete[] bgr;

    fout.close();
}