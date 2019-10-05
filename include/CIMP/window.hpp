#ifndef WINDOW_H
#define WINDOW_H

#include <wx/wx.h>

namespace cp
{
    class Window: public wxFrame
    {
    private:
        wxMenuBar* menuBar;
        wxMenu* file;
        wxMenu* filters;

        void onQuit(wxCommandEvent& event);
        void menuInit();

    public:
        Window(const wxString& title = "Title", int width = 800, int height = 600);
        ~Window();

    };
}

#endif