#include "CIMP/img.hpp"
#include <iostream>
using namespace cp;

Img::Img(uint8_t* pixelDataInput, int colorDepthInput, int width, int height)
{
    // pixelData = pixelDataInput;
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
    // else
    // {
    //     this->colorDepth = NULL;
    // }
    std::cout << size << std::endl;
    this->width = width;
    this->height = height;
    // std::cout << "Test\n";

    pixelData = new uint8_t[size];
    for (uint32_t i = 0; i < size; i++)
    {
        pixelData[i] = pixelDataInput[i];
        // std::cout << i << std::endl;
    }
}

Img::Img(const Img &obj)
{
    std::cout << "copy ctor called\n";
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
    // delete[] pixelData;
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