#include "CIMP/bmp.hpp"
#include <fstream>
#include <iostream>

using namespace cp;

Bmp::Bmp(int width, int height)
: Img(NULL, 24, width, height)
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
    for (int i = 0; i < width * height * 3; i++)
    {
        pixelData[i] = 255;
    }
}

Bmp::Bmp(const char* path)
// : Img()
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
    fin.read((char*) stemp32, 4);
    bmpInfoHeader.bmpWidth = *stemp32;

    fin.seekg(22, ios::beg);
    fin.read((char*) stemp32, 4);
    bmpInfoHeader.bmpHeight = *stemp32;

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
    fin.read((char*) temp32, 4);
    bmpInfoHeader.horizontalResolution = *temp32;

    fin.seekg(42, ios::beg);
    fin.read((char*) temp32, 4);
    bmpInfoHeader.verticalResolution = *temp32;

    fin.seekg(46, ios::beg);
    fin.read((char*) temp32, 4);
    bmpInfoHeader.colorCount = *temp32;

    fin.seekg(50, ios::beg);
    fin.read((char*) temp32, 4);
    bmpInfoHeader.impColorCount = *temp32;

    delete temp32;
    delete stemp32;
    delete temp16;

    // to read color table for 8bit bmp
    if (bmpInfoHeader.colorDepth == 8)
    {
        unsigned int colTableSize = bmpInfoHeader.colorCount * 4;

        // usual offset of color table
        fin.seekg(bmpHeader.pixelDataOffset - colTableSize);
        colorTable = new uint8_t[colTableSize];
        fin.read((char*) colorTable, colTableSize);
    }

    // initialize cp::Img members
    width = bmpInfoHeader.bmpWidth;
    height = bmpInfoHeader.bmpHeight;

    // actual color depth of stored pixel data
    if (bmpInfoHeader.colorDepth == 8 || bmpInfoHeader.colorDepth == 24)
    {
        colorDepth = 24;
    }
    else if (bmpInfoHeader.colorDepth == 32)
    {
        colorDepth = 32;
    }
    else
    {
        colorDepth = 0;
    }

    // bytes of pixel data to be read from file
    // so it works even if img is missing some pixels
    streampos begin, end, readSize;
    fin.seekg(bmpHeader.pixelDataOffset, ios::beg);
    begin = fin.tellg();
    fin.seekg(0, ios::end);
    end = fin.tellg();
    readSize = end - begin;

    // for reading 8bit indexed pixel data
    if (bmpInfoHeader.colorDepth == 8)
    {
        uint32_t arrSize = width * height * 3;
        pixelData = new uint8_t[arrSize];

        // to read and process pixel data
        uint8_t* bgr = new uint8_t[readSize];
        uint8_t* flip = new uint8_t[readSize];
        fin.seekg(bmpHeader.pixelDataOffset, ios::beg);
        fin.read((char*) bgr, readSize);

        // vertical flip
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                for (int k = 0; k < 1; ++k)
                {
                    flip[(i + j * width) * 1 + k] = bgr[(i + (height - 1 - j) * width) * 1 + k];
                }
            }
        }

        // converting to 24bit rgb
        for (int i = 0; i < readSize; i++)
        {
            int index = flip[i];
            pixelData[3 * i] = colorTable[4 * index + 2];
            pixelData[3 * i + 1] = colorTable[4 * index + 1];
            pixelData[3 * i + 2] = colorTable[4 * index];
            // colorTable[4 * i + 3] is ignored
        }

        delete[] bgr;
        delete[] flip;
    }

    // for reading 24bit or 32bit non indexed pixel data
    else
    {
        // accurate size of pixel data
        uint32_t arrSize;
        if (bmpInfoHeader.colorDepth == 24)
        {
            arrSize = width * height * 3;
        }
        else if (bmpInfoHeader.colorDepth == 32)
        {
            arrSize = width * height * 4;
        }
        pixelData = new uint8_t[arrSize];

        // to read and process pixel data
        uint8_t* bgr = new uint8_t[arrSize];
        uint8_t* flip = new uint8_t[arrSize];
        fin.seekg(bmpHeader.pixelDataOffset, ios::beg);
        fin.read((char*) bgr, readSize);

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
            for (int i = 0; i < arrSize; i += 3)
            {
                pixelData[i] = flip[i + 2];
                pixelData[i + 1] = flip[i + 1];
                pixelData[i + 2] = flip[i];
            }
        }
        else if (bmpInfoHeader.colorDepth == 32)
        {
            for (int i = 0; i < arrSize; i += 4)
            {
                pixelData[i] = flip[i + 2];
                pixelData[i + 1] = flip[i + 1];
                pixelData[i + 2] = flip[i];
                pixelData[i + 3] = flip[i + 3];
            }
        }

        delete[] bgr;
        delete[] flip;
    }

    fin.close();
}

