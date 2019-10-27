#include "CIMP/cimp.hpp"
#include <iostream>
using namespace std;

int main()
{
    cout << "HelloWorld!\n";
    cin.get();

    cp::Bmp bmp("data\\pen.bmp");
    bmp.getImg24();

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