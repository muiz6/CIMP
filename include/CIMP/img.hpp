#ifndef IMG_H
#define IMG_H

#include <cstdint>

namespace cp
{
    /// @brief class to contain minimal rgb and rgba image
    class Img
    {
    private:

    protected:
        unsigned int width;
        unsigned int height;
        int colorDepth;
        uint8_t* pixelData = NULL;

        /// @brief does nothing
        Img();

    public:

        /// @brief initialize cp::Img with array of pixel data
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
        virtual ~Img();

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

        /// @return cp::img object 24bit i.e. RGB
        virtual cp::Img getImg24();

        /// @return cp::Img object of 32bit i.e. RGBA
        virtual cp::Img getImg32();

        /// @brief get pixel data in RGB array
        /// @return pointer to dynamic array of 24bit RGB pixel data
        virtual uint8_t* getRGB();

        /// @brief get alpha channel separately
        /// @return pointer to dynamic array of alpha channel
        /// only valid if colorDepth is 32bit
        virtual uint8_t* getAlpha();
    };
}

#endif // IMG_H