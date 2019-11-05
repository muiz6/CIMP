#ifndef MAIN_H
#define MAIN_H

#include <wx/wx.h>

namespace cp
{
    class Main: public wxApp
    {
    private:

    public:
        virtual bool OnInit();
    };
}

#endif // MAIN_H