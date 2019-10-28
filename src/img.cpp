#include "CIMP/img.hpp"
#include <iostream>
using namespace cp;

Img::Img(uint8_t* pixelData, int colorDepth, int width, int height)
{
    this->pixelData = pixelData;
    if (colorDepth == 24)
    {
        this->colorDepth = colorDepth;
    }
    else if (colorDepth == 32)
    {
        this->colorDepth = 32;
    }
    else
    {
        this->colorDepth = NULL;
    }
    this->width = width;
    this->height = height;
}

Img::Img(const Img &obj)
{
    width = obj.width;
    height = obj.height;
    colorDepth = obj.colorDepth;

    pixelData = new uint8_t[obj.size()];
    for (int i = 0; i < obj.size(); i++)
    {
        pixelData[i] = obj.pixelData[i];
    }
}

Img::~Img()
{
    if (pixelData != NULL)
    {
        delete[] pixelData;
    }
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
        return NULL;
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
        return NULL;
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
    std::cout << this->size() << std::endl;
    uint8_t* result = new uint8_t[this->size()];
    for (int i = 0; i < this->size(); i++)
    {
        result[i] = pixelData[i];
    }
    return result;
}