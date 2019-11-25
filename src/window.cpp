#include "CIMP/window.hpp"
#include "CIMP/cimp.hpp"
#include <string.h>
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
	EVT_MENU(9, blue)
	EVT_MENU(10, silly)
	EVT_MENU(11, painty)
	EVT_MENU(12, red)
	EVT_MENU(13, green)
	EVT_MENU(6, saveFile)
	EVT_TOOL(7, zoomOut)
	EVT_TOOL(8, zoomIn)
END_EVENT_TABLE()

Window::Window(const char *title, int width, int height)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
	this->SetIcon(wxIcon("data\\icon.png", wxBITMAP_TYPE_PNG));

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
	filters->Append(12, "Red");
	filters->Append(13 , "Green");
	filters->Append(9, "Blue");
	filters->Append(10, "silly");
	filters->Append(11, "painty");

	imgMenu->Append(5, "Flip Vertically");

	menuBar->Append(file, "File");
	menuBar->Append(filters, "Filters");
	menuBar->Append(imgMenu, "Image");
	this->SetMenuBar(menuBar);

	// setting up tool bar
	toolBar = this->CreateToolBar(wxTB_HORIZONTAL | wxTB_FLAT, wxID_ANY);
	toolBar->SetBackgroundColour(wxColour(40, 40, 40));
	toolZoomIn = toolBar->AddTool(8, "zoom-in", wxBitmap("data\\zoom-in.png", wxBITMAP_TYPE_PNG));
	toolZoomOut = toolBar->AddTool(7, "zoom-out", wxBitmap("data\\zoom-out.png", wxBITMAP_TYPE_PNG));
	toolBar->Realize();

	panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(wxColour(55, 55, 55));

	// initialize blank canvas
	int imgHeight = 600;
	canvas = new wxStaticBitmap(panel, wxID_ANY, wxNullBitmap, wxPoint(10, 10), wxSize(canvasWidth, imgHeight));

	this->Centre();
}

Window::~Window() {}

void Window::newFile(wxCommandEvent &event)
{
	Bmp bmp(800, 600);
	buffer = new wxImage(bmp.getWidth(), bmp.getHeight(), bmp.getRGB());

	wxImage img = *buffer;
	canvasWidth = 800;
	float ratio = (float)canvasWidth / (float)bmp.getWidth();
	int height = ratio * bmp.getHeight();
	img.Rescale(canvasWidth, height);

	canvas->SetBitmap(img);
}

void Window::openFile(wxCommandEvent &event)
{
	wxFileDialog *open = new wxFileDialog(this, "Open");
	open->SetWindowStyle(wxFD_FILE_MUST_EXIST);
	open->SetWildcard("Bitmap Files|*.bmp");
	if (open->ShowModal() == wxID_OK)
	{
		auto path = open->GetPath();
		ImageFile img((std::string) path, ANY_IMAGE);

		buffer = new wxImage(img.getWidth(), img.getHeight(), img.getRGB());
		canvasWidth = 800;
		float ratio = (float)canvasWidth / (float)img.getWidth();
		int height = ratio * img.getHeight();
		wxImage displayImg = *buffer;
		displayImg.Rescale(canvasWidth, height);

		panel->ClearBackground();
		canvas->SetBitmap(wxBitmap(displayImg));
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

void Window::green(wxCommandEvent &event)
{
	unsigned char* pix = buffer->GetData();
	Filters fltr(pix, 24, buffer->GetWidth(), buffer->GetHeight());
	fltr.green();

	buffer->SetData(fltr.getPixelDataInt());
	wxImage displayImg = *buffer;
	int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
	displayImg.Rescale(canvasWidth, height);

	wxBitmap rslt(displayImg, 24);
	canvas->SetBitmap(rslt);
}

void Window::blue(wxCommandEvent &event)
{
	unsigned char* pix = buffer->GetData();
	Filters fltr(pix, 24, buffer->GetWidth(), buffer->GetHeight());
	fltr.blue();

	buffer->SetData(fltr.getPixelDataInt());
	wxImage displayImg = *buffer;
	int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
	displayImg.Rescale(canvasWidth, height);

	wxBitmap rslt(displayImg, 24);
	canvas->SetBitmap(rslt);
}

void Window::silly(wxCommandEvent &event)
{
	unsigned char* pix = buffer->GetData();
	Filters fltr(pix, 24, buffer->GetWidth(), buffer->GetHeight());
	fltr.silly();

	buffer->SetData(fltr.getPixelDataInt());
	wxImage displayImg = *buffer;
	int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
	displayImg.Rescale(canvasWidth, height);

	wxBitmap rslt(displayImg, 24);
	canvas->SetBitmap(rslt);
}

void Window::painty(wxCommandEvent &event)
{
	unsigned char* pix = buffer->GetData();
	Filters fltr(pix, 24, buffer->GetWidth(), buffer->GetHeight());
	fltr.painty();

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
	save->SetWildcard("24-bit Bitmap (*.bmp)|*.bmp|32-bit Bitmap (*.bmp)|*.bmp|8-bit Bitmap (*.bmp)|*.bmp|16-bit Bitmap (*.bmp)|*.bmp");
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
			img.writeToFile(path, BITMAP_16_BIT);
		}
		else if (choice == 4)
		{
			img.writeToFile(path, PNG_24_BIT);
		}
	}
}

void Window::red(wxCommandEvent &event)
{
	unsigned char* pix = buffer->GetData();
	Filters fltr(pix, 24, buffer->GetWidth(), buffer->GetHeight());
	fltr.red();

	buffer->SetData(fltr.getPixelDataInt());
	wxImage displayImg = *buffer;
	int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
	displayImg.Rescale(canvasWidth, height);

	wxBitmap rslt(displayImg, 24);
	canvas->SetBitmap(rslt);
void Window::zoomIn(wxCommandEvent &event)
{
	if (canvasWidth < 1600)
	{
		canvasWidth += 50;

		wxImage displayImg = *buffer;
		int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
		displayImg.Rescale(canvasWidth, height);

		wxBitmap rslt(displayImg, 24);
		canvas->SetBitmap(rslt);
	}
}

void Window::zoomOut(wxCommandEvent &event)
{
	if (canvasWidth > 300)
	{
		canvasWidth -= 50;

		wxImage displayImg = *buffer;
		int height = (float)canvasWidth / (float)buffer->GetWidth() * buffer->GetHeight();
		displayImg.Rescale(canvasWidth, height);

		wxBitmap rslt(displayImg, 24);
		// panel->ClearBackground();
		canvas->SetBitmap(rslt);
		panel->ClearBackground();
	}
}