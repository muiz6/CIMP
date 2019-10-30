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
    for (int i = 0; i < width * height * 3; i++)
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

    // to read color table for 8bit bmp
    if (bmpInfoHeader.colorDepth == 8)
    {
        uint32_t colCount;
        fin.seekg(46);
        fin.read((char*) &colCount, 4);
        unsigned int colTableSize = colCount * 4;
        fin.seekg(54);
        colorTable = new uint8_t[colTableSize];
        fin.read((char*) colorTable, colTableSize);
    }

    // to read pixel data

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
    else if (bmpInfoHeader.colorDepth == 8)
    {
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
    else if (bmpInfoHeader.colorDepth == 8)
    {
        for (int i = 0; i < size; i++)
        {
            pixelData[i] = flip[i];
        }
    }

    delete[] bgr;
    delete[] flip;
    fin.close();
}

Bmp::Bmp(uint8_t* pixelDataInput, int colorDepth, int width, int height)
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

    if (colorDepth == 24)
    {
        uint32_t size = width * height * 3;
        pixelData = new uint8_t[size];
    }
    else if (colorDepth == 32)
    {
        uint32_t size = width * height * 4;
        pixelData = new uint8_t[size];
    }

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

Bmp::Bmp(Img &img)
{
    // initializing bmpHeader
    bmpHeader.fileType[0] = 'B';
    bmpHeader.fileType[1] = 'M';
    bmpHeader.fileSize = img.size() + 54;
    bmpHeader.reserved = 0;
    bmpHeader.pixelDataOffset = 54;

    // initializing bmpInfoHeader
    bmpInfoHeader.headerSize = 40;
    bmpInfoHeader.bmpWidth = img.getWidth();
    bmpInfoHeader.bmpHeight = img.getHeight();
    bmpInfoHeader.colorPlaneCount = 1;
    bmpInfoHeader.colorDepth = 24;
    bmpInfoHeader.compressionMethod = 0;
    bmpInfoHeader.imageSize = bmpHeader.fileSize;
    bmpInfoHeader.horizontalResolution = 3780;
    bmpInfoHeader.verticalResolution = 3780;
    bmpInfoHeader.colorCount = 0;
    bmpInfoHeader.impColorCount = 0;

    uint8_t* pixelDataInput = img.getPixelDataInt();

    pixelData = new uint8_t[img.size()];
    for (int i = 0; i < img.size(); i++)
    {
        pixelData[i] = pixelDataInput[i];
    }

    delete[] pixelDataInput;
}

Bmp::~Bmp() {}

void Bmp::close()
{
    // erasing bmpHeader
    bmpHeader.fileType[0] = NULL;
    bmpHeader.fileType[1] = NULL;
    bmpHeader.fileSize = NULL;
    bmpHeader.reserved = NULL;
    bmpHeader.pixelDataOffset = NULL;

    // erasing bmpInfoHeader
    bmpInfoHeader.headerSize = NULL;
    bmpInfoHeader.bmpWidth = NULL;
    bmpInfoHeader.bmpHeight = NULL;
    bmpInfoHeader.colorPlaneCount = NULL;
    bmpInfoHeader.colorDepth = NULL;
    bmpInfoHeader.compressionMethod = NULL;
    bmpInfoHeader.imageSize = NULL;
    bmpInfoHeader.horizontalResolution = NULL;
    bmpInfoHeader.verticalResolution = NULL;
    bmpInfoHeader.colorCount = NULL;
    bmpInfoHeader.impColorCount = NULL;

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
    // converting 8bit to 24bit rgb
    if (bmpInfoHeader.colorDepth == 8)
    {
        uint32_t size = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 3;
        uint8_t* result = new uint8_t[size];
        for (int i = 0; i < bmpHeader.fileSize - 1024 - 54; i++)
        {
            int j = 3 * i;
            int k = 4 * i;
            result[j] = colorTable[k];
            result[j + 1] = colorTable[k + 1];
            result[j + 2] = colorTable[k + 2];
            // alpha value colorTable[k + 3] is skipped
        }

        // converting bgr to rgb
        for (int i = 0; i < size; i += 3)
        {
            uint8_t temp = result[i];
            result[i] = result[i + 2];
            // result[i + 1] is ignored
            result[i + 2] = temp;
        }
        return result;
    }
    else if (bmpInfoHeader.colorDepth == 24)
    {
        uint32_t size = bmpHeader.fileSize - 54;
        uint8_t* result = new uint8_t[size];
        for (int i = 0; i < bmpHeader.fileSize - 54; i++)
        {
            result[i] = pixelData[i];
        }
        return result;
    }
    else if (bmpInfoHeader.colorDepth == 32)
    {
        uint32_t size = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 3;
        uint8_t* result = new uint8_t[size];

        int i = 0;
        int j = 0;
        while (i < size)
        {
            result[j] = pixelData[i];
            result[j + 1] = pixelData[i + 1];
            result[j + 2] = pixelData[i + 2];
            // alpha value: pixelData[i + 3] is skipped

            i += 4;
            j += 3;
        }
        return result;
    }
    else
    {
        return NULL;
    }
}

