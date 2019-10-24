#ifndef MAIN_H
#define MAIN_H

#include <wx/wx.h>

namespace cp
{
    class Main : public wxApp
    {
    public:
        /// @brief main method to launch a wx application
        virtual bool OnInit();
    };
}

#endif // MAIN_H