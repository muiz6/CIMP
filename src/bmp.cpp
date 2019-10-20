#include "CIMP/bmp.hpp"
#include <fstream>
#include <iostream>

using namespace cp;

Bmp::Bmp(int width, int height)
{
    // initializing bmpHeader
    bmpHeader.fileType[0] = 'B';
    bmpHeader.fileType[1] = 'M';
    bmpHeader.fileSize = (width * height) * 3 + 54;
    bmpHeader.reserved = 0;
    bmpHeader.pixelDataOffset = 54;

    // initializing bmpInfoHeader
    bmpInfoHeader.headerSize = 40;
    bmpInfoHeader.bmpWidth = width;
    bmpInfoHeader.bmpHeight = height;
    bmpInfoHeader.colorPlaneCount = 1;
    bmpInfoHeader.colorDepth = 24;
    bmpInfoHeader.compressionMethod = 0;
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.horizontalResolution = 3780;
    bmpInfoHeader.verticalResolution = 3780;
    bmpInfoHeader.colorCount = 0;
    bmpInfoHeader.impColorCount = 0;

    // deleted in destructor
    pixelData = new uint8_t[width * height * 3];

    // all pixels have value 255 i.e. white image
    for (int i; i < width * height * 3; i++)
    {
        pixelData[i] = 255;
    }
}

Bmp::Bmp(char* path)
{
    using namespace std;

    ifstream fin(path, ios::binary);
    uint32_t* temp32 = new uint32_t;
    int32_t* stemp32 = new int32_t;
    uint16_t* temp16 = new uint16_t;

    // initializing bmpHeader
    bmpHeader.fileType[0] = 'B';
    bmpHeader.fileType[1] = 'M';

    fin.seekg(2, ios::beg);
    fin.read((char*) temp32, 4);
    bmpHeader.fileSize = *temp32;

    bmpHeader.reserved = 0;

    fin.seekg(10, ios::beg);
    fin.read((char*) temp32, 4);
    bmpHeader.pixelDataOffset = *temp32;

    // initializing bmpInfoHeader
    bmpInfoHeader.headerSize = 40;

    fin.seekg(18, ios::beg);
    fin.read((char*) temp32, 4);
    bmpInfoHeader.bmpWidth = *temp32;

    fin.seekg(22, ios::beg);
    fin.read((char*) temp32, 4);
    bmpInfoHeader.bmpHeight = *temp32;

    bmpInfoHeader.colorPlaneCount = 1;

    fin.seekg(28, ios::beg);
    fin.read((char*) temp16, 2);
    bmpInfoHeader.colorDepth = *temp16;

    fin.seekg(30, ios::beg);
    fin.read((char*) temp32, 4);
    bmpInfoHeader.compressionMethod = *temp32;

    fin.seekg(34, ios::beg);
    fin.read((char*) temp32, 4);
    bmpInfoHeader.imageSize = *temp32;

    fin.seekg(38, ios::beg);
    fin.read((char*) stemp32, 4);
    bmpInfoHeader.horizontalResolution = *stemp32;

    fin.seekg(42, ios::beg);
    fin.read((char*) stemp32, 4);
    bmpInfoHeader.verticalResolution = *stemp32;

    fin.seekg(46, ios::beg);
    fin.read((char*) temp32, 4);
    bmpInfoHeader.colorCount = *temp32;

    bmpInfoHeader.impColorCount = 0;

    delete temp32;
    delete stemp32;
    delete temp16;

    streampos begin;
    streampos end;
    streampos size;
    fin.seekg(bmpHeader.pixelDataOffset, ios::beg);
    begin = fin.tellg();
    fin.seekg(0, ios::end);
    end = fin.tellg();
    size = end - begin;

    // fix for
    // if size of the image is not a multiple of 3
    if (size % 3 != 0 && bmpInfoHeader.colorDepth == 24)
    {
        // insert bit depth check
        if (true)
        {
            size = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 3;
        }
        else
        {
            size = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 4;
        }
    }

    // deleted in destructor
    pixelData = new uint8_t[size];

    uint8_t* bgr = new uint8_t[size];

    fin.seekg(bmpHeader.pixelDataOffset, ios::beg);
    fin.read((char*) bgr, size);

    // vertical flip + bgr to rgb
    uint8_t* flip = new uint8_t[size];
    int width = bmpInfoHeader.bmpWidth;
    int height = bmpInfoHeader.bmpHeight;

    // vertical flip
    if (bmpInfoHeader.colorDepth == 24)
    {
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
    }
    else if (bmpInfoHeader.colorDepth == 32)
    {
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
    }

    // bgr to rgb
    if (bmpInfoHeader.colorDepth == 24)
    {
        for (int i = 0; i < size; i += 3)
        {
            pixelData[i] = flip[i + 2];
            pixelData[i + 1] = flip[i + 1];
            pixelData[i + 2] = flip[i];
        }
    }
    else if (bmpInfoHeader.colorDepth == 32)
    {
        for (int i = 0; i < size; i += 4)
        {
            pixelData[i] = flip[i + 2];
            pixelData[i + 1] = flip[i + 1];
            pixelData[i + 2] = flip[i];
            pixelData[i + 3] = flip[i + 3];
        }
    }

    delete[] bgr;
    delete[] flip;
    fin.close();
}

