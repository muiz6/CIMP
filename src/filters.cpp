#include "CIMP/filters.hpp"
#include <iostream>
#include <cstdint>
using namespace cp;

Filters::Filters(uint8_t* pixelDataInput, int colorDepth, int width, int height)
: Img(pixelDataInput, colorDepth, width, height) {}

Filters::Filters(Img &img): Img(img) {}

Filters::~Filters() {}

void Filters::grayScale()
{
    uint32_t size = getWidth() * getHeight() * 3;
    uint8_t* filteredPixels = new uint8_t[size];

    // applying filter in new image
    for(unsigned int i = 0; i < size; i += 3)
    {
        int avg = (pixelData[i] + pixelData[i + 1] + pixelData[i + 2]) / 3;
        filteredPixels[i] = avg;
        filteredPixels[i+1] = avg;
        filteredPixels[i+2] = avg;
    }

    // copying filtered image in pixelData
    for (unsigned int i = 0; i < size; i++)
    {
        pixelData[i] = filteredPixels[i];
    }

    delete[] filteredPixels;
}

void Filters::invert()
{
    uint32_t size = getWidth() * getHeight() * 3;
    uint8_t* filteredPixels = new uint8_t[size];

    //new invert filter
    for (unsigned int i = 0; i < size; i++)
    {
        filteredPixels[i] = 255 - pixelData[i];
    }

    // copying filtered image in pixelData
    for (int i = 0; i < size; i++)
    {
        pixelData[i] = filteredPixels[i];
    }

    delete[] filteredPixels;
}

void Filters::alienate()
{
    uint32_t size = getWidth() * getHeight() * 3;
    uint8_t* filteredPixels = new uint8_t[size];

    //applying new filters
    for(int i = 0 ; i < size; i+=3)
    {
        filteredPixels[i]=pixelData[i+1];
        filteredPixels[i+1]=pixelData[i+2];
        filteredPixels[i+2]=pixelData[i];
    }
    // copying filtered image in pixelData
    for (int i = 0; i < size; i++)
    {
        pixelData[i] = filteredPixels[i];
    }

    delete[] filteredPixels;
}

void Filters:: verticalFlip()
{
    uint32_t size = getWidth() * getHeight() * 3;
    uint8_t* filteredPixels = new uint8_t[size];

    //vertical flip
    for (int i = 0; i < getWidth(); ++i)
    {
        for (int j = 0; j < getHeight(); ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                filteredPixels[(i + j * getWidth()) * 3 + k] = pixelData[(i + (getHeight() - 1 - j) * getWidth()) * 3 + k];
            }
        }
    }

    // copying filtered image in pixelData
    for (int i = 0; i < size; i++)
    {
        pixelData[i] = filteredPixels[i];
    }

    delete[] filteredPixels;
}
