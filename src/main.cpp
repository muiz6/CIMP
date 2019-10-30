#include "CIMP/cimp.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    cout << "HelloWorld!\n";

    cp::Bmp bmp("..\\sample\\bmp-24bit-2.bmp");
    cp::Img img = bmp.getImg24();

    cp::Bmp newBmp(img);
    newBmp.writeToFile("data\\output.bmp");
    newBmp.close();
    bmp.close();

    // cp::Bmp bmp("..\\sample\\bmp-24bit-2.bmp");
    // uint8_t* pixels = bmp.getPixelDataInt();
    // int width = bmp.getWidth();
    // int height = bmp.getHeight();
    // bmp.close();

    // cp::Img img(pixels, 24, width, height);
    // cp::Img imgCpy = img;

    // cp::Bmp newBmp(imgCpy);
    // newBmp.writeToFile("data\\output.bmp");
    // newBmp.close();

    // delete[] pixels;

    cin.get();
    return 0;
}

// ********************************************
// wxWidgets boilerplate code, to be used later
// ********************************************

// IMPLEMENT_APP(Main)

// bool Main::OnInit()
// {
//     Window *window = new Window(NULL);
//     window->Show(true);

//     return true;
// }