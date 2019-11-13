#include "CIMP/window.hpp"
#include "CIMP/cimp.hpp"
#include "CIMP/png.hpp"
#include <string.h>
#include <iostream>
#include <wx/filedlg.h>
using namespace cp;

// event table
BEGIN_EVENT_TABLE(Window, wxFrame)
	EVT_MENU(wxID_EXIT, onExit)
	EVT_MENU(0, newFile)
	EVT_MENU(1, openFile)
	EVT_MENU(2, invertColors)
	EVT_MENU(3, grayScale)
	EVT_MENU(4, alienate)
	EVT_MENU(5, vFlip)
	EVT_MENU(6, saveFile)
END_EVENT_TABLE()

Window::Window(const char *title, int width, int height)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
	// creating menu
	menuBar = new wxMenuBar;

	file = new wxMenu;
	filters = new wxMenu;
	imgMenu = new wxMenu;

	file->Append(0, "New");
	file->Append(1, "Open");
	file->Append(6, "Save As");
	file->Append(wxID_EXIT, "Exit");

	filters->Append(3, "Gray Scale");
	filters->Append(2, "Invert Colors");
	filters->Append(4, "Alienate");

	imgMenu->Append(5, "Flip Vertically");

	menuBar->Append(file, "File");
	menuBar->Append(filters, "Filters");
	menuBar->Append(imgMenu, "Image");
	this->SetMenuBar(menuBar);

	panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(wxColour(55, 55, 55));

	// creating tool bar
	// toolBar = new wxToolBar(panel, wxID_ANY);
	// toolBar->SetWindowStyleFlag(wxstretc);
	// toolBar->AddTool(wxID_ANY, "zoom In", wxBitmap("Data\\zoom-in.png", wxBITMAP_TYPE_PNG));
	// toolBar->AddTool(wxID_ANY, "zoom In", wxBitmap("Data\\zoom-out.png", wxBITMAP_TYPE_PNG));

	this->Centre();
}

Window::~Window() {}

void Window::newFile(wxCommandEvent &event)
{
	Bmp bmp(800, 600);
	wxImage img(800, 600, bmp.getPixelDataInt());
	canvas = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(img), wxPoint(10, 10), wxSize(800, 600));
}

void Window::openFile(wxCommandEvent &event)
{
	wxFileDialog *open = new wxFileDialog(this, "Open");
	open->SetWindowStyle(wxFD_FILE_MUST_EXIST);
	open->SetWildcard("All Files|*|Bitmap Files|*.bmp|PNG Files|*.png");
	if (open->ShowModal() == wxID_OK)
	{
		auto path = open->GetPath();
		ImageFile img((std::string) path, ANY_IMAGE);

		buffer = new wxImage(img.getWidth(), img.getHeight(), img.getRGB());
		canvasWidth = 800;
		float ratio = (float)canvasWidth / (float)img.getWidth();
		int height = ratio * img.getHeight();
		// buffer->Rescale(canvasWidth, height);
		wxImage displayImg = *buffer;
		displayImg.Rescale(canvasWidth, height);

		canvas = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(displayImg), wxPoint(10, 10), wxSize(canvasWidth, height));
	}
}

void Window::onExit(wxCommandEvent &event)
{
	this->Close(true);
}

void Window::invertColors(wxCommandEvent &event)
{
	unsigned char* pix = buffer->GetData();
	Filters fltr(pix, 24, buffer->GetWidth(), buffer->GetHeight());
	fltr.invert();

	buffer->SetData(fltr.getPixelDataInt());
	wxImage displayImg = *buffer;
	int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
	displayImg.Rescale(canvasWidth, height);

	wxBitmap rslt(displayImg, 24);
	canvas->SetBitmap(rslt);
}

void Window::alienate(wxCommandEvent &event)
{
	unsigned char* pix = buffer->GetData();
	Filters fltr(pix, 24, buffer->GetWidth(), buffer->GetHeight());
	fltr.alienate();

	buffer->SetData(fltr.getPixelDataInt());
	wxImage displayImg = *buffer;
	int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
	displayImg.Rescale(canvasWidth, height);

	wxBitmap rslt(displayImg, 24);
	canvas->SetBitmap(rslt);
}

void Window::grayScale(wxCommandEvent &event)
{
	unsigned char* pix = buffer->GetData();
	Filters fltr(pix, 24, buffer->GetWidth(), buffer->GetHeight());
	fltr.grayScale();

	buffer->SetData(fltr.getPixelDataInt());
	wxImage displayImg = *buffer;
	int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
	displayImg.Rescale(canvasWidth, height);

	wxBitmap rslt(displayImg, 24);
	canvas->SetBitmap(rslt);
}

void Window::vFlip(wxCommandEvent &event)
{
	unsigned char* pix = buffer->GetData();
	Filters fltr(pix, 24, buffer->GetWidth(), buffer->GetHeight());
	fltr.verticalFlip();

	buffer->SetData(fltr.getPixelDataInt());
	wxImage displayImg = *buffer;
	int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
	displayImg.Rescale(canvasWidth, height);

	wxBitmap rslt(displayImg, 24);
	canvas->SetBitmap(rslt);
}

void Window::saveFile(wxCommandEvent &event)
{
	wxFileDialog *save = new wxFileDialog(this);
	save->SetWindowStyle(wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	save->SetMessage("Save As");
	save->SetWildcard("24-bit Bitmap (*.bmp)|*.bmp|32-bit Bitmap (*.bmp)|*.bmp|8-bit Bitmap (*.bmp)|*.bmp|PNG (*.png)|*.png");
	save->SetFilename("untitled");
	if(save->ShowModal() == wxID_OK)
	{
		ImageFile img(buffer->GetData(), 24, buffer->GetWidth(), buffer->GetHeight());
		wxString path = save->GetPath();
		int choice = save->GetFilterIndex();
		if (choice == 0)
		{
			img.writeToFile(path, BITMAP_24_BIT);
		}
		else if (choice == 1)
		{
			img.writeToFile(path, BITMAP_32_BIT);
		}
		else if (choice == 2)
		{
			img.writeToFile(path, BITMAP_8_BIT);
		}
		else if (choice == 3)
		{
			img.writeToFile(path, PNG_24_BIT);
		}
	}
}