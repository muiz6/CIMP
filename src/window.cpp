#include "CIMP/window.hpp"
using namespace cp;

Window::Window(const wxString& title, int width, int height)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    // set background color of window
    SetBackgroundColour(wxColour(43, 50, 54));
    menuInit();

    // Centres the window on screen

    Centre();
}

void Window::onQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void Window::menuInit()
{
    // create menu bar
    menuBar = new wxMenuBar;

    // create menu
    file = new wxMenu;
    filters = new wxMenu;

    // attach items to menu
    file->Append(wxID_OPEN, "New");
    file->Append(wxID_OPEN, "Open");
    file->Append(wxID_EXIT, "Quit");

    filters->Append(wxID_OPEN, "Invert");
    filters->Append(wxID_OPEN, "Grayscale");
    filters->Append(wxID_OPEN, "Sepia");
    filters->Append(wxID_OPEN, "Blur");
    filters->Append(wxID_OPEN, "Sharpen");

    // attach menu to menubar
    menuBar->Append(file, "File");
    menuBar->Append(filters, "Filters");

    SetMenuBar(menuBar);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Window::onQuit));
}

Window::~Window()
{
    // delete menuBar;
    // delete file;
    // delete filters;
}