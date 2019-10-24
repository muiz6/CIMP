///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CIMP/window.hpp"
using namespace cp;

///////////////////////////////////////////////////////////////////////////
Window::Window( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	this->SetBackgroundColour( wxColour( 43, 47, 55 ) );

	menuBar = new wxMenuBar( 0 );
	menuBar->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	menuBar->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	menuFile = new wxMenu();
	wxMenuItem* mItemNew;
	mItemNew = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("New") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( mItemNew );

	wxMenuItem* mItemOpen;
	mItemOpen = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Open") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( mItemOpen );

	wxMenuItem* mItemSave;
	mItemSave = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Save") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( mItemSave );

	wxMenuItem* mItemSaveAs;
	mItemSaveAs = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Save As") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( mItemSaveAs );

	wxMenuItem* mItemExit;
	mItemExit = new wxMenuItem( menuFile, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	menuFile->Append( mItemExit );

	menuBar->Append( menuFile, wxT("File") );

	menuFilters = new wxMenu();
	wxMenuItem* filterInvert;
	filterInvert = new wxMenuItem( menuFilters, wxID_ANY, wxString( wxT("Invert Colors") ) , wxEmptyString, wxITEM_NORMAL );
	menuFilters->Append( filterInvert );

	wxMenuItem* filterGrey;
	filterGrey = new wxMenuItem( menuFilters, wxID_ANY, wxString( wxT("Grey Scale") ) , wxEmptyString, wxITEM_NORMAL );
	menuFilters->Append( filterGrey );

	wxMenuItem* filterSepia;
	filterSepia = new wxMenuItem( menuFilters, wxID_ANY, wxString( wxT("Sepia") ) , wxEmptyString, wxITEM_NORMAL );
	menuFilters->Append( filterSepia );

	menuBar->Append( menuFilters, wxT("Filters") );

	menuImage = new wxMenu();
	wxMenuItem* imgResize;
	imgResize = new wxMenuItem( menuImage, wxID_ANY, wxString( wxT("Resize") ) , wxEmptyString, wxITEM_NORMAL );
	menuImage->Append( imgResize );

	wxMenuItem* imgFlipV;
	imgFlipV = new wxMenuItem( menuImage, wxID_ANY, wxString( wxT("Flip Vertically") ) , wxEmptyString, wxITEM_NORMAL );
	menuImage->Append( imgFlipV );

	wxMenuItem* imgFlipH;
	imgFlipH = new wxMenuItem( menuImage, wxID_ANY, wxString( wxT("Flip Horizontally") ) , wxEmptyString, wxITEM_NORMAL );
	menuImage->Append( imgFlipH );

	wxMenuItem* imgRotateCW;
	imgRotateCW = new wxMenuItem( menuImage, wxID_ANY, wxString( wxT("Rotate Clockwise") ) , wxEmptyString, wxITEM_NORMAL );
	menuImage->Append( imgRotateCW );

	wxMenuItem* imgRotateACW;
	imgRotateACW = new wxMenuItem( menuImage, wxID_ANY, wxString( wxT("Rotate Anticlockwise") ) , wxEmptyString, wxITEM_NORMAL );
	menuImage->Append( imgRotateACW );

	menuBar->Append( menuImage, wxT("Image") );

	this->SetMenuBar( menuBar );

	m_toolBar3 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	m_tool16 = m_toolBar3->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("data/pen.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_colourPicker4 = new wxColourPickerCtrl( m_toolBar3, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	m_toolBar3->AddControl( m_colourPicker4 );
	m_toolBar3->Realize();

	wxBoxSizer* boxSizer;
	boxSizer = new wxBoxSizer( wxVERTICAL );

	m_bitmap3 = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("data/test.bmp"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	boxSizer->Add( m_bitmap3, 0, wxALL, 5 );


	this->SetSizer( boxSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

Window::~Window()
{
}

SaveDialogue::SaveDialogue( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );

	wxBoxSizer* boxSizer;
	boxSizer = new wxBoxSizer( wxVERTICAL );

	textPath = new wxStaticText( this, wxID_ANY, wxT("Path:"), wxDefaultPosition, wxDefaultSize, 0 );
	textPath->Wrap( -1 );
	boxSizer->Add( textPath, 0, wxALL, 5 );

	saveDir = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	boxSizer->Add( saveDir, 0, wxALL|wxEXPAND, 5 );

	textFormat = new wxStaticText( this, wxID_ANY, wxT("Format:"), wxDefaultPosition, wxDefaultSize, 0 );
	textFormat->Wrap( -1 );
	boxSizer->Add( textFormat, 0, wxALL, 5 );

	wxString choiceImgFormatChoices[] = { wxT("BMP 8-bit"), wxT("BMP 24-bit"), wxT("BMP 32-bit") };
	int choiceImgFormatNChoices = sizeof( choiceImgFormatChoices ) / sizeof( wxString );
	choiceImgFormat = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceImgFormatNChoices, choiceImgFormatChoices, 0 );
	choiceImgFormat->SetSelection( 0 );
	boxSizer->Add( choiceImgFormat, 0, wxALL|wxEXPAND, 5 );

	btnSave = new wxButton( this, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	boxSizer->Add( btnSave, 0, wxALL, 5 );


	this->SetSizer( boxSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

SaveDialogue::~SaveDialogue()
{
}