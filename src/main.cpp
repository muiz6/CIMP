#include "CIMP/cimp.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    cout << "HelloWorld!\n";

    string name;
    cout << "Enter file name : ";
    cin >> name;
    string path = "..\\sample\\" + name;

    cp::Bmp bmp(path);
    cp::Img img = bmp.getImg32();

    cp::Filters fltr(img);
    // fltr.verticalFlip();
    // fltr.invert();
    fltr.alienate();
    cp::Img newImg = fltr.getImg24();

    cp::Bmp newBmp(img);
    newBmp.write24BitBmp("data\\output.bmp");

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