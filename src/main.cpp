#include "CIMP/cimp.hpp"
using namespace cp;

IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    Window *window = new Window(NULL);
    window->Show(true);

    return true;
}