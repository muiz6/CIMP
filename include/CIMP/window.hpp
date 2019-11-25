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

		// tool bar
		wxToolBar* toolBar;
		wxToolBarToolBase* toolZoomIn;
		wxToolBarToolBase* toolZoomOut;

		wxPanel* panel;

		int canvasWidth;
		wxImage* buffer;
		wxStaticBitmap* canvas;

	public:
		Window(const char* title, int width, int height);
		Window(const Window &) = delete;
		~Window();

		// event handler methods

		void newFile(wxCommandEvent &event);
		void onExit(wxCommandEvent &event);
		void openFile(wxCommandEvent &event);
		void invertColors(wxCommandEvent &event);
		void alienate(wxCommandEvent &event);
		void grayScale(wxCommandEvent &event);
		void vFlip(wxCommandEvent &event);
		void saveFile(wxCommandEvent &event);
		void red(wxCommandEvent &event);
		void green(wxCommandEvent &event);
		void blue(wxCommandEvent &event);
		void silly(wxCommandEvent &event);
		void sepia(wxCommandEvent &event);
		
		void zoomIn(wxCommandEvent &event);
		void zoomOut(wxCommandEvent &event);

		DECLARE_EVENT_TABLE()
	};
}

#endif  // WINDOW_H