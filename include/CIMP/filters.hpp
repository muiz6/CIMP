#ifndef FILTERS_H
#define FILTERS_H

#include "CIMP/img.hpp"

namespace cp
{
    /// @brief image object, that can have filters applied on it
    class Filters: public cp::Img
    {
    private:

    public:

        /// @param pixelDataInput: pointer to dynamic array of pixels
        /// @param colorDepth: color depth of image, allowed values are 24
        /// and 32 for 24bit and 32bit respectively. All other values will
        /// be ignored
        /// @param width: width of image in pixels
        /// @param height: height of image in pixels
        Filters(uint8_t* pixelDataInput, int colorDepth, int width, int height);

        /// @brief initialize cp::Filters with cp::Img object
        Filters(cp::Img &img);

        ~Filters();

        void grayScale();

        void invert();

        void alienate();

        void verticalFlip();
    };
}

#endif // FILTERS_H