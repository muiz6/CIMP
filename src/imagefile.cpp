#include "CIMP/imagefile.hpp"
using namespace cp;

ImageFile::~ImageFile() {}

void ImageFile::writeToFile(std::string path)
{
    writeToFile(path.c_str());
}