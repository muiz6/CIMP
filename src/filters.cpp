#include "CIMP/filters.hpp"
#include <iostream>
#include <cstdint>
using namespace cp;



Filters::Filters(uint8_t* pixelDataInput, int colorDepth, int width, int height)
: Img(pixelDataInput, colorDepth, width, height) {}

Filters::Filters(Img &img): Img(img) {}

Filters::~Filters() {}

// GrayScale filter
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
// Invert filter
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
// Alienate Filter(swapping RGB Values)
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
// Flip Vertically function Perfom
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
//  Dark Red Filters function 
void Filters::red()
{
    uint32_t size = width * height * 3;
    uint8_t* filteredPixels = new uint8_t[size];
    
    //Applying Red filter
    for(int i = 0; i < height; i++)
        for(int j=0; j < width; j++)
    {
        filteredPixels[(i * width + j)*3] = 255 - pixelData[(i * width + j)*3];
    }
    
    
    //copying filtered image in pixelData
    for(int i = 0; i < size; i++)
    {
        pixelData[i]=filteredPixels[i];
    
    }

    delete[] filteredPixels;
}
// Dark Green Filter Function
void Filters:: green()
{
    uint32_t size = width * height * 3;
    uint8_t* filteredPixels = new uint8_t[size];
    
    //Applying green filter
    for(int i = 0; i < height; i++)
        for(int j=0; j < width; j++)
    {
        filteredPixels[(i * width + j) * 3 + 1] = 255 - pixelData[(i * width + j)* 3 + 1];
    }
    
    
    //copying filtered image in pixelData
    for(int i = 0; i < size; i++)
    {
        pixelData[i]=filteredPixels[i];
    
    }

    delete[] filteredPixels;
}
// Dark Blue filter function
void Filters:: blue()
{
    uint32_t size = width * height * 3;
    uint8_t* filteredPixels = new uint8_t[size];
    
    //Applying blue filter
    for(int i = 0; i < height; i++)
    {
        for(int j=0; j < width; j++)
        {
            filteredPixels[(i * width + j)* 3 + 2] = 255 - pixelData[(i * width + j)* 3 + 2];
        }
    }
    
    
    //copying filtered image in pixelData
    for(int i = 0; i < size; i++)
    {
        pixelData[i]=filteredPixels[i];
    
    }

    delete[] filteredPixels;
}

// silly filter (redish and sky blue color)
void Filters:: silly()
{
    uint32_t size = width * height * 3;
    uint8_t* filteredPixels = new uint8_t[size];
    //Applying  filter
    for(int i = 0; i < size; i += 3)
    {
        int avg = (pixelData[i] + pixelData[i + 1] + pixelData[i + 2]) / 3 ;
        filteredPixels[i] = avg;
        filteredPixels[i+1] = avg;
        filteredPixels[i+2] = avg;
    }
    for(int i = 0; i < height; i++)
        for(int j=0; j < width; j++)
    {
        filteredPixels[(i * width + j)* 3] = 255 - pixelData[(i * width + j)* 3];
        
    }
    //copying filtered image in pixelData
    for(int i = 0; i < size; i++)
    {
        pixelData[i]=filteredPixels[i];
    
    }

    delete[] filteredPixels;

}
//painty filter (similer to the oil paint filter)
void Filters:: sepia()
{
    uint32_t size = width * height * 3;
    uint8_t* filteredPixels = new uint8_t[size];
    silly();
    //sepia image formula
    for(int i = 0; i < size; i += 3)
    {
        filteredPixels[i] = (0.393*pixelData[i] + 0.769*pixelData[i+1] + 0.189*pixelData[i+2]);
        filteredPixels[i+1] = (0.349*pixelData[i] + 0.686*pixelData[i+1] + 0.168*pixelData[i+2]);
        filteredPixels[i+2] = (0.272*pixelData[i] + 0.534*pixelData[i+1] + 0.131*pixelData[i+2]);
    }
    //copying filtered image in pixelData
    for(int i = 0; i < size; i++)
    {
        pixelData[i]=filteredPixels[i];
    
    }

    delete[] filteredPixels;

}