Bmp::Bmp(uint8_t* pixelDataInput, int size, int width, int height)
{
    // initializing bmpHeader
    bmpHeader.fileType[0] = 'B';
    bmpHeader.fileType[1] = 'M';
    bmpHeader.fileSize = size + 54;
    bmpHeader.reserved = 0;
    bmpHeader.pixelDataOffset = 54;

    // initializing bmpInfoHeader
    bmpInfoHeader.headerSize = 40;
    bmpInfoHeader.bmpWidth = width;
    bmpInfoHeader.bmpHeight = height;
    bmpInfoHeader.colorPlaneCount = 1;
    bmpInfoHeader.colorDepth = 24;
    bmpInfoHeader.compressionMethod = 0;
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.horizontalResolution = 3780;
    bmpInfoHeader.verticalResolution = 3780;
    bmpInfoHeader.colorCount = 0;
    bmpInfoHeader.impColorCount = 0;

    pixelData = new uint8_t[size];

    for (int i = 0; i < bmpHeader.fileSize - 54; i++)
    {
        pixelData[i] = pixelDataInput[i];
    }
}

Bmp::Bmp(std::vector<unsigned char> &pixelDataInput, int width, int height)
{
    // initializing bmpHeader
    bmpHeader.fileType[0] = 'B';
    bmpHeader.fileType[1] = 'M';
    bmpHeader.fileSize = pixelDataInput.size() + 54;
    bmpHeader.reserved = 0;
    bmpHeader.pixelDataOffset = 54;

    // initializing bmpInfoHeader
    bmpInfoHeader.headerSize = 40;
    bmpInfoHeader.bmpWidth = width;
    bmpInfoHeader.bmpHeight = height;
    bmpInfoHeader.colorPlaneCount = 1;
    bmpInfoHeader.colorDepth = 24;
    bmpInfoHeader.compressionMethod = 0;
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.horizontalResolution = 3780;
    bmpInfoHeader.verticalResolution = 3780;
    bmpInfoHeader.colorCount = 0;
    bmpInfoHeader.impColorCount = 0;

    pixelData = new uint8_t[pixelDataInput.size()];

    for (int i = 0; i < pixelDataInput.size(); i++)
    {
        pixelData[i] = pixelDataInput[i];
    }
}

Bmp::~Bmp() {}

void Bmp::close()
{
    delete[] pixelData;

    // only delete color table if any memory is assigned to it
    if (colorTable != NULL)
    {
        delete[] colorTable;
    }
}

