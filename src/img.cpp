#include "CIMP/img.hpp"
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

Img::~Img()
{
    if (pixelData != NULL)
    {
        delete[] pixelData;
    }
}

unsigned long Img::size()
{
    if (colorDepth == 24)
    {
        unsigned long size = width * height * 3;
    }
    else if (colorDepth == 32)
    {
        unsigned long size = width * height * 4;
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
