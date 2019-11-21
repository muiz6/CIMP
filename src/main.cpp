#include "CIMP/cimp.hpp"
#include "CIMP/window.hpp"
#include "CIMP/main.hpp"
#include <wx/sysopt.h>
using namespace cp;

// mandatory wxWidgets boiler plate code
IMPLEMENT_APP(Main)

bool Main::OnInit()
{
    // for enabling png files for wxwidgets
    wxImage::AddHandler(new wxPNGHandler);
    wxSystemOptions::SetOption("msw.remap", 2);

    // creating gui object
    Window *win = new Window("CIMP", 800, 600);
    win->Show(true);

    return true;
}