void Bmp::writeToFile(char* path)
{
    std::ofstream fout(path, std::ios::binary);
    fout.write((char*) &bmpHeader, sizeof(bmpHeader));
    fout.write((char*) &bmpInfoHeader, sizeof(bmpInfoHeader));

    // write color table to file only if bit depth is 8bit
    if (bmpInfoHeader.colorDepth == 8)
    {
        fout.write((char*) colorTable, 1024);
    }

    // arranging pixel data as required in bmp format
    // flipping image vertically +
    // rgb to bgr
    uint8_t* flip;
    uint8_t* bgr;
    if (bmpInfoHeader.colorDepth == 8)
    {
        int width = bmpInfoHeader.bmpWidth;
        int height = bmpInfoHeader.bmpHeight;
        flip = new uint8_t[width * height];
        bgr = new uint8_t[width * height];
    }
    else
    {
        flip = new uint8_t[bmpHeader.fileSize - 54];
        bgr = new uint8_t[bmpHeader.fileSize - 54];
    }

    int width = bmpInfoHeader.bmpWidth;
    int height = bmpInfoHeader.bmpHeight;

    // vertical flip
    if (bmpInfoHeader.colorDepth == 24)
    {
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    flip[(i + j * width) * 3 + k] = pixelData[(i + (height - 1 - j) * width) * 3 + k];
                }
            }
        }
    }
    else if (bmpInfoHeader.colorDepth == 32)
    {
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                for (int k = 0; k < 4; ++k)
                {
                    flip[(i + j * width) * 4 + k] = pixelData[(i + (height - 1 - j) * width) * 4 + k];
                }
            }
        }
    }
    else if (bmpInfoHeader.colorDepth == 8)
    {
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                for (int k = 0; k < 1; ++k)
                {
                    flip[(i + j * width) * 1 + k] = pixelData[(i + (height - 1 - j) * width) * 1 + k];
                }
            }
        }
    }

    // rgb to bgr
    if (bmpInfoHeader.colorDepth == 24)
    {
        for (int i = 0; i < bmpHeader.fileSize - 54; i += 3)
        {
            bgr[i] = flip[i + 2];
            bgr[i + 1] = flip[i + 1];
            bgr[i + 2] = flip[i];
        }
    }
    else if (bmpInfoHeader.colorDepth == 32)
    {
        for (int i = 0; i < bmpHeader.fileSize - 54; i += 4)
        {
            bgr[i] = flip[i + 2];
            bgr[i + 1] = flip[i + 1];
            bgr[i + 2] = flip[i];
            bgr[i + 3] = flip[i + 3];
        }
    }
    else if (bmpInfoHeader.colorDepth == 8)
    {
        for (int i = 0; i < width* height; i++)
        {
            bgr[i] = flip[i];
        }
    }

    fout.write((char*) bgr, bmpHeader.fileSize - 54);
    fout.close();

    delete[] flip;
    delete[] bgr;
}

void Bmp::setDotDensity(int dpi)
{
    // convert dots per inch to pixel per metre
    uint32_t ppm = 39.370079f * dpi;
    bmpInfoHeader.horizontalResolution = ppm;
    bmpInfoHeader.verticalResolution = ppm;
}

void Bmp::setBitDepth(int b)
{
    if (b == 24)
    {
        bmpHeader.fileSize = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 3 + 54;
        bmpInfoHeader.colorDepth = b;
        bmpInfoHeader.imageSize = bmpHeader.fileSize;
    }
    else if (b == 32)
    {
        bmpHeader.fileSize = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 4 + 54;
        bmpInfoHeader.colorDepth = b;
        bmpInfoHeader.imageSize = bmpHeader.fileSize;
    }
    else if (b == 8)
    {
        // 1024 is size of full 256 entry colortable;
        bmpHeader.fileSize = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight + 1024 + 54;
        bmpInfoHeader.colorDepth = b;
        bmpInfoHeader.imageSize = bmpHeader.fileSize;
        bmpHeader.pixelDataOffset = 54 + 1024;
        bmpInfoHeader.colorCount = 256;
        bmpInfoHeader.impColorCount = 256;
    }
}

uint32_t Bmp::getHeight()
{
    return bmpInfoHeader.bmpHeight;
}

uint32_t Bmp::getWidth()
{
    return bmpInfoHeader.bmpWidth;
}

uint8_t* Bmp::getPixelDataInt()
{
    uint8_t* result = new uint8_t[bmpHeader.fileSize - 54];
    for (int i = 0; i < bmpHeader.fileSize - 54; i++)
    {
        result[i] = pixelData[i];
    }
    return result;
}

unsigned char* Bmp::getPixelDataChar()
{
    unsigned char* result = new unsigned char[bmpHeader.fileSize - 54];
    for (int i = 0; i < bmpHeader.fileSize - 54; i++)
    {
        result[i] = pixelData[i];
    }
    return result;
}

int Bmp::size()
{
    return bmpHeader.fileSize - 54;
}

void Bmp::setColorTable(uint8_t* input)
{
    colorTable = new uint8_t[1024];
    for (int i = 0; i < 1024; i++)
    {
        colorTable[i] = input[i];
    }
}