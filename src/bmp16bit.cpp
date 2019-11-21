#include "CIMP/bmp16bit.hpp"
#include <fstream>
using namespace cp;

Bmp16Bit::Bmp16Bit(int width, int height)
    : Bmp(width, height) {}

Bmp16Bit::Bmp16Bit(const char *path)
    : Bmp(path) {}

Bmp16Bit::Bmp16Bit(uint8_t* pixelData, int colorDepth, int width, int height)
    : Bmp(pixelData, colorDepth, width, height) {}

Bmp16Bit::Bmp16Bit(const Img &img)
    : Bmp(img) {}

void Bmp16Bit::writeToFile(const char* path)
{
    // according to 24bit color depth
    uint32_t size = width * height * 3;
    uint8_t *flip = new uint8_t[size], *bgr = new uint8_t[size];

    // conversion to bgr + 24bit
    int step = 0;
    if (colorDepth == 24)
    {
        step = 3;
    }
    else if (colorDepth == 32)
    {
        step = 4;
    }
    for (unsigned int i = 0, j = 0; i < size; i += 3, j += step)
    {
        bgr[i] = pixelData[j + 2];
        bgr[i + 1] = pixelData[j + 1];
        bgr[i + 2] = pixelData[j];
        // pixelData[j + 3] is ignored
    }

    // vertical flip for 24bit pixels
    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                flip[(i + j * width) * 3 + k] = bgr[(i + (height - 1 - j) * width) * 3 + k];
            }
        }
    }

    size = width * height;

    // pixel of 16bit RGB555
    struct Pixel
    {
        unsigned int b : 5;
        unsigned int g : 5;
        unsigned int r : 5;
        unsigned int x : 1;
    };
    Pixel *pixels16Bit = new Pixel[size];

    for(unsigned int i = 0, j = 0; i < size; i++, j += 3)
    {
        unsigned int b = ((float) flip[j] / 255.0f) * 31;
        unsigned int g = ((float) flip[j + 1] / 255.0f) * 31;
        unsigned int r = ((float) flip[j + 2] / 255.0f) * 31;

        pixels16Bit[i] = {b, g, r, 0};
    }

    std::ofstream fout(path, std::ios::binary);
    bmpHeader.fileSize = 54 + size * 2;
    bmpHeader.pixelDataOffset = 54;
    fout.write((char*) &bmpHeader, sizeof(bmpHeader));
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.colorDepth = 16;
    fout.write((char*) &bmpInfoHeader, sizeof(bmpInfoHeader));
    fout.write((char*) pixels16Bit, size * 2);

    delete[] flip;
    delete[] bgr;
    delete[] pixels16Bit;

    fout.close();
}