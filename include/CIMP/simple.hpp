#ifndef SIMPLE_H
#define SIMPLE_H

#include <wx/wx.h>

namespace cp
{
    class Simple: public wxFrame
    {
    public:
        Simple(const wxString& title);
    };
}

#endif