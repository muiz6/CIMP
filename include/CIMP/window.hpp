///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef WINDOW_H
#define WINDOW_H

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/clrpicker.h>
#include <wx/toolbar.h>
#include <wx/statbmp.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Window
///////////////////////////////////////////////////////////////////////////////
namespace cp
{
	class Window : public wxFrame
	{
	private:

	protected:
		wxMenuBar* menuBar;
		wxMenu* menuFile;
		wxMenu* menuFilters;
		wxMenu* menuImage;
		wxToolBar* m_toolBar3;
		wxToolBarToolBase* m_tool16;
		wxColourPickerCtrl* m_colourPicker4;
		wxStaticBitmap* m_bitmap3;

	public:

		Window( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("CIMP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 582,402 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Window();

	};

	///////////////////////////////////////////////////////////////////////////////
	/// Class SaveDialogue
	///////////////////////////////////////////////////////////////////////////////
	class SaveDialogue : public wxDialog
	{
	private:

	protected:
		wxStaticText* textPath;
		wxDirPickerCtrl* saveDir;
		wxStaticText* textFormat;
		wxChoice* choiceImgFormat;
		wxButton* btnSave;

	public:

		SaveDialogue( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Save As"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,200 ), long style = wxDEFAULT_DIALOG_STYLE );
		~SaveDialogue();

	};
}

#endif  // WINDOW_H