unsigned char* Bmp::getPixelDataChar()
{
    if (bmpInfoHeader.colorDepth == 24)
    {
        unsigned char* result = new unsigned char[bmpHeader.fileSize - 54];
        for (int i = 0; i < bmpHeader.fileSize - 54; i++)
        {
            result[i] = pixelData[i];
        }
        return result;
    }
    else if (bmpInfoHeader.colorDepth == 32)
    {
        uint32_t size;
    }
    else if (bmpInfoHeader.colorDepth == 8)
    {

    }
    else
    {
        return NULL;
    }
}

int Bmp::size()
{
    return bmpHeader.fileSize - 54;
}

cp::Img Bmp::getImg24()
{
    // uint32_t size = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 3;
    // uint8_t* pixelDataInput = new uint8_t[size];
    // for (int i=0;i<size;i++)
    // {
    //     pixelDataInput[i] = pixelData[i];
    // }

    // converting 8bit to 24bit rgb
    uint8_t* pixelDataInput = NULL;
    if (bmpInfoHeader.colorDepth == 8)
    {
        uint32_t size = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 3;
        pixelDataInput = new uint8_t[size];
        for (int i = 0; i < bmpHeader.fileSize - 1024 - 54; i++)
        {
            int j = 3 * i;
            int k = 4 * i;
            pixelDataInput[j] = colorTable[k];
            pixelDataInput[j + 1] = colorTable[k + 1];
            pixelDataInput[j + 2] = colorTable[k + 2];
            // alpha value colorTable[k + 3] is skipped
        }

        // converting bgr to rgb
        for (int i = 0; i < size; i += 3)
        {
            uint8_t temp = pixelDataInput[i];
            pixelDataInput[i] = pixelDataInput[i + 2];
            // pixelData[i + 1] is ignored
            pixelDataInput[i + 2] = temp;
        }
    }
    else if (bmpInfoHeader.colorDepth == 24)
    {
        uint32_t size = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 3;
        uint8_t* pixelDataInput = new uint8_t[size];
        for (int i = 0; i < size; i++)
        {
            pixelDataInput[i] = pixelData[i];
        }
    }
    else if (bmpInfoHeader.colorDepth == 32)
    {
        uint32_t size = bmpInfoHeader.bmpWidth * bmpInfoHeader.bmpHeight * 4;
        pixelDataInput = new uint8_t[size];

        int i = 0;
        int j = 0;
        while (i < size)
        {
            pixelDataInput[j] = pixelData[i];
            pixelDataInput[j + 1] = pixelData[i + 1];
            pixelDataInput[j + 2] = pixelData[i + 2];
            // alpha value: pixelData[i + 3] is skipped

            i += 4;
            j += 3;
        }
    }

    int imgWidth = bmpInfoHeader.bmpWidth;
    int imgHeight = bmpInfoHeader.bmpHeight;

    std::cout << bmpHeader.fileSize - 54<<std::endl;
    Img img(pixelDataInput, 24, imgWidth, imgHeight);
    // Img img = new Img(pixelDataInput, 24, imgWidth, imgHeight);

    delete[] pixelDataInput;

    return img;
}

Img Bmp::getImg32() {}

void Bmp::write8BitBmp(char* path) {}

void Bmp::write24BitBmp(char* path)
{
    if (bmpInfoHeader.colorDepth == 8)
    {

    }
    else if (bmpInfoHeader.colorDepth == 24)
    {

    }
    else if (bmpInfoHeader.colorDepth == 32)
    {

    }
}

void Bmp::write32BitBmp(char* path) {}