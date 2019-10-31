#include "CIMP/cimp.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    cout << "HelloWorld!\n";

    cp::Bmp bmp("..\\sample\\bmp-24bit-2.bmp");
    cp::Img img = bmp.getImg24();

    cp::Filters fltr(img);
    fltr.alienate();
    cp::Img newImg = fltr.getImg24();

    cp::Bmp newBmp(newImg);
    newBmp.writeToFile("data\\output.bmp");
    newBmp.close();
    bmp.close();

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