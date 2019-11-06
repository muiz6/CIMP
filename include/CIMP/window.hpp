#ifndef WINDOW_H
#define WINDOW_H

#include <wx/wx.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>

namespace cp
{
	/// @brief main application window
	class Window : public wxFrame
	{
		// menu bar
		wxMenuBar* menuBar;

		wxMenu* file;
		wxMenu* filters;
		wxMenu* imgMenu;

		wxPanel* panel;

		int canvasWidth;
		wxImage* buffer;
		wxStaticBitmap* canvas;

	public:
		Window(const char* title, int width, int height);
		~Window();

		void newFile(wxCommandEvent &event);
		void onExit(wxCommandEvent &event);
		void openFile(wxCommandEvent &event);
		void invertColors(wxCommandEvent &event);
		void alienate(wxCommandEvent &event);
		void grayScale(wxCommandEvent &event);
		void vFlip(wxCommandEvent &event);
		void saveFile(wxCommandEvent &event);

		DECLARE_EVENT_TABLE()
	};
}

#endif  // WINDOW_H