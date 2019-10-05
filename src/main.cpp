#include "CIMP/cimp.hpp"
using namespace cp;

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    Window *window = new Window("CIMP");
    window->Show(true);

    return true;
}