Bmp::Bmp(uint8_t* pixelDataInput, int colorDepth, int width, int height)
: Img(pixelDataInput, colorDepth, width, height)
{
    // initializing bmpHeader
    bmpHeader.fileType[0] = 'B';
    bmpHeader.fileType[1] = 'M';
    if (colorDepth == 24)
    {
        bmpHeader.fileSize = width * height * 3 + 54;
    }
    else if (colorDepth == 32)
    {
        bmpHeader.fileSize = width * height * 3 + 54;
    }
    else
    {
        bmpHeader.fileSize = 0;
    }
    bmpHeader.reserved = 0;
    bmpHeader.pixelDataOffset = 54;

    // initializing bmpInfoHeader
    bmpInfoHeader.headerSize = 40;
    bmpInfoHeader.bmpWidth = width;
    bmpInfoHeader.bmpHeight = height;
    bmpInfoHeader.colorPlaneCount = 1;
    bmpInfoHeader.colorDepth = colorDepth;
    bmpInfoHeader.compressionMethod = 0;
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.horizontalResolution = 3780;
    bmpInfoHeader.verticalResolution = 3780;
    bmpInfoHeader.colorCount = 0;
    bmpInfoHeader.impColorCount = 0;
}

Bmp::Bmp(Img &img)
: Img(img)
{
    // initializing bmpHeader
    bmpHeader.fileType[0] = 'B';
    bmpHeader.fileType[1] = 'M';
    bmpHeader.fileSize = size() + 54;
    bmpHeader.reserved = 0;
    bmpHeader.pixelDataOffset = 54;

    // initializing bmpInfoHeader
    bmpInfoHeader.headerSize = 40;
    bmpInfoHeader.bmpWidth = getWidth();
    bmpInfoHeader.bmpHeight = getHeight();
    bmpInfoHeader.colorPlaneCount = 1;
    bmpInfoHeader.colorDepth = 24;
    bmpInfoHeader.compressionMethod = 0;
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.horizontalResolution = 3780;
    bmpInfoHeader.verticalResolution = 3780;
    bmpInfoHeader.colorCount = 0;
    bmpInfoHeader.impColorCount = 0;
}

Bmp::~Bmp()
{
    // delete colorTable only if memory is assigned to it
    if (colorTable != NULL)
    {
        delete[] colorTable;
    }
}

void Bmp::writeToFile(const char* path)
{
    std::ofstream fout(path, std::ios::binary);

    // write bmpHeader and bmpInfoHeader
    fout.write((char*) &bmpHeader, sizeof(bmpHeader));
    fout.write((char*) &bmpInfoHeader, sizeof(bmpInfoHeader));

    // write color table to file only if color depth is 8bit
    if (bmpInfoHeader.colorDepth == 8)
    {
        fout.write((char*) colorTable, 1024);
    }

    // arranging pixel data as required in bmp format
    // flipping image vertically +
    // rgb to bgr
    uint8_t* flip;
    uint8_t* bgr;
    uint32_t size;
    int width = bmpInfoHeader.bmpWidth;
    int height = bmpInfoHeader.bmpHeight;

    if (bmpInfoHeader.colorDepth == 8)
    {
        int width = bmpInfoHeader.bmpWidth;
        int height = bmpInfoHeader.bmpHeight;
        flip = new uint8_t[width * height];
        bgr = new uint8_t[width * height];
    }
    else if (bmpInfoHeader.colorDepth == 24)
    {
        size = width * height * 3;
        flip = new uint8_t[size];
        bgr = new uint8_t[size];
    }
    else if (bmpInfoHeader.colorDepth == 32)
    {
        size = width * height * 4;
        flip = new uint8_t[size];
        bgr = new uint8_t[size];
    }

    // vertical flip
    if (bmpInfoHeader.colorDepth == 8)
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
    else if (bmpInfoHeader.colorDepth == 24)
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

    // rgb to bgr
    if (bmpInfoHeader.colorDepth == 8)
    {
        for (int i = 0; i < width* height; i++)
        {
            bgr[i] = flip[i];
        }
    }
    else if (bmpInfoHeader.colorDepth == 24)
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

void Bmp::write8BitBmp(const char* path) {}

void Bmp::write24BitBmp(const char* path)
{
    std::ofstream fout(path, std::ios::binary);

    // write bmpHeader and bmpInfoHeader
    fout.write((char*) &bmpHeader, sizeof(bmpHeader));
    fout.write((char*) &bmpInfoHeader, sizeof(bmpInfoHeader));

    uint8_t *flip, *bgr;
    uint32_t size;
    int width = bmpInfoHeader.bmpWidth;
    int height = bmpInfoHeader.bmpHeight;

    if (colorDepth == 24)
    {
        size = width * height * 3;
        flip = new uint8_t[size];
        bgr = new uint8_t[size];
    }
    else if (colorDepth == 32)
    {
        size = width * height * 4;
        flip = new uint8_t[size];
        bgr = new uint8_t[size];
    }

    // vertical flip
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

    // rgb to bgr
    for (int i = 0; i < bmpHeader.fileSize - 54; i += 3)
    {
        bgr[i] = flip[i + 2];
        bgr[i + 1] = flip[i + 1];
        bgr[i + 2] = flip[i];
    }

    fout.write((char*) bgr, bmpHeader.fileSize - 54);
    fout.close();

    delete[] flip;
    delete[] bgr;

    fout.close();
}

void Bmp::write32BitBmp(const char* path) {}