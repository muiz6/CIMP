#ifndef IMG_H
#define IMG_H

#include <cstdint>

namespace cp
{
    /// @brief class to contain minimal rgb and rgba image
    class Img
    {
    private:
        unsigned int height;
        unsigned int width;
        int colorDepth;
        uint8_t* pixelData;

    public:

        /// @param pixelDataInput: pointer to dynamic array of pixels
        /// @param colorDepth: color depth of image, allowed values are 24
        /// and 32 for 24bit and 32bit respectively. All other values will
        /// be ignored
        /// @param width: width of image in pixels
        /// @param height: height of image in pixels
        Img(uint8_t* pixelDataInput, int colorDepth, int width, int height);

        /// copy constructor
        Img(const Img &);

        /// destructor
        ~Img();

        /// @return size of image(pixels) in bytes
        /// same as length
        uint32_t size() const;

        /// @return color depth of the image in bits
        /// 24 means RGB image, 32 means RGBA image
        int getColorDepth();

        /// @return width of image in pixels
        int getWidth();

        /// @return height of image in pixels
        int getHeight();

        /// @return returns pointer to dynamic pixel data array
        uint8_t* getPixelDataInt();
    };
}

#endif // IMG_H