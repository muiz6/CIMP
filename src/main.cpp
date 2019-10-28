#include "CIMP/cimp.hpp"
#include <iostream>
using namespace std;

int main()
{
    cout << "HelloWorld!\n";

    cp::Bmp bmp("data\\tiger.bmp");
    uint8_t* pixels = bmp.getPixelDataInt();
    int width = bmp.getWidth();
    int height = bmp.getHeight();
    bmp.close();

    cp::Img img(pixels, 24, width, height);

    cp::Bmp newBmp(img);
    // cp::Bmp newBmp(pixels, 24, width, height);
    newBmp.writeToFile("data\\output.bmp");
    newBmp.close();

    delete[] pixels;

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