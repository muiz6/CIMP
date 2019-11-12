#include "CIMP/imagefileinterface.hpp"
using namespace cp;

ImageFileInterface::~ImageFileInterface() {}

void ImageFileInterface::writeToFile(std::string path)
{
    writeToFile(path.c_str());
}