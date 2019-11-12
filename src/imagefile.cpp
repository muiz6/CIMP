#include "CIMP/imagefile.hpp"
#include "CIMP/imagefileinterface.hpp"
#include "CIMP/bmp.hpp"
#include "CIMP/bmp24bit.hpp"
#include "CIMP/bmp32bit.hpp"
#include "CIMP/bmp8bit.hpp"
using namespace cp;

ImageFile::ImageFile(uint8_t* pixelDataInput, int colorDepth, int width, int height)
    : flagIsOpen(true), Img(pixelData, colorDepth, width, height)
{
    if (colorDepth != 24 && colorDepth != 32)
    {
        flagIsOpen = false;
    }
}

ImageFile::ImageFile(const Img &img): flagIsOpen(true), Img(img) {}

ImageFile::ImageFile(const char *path, ImageReadType type)
    : flagIsOpen(true)
{
    if (type == anyImage)
    {
        if (Bmp::isBmp(path))
        {

        }
        else if(false) //isPNG?
        {

        }
        else
        {
            flagIsOpen = false;
        }
    }
    else if (type == bmp)
    {
        if (Bmp::isBmp(path))
        {

        }
        else
        {
            flagIsOpen = false;
        }
    }
    else if (type == png)
    {
        if (false)
        {

        }
        else
        {
            flagIsOpen = false;
        }
    }
    else
    {
        flagIsOpen = false;
    }
}

ImageFile::ImageFile(std::string path, ImageReadType type)
    : ImageFile(path.c_str(), type) {}

ImageFile::~ImageFile() {}

bool ImageFile::isOpen()
{
    return flagIsOpen;
}

void ImageFile::writeToFile(const char* path, ImageType type)
{
    ImageFileInterface *img;
    if (type == bitmap24Bit)
    {
        img = new Bmp24Bit(*this);
        img->writeToFile(path);
    }
    else if (type == bitmap32Bit)
    {
        img = new Bmp32Bit(*this);
        img->writeToFile(path);
    }
    else if (type == bitmap8Bit)
    {
        img = new Bmp8Bit(*this);
        img->writeToFile(path);
    }
    delete img;
}

void ImageFile::writeToFile(std::string path, ImageType type)
{
    writeToFile(path.c_str(), type);
}