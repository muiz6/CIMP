#include "CIMP/cimp.hpp"
#include "CIMP/window.hpp"
#include "CIMP/main.hpp"
#include <iostream>
#include <string>
using namespace cp;


IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    Window *win = new Window("CIMP", 800, 600);
    win->Show(true);

    return true;
}
