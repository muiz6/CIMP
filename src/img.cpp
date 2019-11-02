#include "CIMP/img.hpp"
#include <iostream>
using namespace cp;

Img::Img() {}

Img::Img(uint8_t* pixelDataInput, int colorDepthInput, int width, int height)
    :width(width), height(height)
{
    uint32_t size;
    if (colorDepthInput == 24)
    {
        colorDepth = colorDepthInput;
        size = width * height * 3;
    }
    else if (colorDepthInput == 32)
    {
        colorDepth = colorDepthInput;
        size = width * height * 4;
    }
    else
    {
        this->colorDepth = 0;
    }

    pixelData = new uint8_t[size];
    for (uint32_t i = 0; i < size; i++)
    {
        pixelData[i] = pixelDataInput[i];
    }
}

Img::Img(const Img &obj)
{
    width = obj.width;
    height = obj.height;
    colorDepth = obj.colorDepth;

    pixelData = new uint8_t[obj.size()];
    for (unsigned int i = 0; i < obj.size(); i++)
    {
        pixelData[i] = obj.pixelData[i];
    }
}

Img::~Img()
{
    delete[] pixelData;
}

uint32_t Img::size() const
{
    if (colorDepth == 24)
    {
        uint32_t size = width * height * 3;
        return size;
    }
    else if (colorDepth == 32)
    {
        uint32_t size = width * height * 4;
        return size;
    }
    else
    {
        return 0;
    }
}

int Img::getColorDepth()
{
    if (colorDepth == 24)
    {
        return colorDepth;
    }
    else if (colorDepth == 32)
    {
        return colorDepth;
    }
    else
    {
        return 0;
    }
}

int Img::getWidth()
{
    return width;
}

int Img::getHeight()
{
    return height;
}

uint8_t* Img::getPixelDataInt()
{
    uint8_t* result = new uint8_t[this->size()];
    for (int i = 0; i < this->size(); i++)
    {
        result[i] = pixelData[i];
    }
    return result;
}

Img Img::getImg24()
{
    if (colorDepth == 24)
    {
        Img img(pixelData, 24, width, height);
        return img;
    }
    else if (colorDepth == 32)
    {
        uint32_t size = width * height * 3;
        uint8_t* pixelDataInput = new uint8_t[size];
        for (unsigned int i = 0, j = 0; i < size; i += 3, j += 4)
        {
            pixelDataInput[i] = pixelData[j];
            pixelDataInput[i + 1] = pixelData[j + 1];
            pixelDataInput[i + 2] = pixelData[j + 2];
            // pixelData[j + 3] is skipped
        }
        Img img(pixelDataInput, 24, width, height);
        delete[] pixelDataInput;
        return img;
    }
    else
    {
        return Img();
    }
}

Img Img::getImg32()
{
    if (colorDepth == 24)
    {
        uint32_t size = width * height * 4;
        uint8_t* pixelDataInput = new uint8_t[size];
        for (unsigned int i = 0, j = 0; j < size; i += 3, j += 4)
        {
            pixelDataInput[j] = pixelData[i];
            pixelDataInput[j + 1] = pixelData[i + 1];
            pixelDataInput[j + 2] = pixelData[i + 2];
            pixelDataInput[j + 3] = 255;
        }
        Img img(pixelDataInput, 32, width, height);
        delete[] pixelDataInput;
        return img;
    }
    else if (colorDepth == 32)
    {
        Img img(pixelData, 32, width, height);
        return img;
    }
    else
    {
        return Img();
    }
}