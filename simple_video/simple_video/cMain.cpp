#include "cMain.h"
#include "EList.h"
#include "Entry.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10000, OnbtnClck)
EVT_MENU(EList::MenuNew, MenuNew)
EVT_MENU(EList::MenuOpen, MenuOpen)
EVT_MENU(EList::MenuExit, MenuExit)
EVT_MENU(EList::MenuImport, MenuImport)
EVT_MENU(EList::MenuExport, MenuExport)
EVT_BUTTON(EList::Nextf, BtnNextF)
EVT_BUTTON(EList::prevf, BtnPrevF)
EVT_BUTTON(EList::play, BtnPlay)


EVT_TIMER(EList::Timer, TimNextF)
wxEND_EVENT_TABLE()


cMain::cMain() :wxFrame(nullptr, wxID_ANY, "name",wxPoint(0,0),wxSize(1200,1000)) {
	assets = new assetMng();
	//top bar-------------------------------------
	this->SetMinSize(wxSize(500,400));
	menuBar = new wxMenuBar();
	this->SetMenuBar(menuBar);

	wxMenu* menuFile = new wxMenu;
	
	menuFile->Append(EList::MenuNew, "New");
	menuFile->Append(EList::MenuOpen, "Open");
	menuFile->Append(EList::MenuSave, "Save");
	menuFile->AppendSeparator(); 
	menuFile->Append(EList::MenuImport, "Import");
	menuFile->Append(EList::MenuExport, "Export");
	menuFile->AppendSeparator();
	menuFile->Append(EList::MenuExit, "Exit");

	
	menuBar->Append(menuFile, "File");
	//-----------------------------------------

	// make sure to call this first
	wxInitAllImageHandlers();
	//wxSplitterWindow* splitterBot = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

	wxSplitterWindow* splitterV = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	wxSplitterWindow* splitter = new wxSplitterWindow(splitterV, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	
	//wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
	topPanel = new wxPanel(splitter, wxID_ANY, wxPoint(500, 50), wxSize(50, 50));
	topPanel->SetBackgroundColour(wxColor(100,100,100));

	


	botPanel = new wxPanel(splitterV, wxID_ANY, wxPoint(500, 50), wxSize(50, 50));
	botPanel->SetBackgroundColour(wxColor(25, 0, 100));
	
	tlScroller = new wxScrolledWindow(botPanel, wxID_ANY, wxPoint(500, 50), wxSize(2000, 50), wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB, wxT("scrolledWindow"));
	tlScroller->SetBackgroundColour(wxColor(5, 2, 5));
	tlScroller->SetVirtualSize(wxSize(4000, 300));
	playPanel = new wxPanel(botPanel, wxID_ANY, wxPoint(500, 50), wxSize(50, 50));
	tlPanel = new wxPanel(tlScroller, wxID_ANY, wxPoint(500, 50), wxSize(50, 50));
	playPanel->SetBackgroundColour(wxColor(25, 25, 25));
	tlPanel->SetBackgroundColour(wxColor(25, 200, 50));

	tlScroller->SetScrollRate(7, 7);

	frame = new wxPanel(splitter, wxID_ANY,  wxPoint(50, 50), wxSize(300, 300));
	
	DisplayScroller = new wxScrolledWindow(frame, wxID_ANY, wxPoint(0, 0), wxSize(600, 600), wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB, wxT("scrolledWindow"));
	
	frame2 = new wxPanel(DisplayScroller, wxID_ANY, wxPoint(0, 0), wxSize(1920, 1080));
	//varius definers--------------------------------
	tim = new wxTimer(this, EList::Timer);
	nextf = new wxButton(playPanel, EList::Nextf, ">");
	play = new wxButton(playPanel, EList::play, ">>");
	prevf = new wxButton(playPanel, EList::prevf, "<");
	//nextf->Bind(wxEVT_BUTTON, &cMain::BtnNextF, this);
	//nextf->Bind(wxEVT_BUTTON, &Entry::clicked, this, -1, e->img);
	
	
	//temp drawpane thingie
	//path = wxGetCwd() + wxT("/pot.png");
	//drawPane = new wxImagePanel(frame, path, wxBITMAP_TYPE_PNG);

	//sizer balongas-----------------------------------------
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* botSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* tlScrSizer = new wxBoxSizer(wxVERTICAL);


	wxBoxSizer* playSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* tlSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
	//wxBoxSizer* sizer3stupidname = new wxBoxSizer(wxHORIZONTAL);

	playPanel->SetSizer(playSizer);
	tlScroller->SetSizer(tlScrSizer);
	tlPanel->SetSizer(tlSizer);
	botPanel->SetSizer(botSizer);
	//sizer->Add(drawPane, 1, wxEXPAND);
	frame->SetSizer(sizer);
	frame2->SetSizer(sizer2);
	//DisplayScroller->SetSizer(sizer3stupidname);
	
	DisplayScroller->SetVirtualSize(wxSize(1920, 1080));
	DisplayScroller->SetScrollRate(2, 2);

	//sizer2->Add(frame, 1, wxEXPAND | wxALL, 5);
	//sizer2->Add(topPanel, 1, wxEXPAND | wxALL, 5);
	//this->SetSizer(sizer2);

	//splitter balongas-----------------------------------------
	splitter->SetMinimumPaneSize(100);
	splitter->SetSashGravity(1);
	splitterV->SetSashGravity(1);
	splitter->SplitVertically(frame, topPanel);
	splitterV->SetMinimumPaneSize(100);
	splitterV->SplitHorizontally(splitter, botPanel);
	
	//splitter->SetSashPosition(128*3);
	//splitterV->SetSashPosition( 100);
	//sizer addition balongas-----------------------------------------
	//frame->GetSizer()->Add(drawPane, 1, wxEXPAND);


	botPanel->GetSizer()->Add(playPanel, 0, wxEXPAND);
	botPanel->GetSizer()->Add(tlScroller, 1, wxEXPAND);

	tlScroller->GetSizer()->Add(tlPanel, 0, wxEXPAND);
	frame->GetSizer()->Add(DisplayScroller, 1, wxEXPAND);

	playPanel->GetSizer()->Add(prevf, 0, wxEXPAND);
	playPanel->GetSizer()->Add(play, 0, wxEXPAND);
	playPanel->GetSizer()->Add(nextf, 0, wxEXPAND);


	splitter->SetSashPosition(128 * 3);
	//wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
	//panel2 = new wxPanel(this, wxID_ANY, wxPoint(550, 50), wxSize(300, 300));
	// then simply create like this
	//path = wxGetCwd() + wxT("/pot.png");
	//drawPane2 = new wxImagePanel(panel2, path, wxBITMAP_TYPE_PNG);
	//sizer2->Add(drawPane2, 1, wxEXPAND);
	//panel2->SetSizer(sizer2);
	//frame->Show();

	//btn = new wxButton(this, 10000, ":)",wxPoint(30, 15), wxSize(75, 50));
	//txt = new wxTextCtrl(this, wxID_ANY, "", wxPoint(15, 90), wxSize(150, 50));
	//lst = new wxListBox(this, wxID_ANY, wxPoint(250, 15), wxSize(500, 200));

	
}

cMain::~cMain() {}
void cMain::ZoomDisplay(double s) {
	int x; int y;
	DisplayScroller->GetVirtualSize(&x,&y);
	DisplayScroller->SetVirtualSize(x*s,y*s);
	frame2->SetSize(x*s, y*s);

	DisplayScroller->Layout();
}
void cMain::OnbtnClck(wxCommandEvent& evt) {
	//lst->AppendString(txt->GetValue());
	//OutputDebugStringA("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	evt.Skip();
}

void cMain::BtnNextF(wxCommandEvent& evt) {
	assets->nextFrame();
}

void cMain::BtnPrevF(wxCommandEvent& evt) {
	assets->prevFrame();
}

void cMain::BtnPlay(wxCommandEvent& evt) {
	if (!tim->IsRunning()) {
		tim->Start(83.3333  * .75);
	}else{
		tim->Stop();
	}

}
void cMain::TimNextF(wxTimerEvent& evt) {
	assets->nextFrame();
}

void cMain::MenuNew(wxCommandEvent& evt) {
}

void cMain::MenuOpen(wxCommandEvent& evt) {
}

void cMain::MenuSave(wxCommandEvent& evt) {
}

//TODO error handling it was litteraly in´the docs, why not include it?
void cMain::MenuImport(wxCommandEvent& evt) {
	wxDirDialog dirDial(this, "chose frame folder", "E:/ANIM"/*def path*/, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST, wxDefaultPosition, wxDefaultSize, "chose frame folder");
	dirDial.ShowModal();
	//dirDial.GetPath();


	
	assets->addFolder(dirDial.GetPath().ToStdString(),tlPanel, frame2);
	this->Layout();
	

		//std::cout << entry.path() << std::endl;
	ZoomDisplay(.1);
}

void cMain::MenuExport(wxCommandEvent& evt) {
	OutputDebugStringA("EXPORTINGGGGGGGGGGGGGGGGGGGGGGG");

	wxDirDialog dirDial(this, "chose output folder", "E:/ANIM"/*def path*/, 
						wxDD_DEFAULT_STYLE, 
						wxDefaultPosition, wxDefaultSize,
						"chose output folder"
	);
	dirDial.ShowModal();
	//dirDial.GetPath();
	assets->exportFolder(dirDial.GetPath().ToStdString());


}

void cMain::MenuExit(wxCommandEvent& evt) {
	Close();
	evt.Skip();
}
