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
        
        /// @brief  filters prototype
        /// @param Filters: Filter type Class  that link with Filters.cpp
        

        /// @brief  GrayScale is the Black and White filter
        /// @param GrayScale: Add Red,Green,Blue Values in new variable 
        /// @param avg: A variable store RGB Values and divide by 3 
        /// store RGB Value in new Array FiltersPixels
        
        void grayScale();
        
        /// @brief  Invert is the X-Ray type  filter
        /// @param Invert:  Red,Green,Blue Values are minus with 255 
        /// negetive of all RGB Value and store in New Array FiltersPixel
        
        void invert();
        
        /// @brief  Alienate is the Swaping type  filter
        /// @param alienate: Red,Green,Blue are swap to each other  
        /// Swapping  RGB Value to each other and  store in New Array FiltersPixel
        
        void alienate();
        
        /// @brief  VerticalFlip function(pixelData Array convert into vertically)
        /// @param verticalFlip: vertically convert image in two loops 
        ///  RGB Value convert into vertically  and  store in New Array FiltersPixel
        
        void verticalFlip();
        
        /// @brief  Red is the Dark red and black type filter
        /// @param red: ignore Green and Blue values   
        
        void red();
        
        /// @brief  green is the Dark green and black type filter
        /// @param red: ignore red and Blue values
        
        void green();
        
        /// @brief  blue is the Dark blue and black type filter
        /// @param red: ignore Green and red values
        
        void blue();
        
        /// @brief  Silly function is the redish and bluish filetr
        /// @param silly: first loop convert the image into black and white  
        /// Black and white image are convert into redish color and store in new FiltersPixels Array
        
        void silly();
        
        /// @brief  painty function is the oily paint filetr
        /// @param silly: In RGB  give Hard coded Values  
        /// These values are store in new Array called FiletrPixel 
        void painty();
    };
}

#endif // FILTERS_H