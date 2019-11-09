#include "CIMP/bmp8bit.hpp"
#include <fstream>
using namespace cp;

Bmp8Bit::Bmp8Bit(int width, int height): Bmp(width, height) {}

Bmp8Bit::Bmp8Bit(const char *path): Bmp(path) {}

Bmp8Bit::Bmp8Bit(std::string path): Bmp(path) {}

Bmp8Bit::Bmp8Bit(uint8_t* pixelData, int colorDepth, int width, int height)
    : Bmp(pixelData, colorDepth, width, height) {}

void Bmp8Bit::writeToFile(const char *path)
{
    // initializing standard 216 web safe color pallete
    uint8_t *stdColTable = new uint8_t[864];
    int col[] = {0, 51, 102, 153, 204, 255};
    int count = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            for (int k = 0; k < 6; k++)
            {
                stdColTable[4 * count] = col[i];
                stdColTable[4 * count + 1] = col[j];
                stdColTable[4 * count + 2] = col[k];
                stdColTable[4 * count + 3] = 0;
                count++;
            }
        }
    }
    // palette is uninitialized after index 863

    uint8_t* bgr = new uint8_t[width * height], *flip = new uint8_t[width * height];

    // for 24bit pixels
    int step = 3;
    // for 32bit pixels
    if (colorDepth == 32)
    {
        step = 4;
    }

    for (unsigned int i = 0; i < size(); i += step)
    {
        int pixel[3];
        for (int j = 0; j < 3; j++)
        {
            if (pixelData[i + j] < 26)
            {
                pixel[j] = 0;
            }
            else if (pixelData[i + j] < 77)
            {
                // 51/51 = 1
                pixel[j] = 1;
            }
            else if (pixelData[i + j] < 128)
            {
                pixel[j] = 2;
            }
            else if (pixelData[i + j] < 179)
            {
                pixel[j] = 3;
            }
            else if (pixelData[i + j] < 230)
            {
                pixel[j] = 4;
            }
            else
            {
                pixel[j] = 5;
            }
        }

        int index = i / step;
        // general formula to calculate color index
        bgr[index] = 36 * pixel[2] + 6 * pixel[1] + pixel[0];
    }

    // vertical flip
     for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            for (int k = 0; k < 1; ++k)
            {
                flip[(i + j * width) * 1 + k] = bgr[(i + (height - 1 - j) * width) * 1 + k];
            }
        }
    }

    std::ofstream fout(path, std::ios::binary);
    bmpHeader.fileSize = 54 + 1024 + width * height;
    bmpHeader.pixelDataOffset = 1078;
    fout.write((char*) &bmpHeader, sizeof(bmpHeader));
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.colorDepth = 8;
    fout.write((char*) &bmpInfoHeader, sizeof(bmpInfoHeader));
    fout.write((char*) stdColTable, 1024);
    fout.write((char*) flip, width * height);

    delete[] stdColTable;
    delete[] bgr;
    delete[] flip;
    fout.close();
}