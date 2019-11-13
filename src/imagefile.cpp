#include "CIMP/imagefile.hpp"
#include "CIMP/imagefileinterface.hpp"
#include "CIMP/bmp.hpp"
#include "CIMP/bmp24bit.hpp"
#include "CIMP/bmp32bit.hpp"
#include "CIMP/bmp8bit.hpp"
using namespace cp;

ImageFile::ImageFile(uint8_t* pixelDataInput, int colorDepth, int width, int height)
    : flagIsOpen(true), Img(pixelDataInput, colorDepth, width, height)
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
    if (type == ANY_IMAGE)
    {
        if (Bmp::isBmp(path))
        {
            Bmp bmp(path);
            if (bmp.isOpen())
            {
                colorDepth = bmp.getColorDepth();
                height = bmp.getHeight();
                width = bmp.getWidth();
                pixelData = bmp.getPixelDataInt();
            }
            else
            {
                flagIsOpen = false;
            }
        }
        else if (false) //isPNG?
        {
            // read png file
        }
        else
        {
            flagIsOpen = false;
        }
    }
    else if (type == BITMAP_IMAGE)
    {
        if (Bmp::isBmp(path))
        {
            Bmp bmp(path);
            if (bmp.isOpen())
            {
                colorDepth = bmp.getColorDepth();
                height = bmp.getHeight();
                width = bmp.getWidth();
                pixelData = bmp.getPixelDataInt();
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
    else if (type == PNG_IMAGE)
    {
        if (false) // isPNG?
        {
            // read png file
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

void ImageFile::writeToFile(const char* path, ImageWriteType type)
{
    ImageFileInterface *img;
    if (type == BITMAP_24_BIT)
    {
        img = new Bmp24Bit(*this);
        img->writeToFile(path);
    }
    else if (type == BITMAP_32_BIT)
    {
        img = new Bmp32Bit(*this);
        img->writeToFile(path);
    }
    else if (type == BITMAP_8_BIT)
    {
        img = new Bmp8Bit(*this);
        img->writeToFile(path);
    }
    delete img;
}

void ImageFile::writeToFile(std::string path, ImageWriteType type)
{
    writeToFile(path.c_str(), type);
}