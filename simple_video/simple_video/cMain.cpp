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

EVT_BUTTON(EList::zoomin, Zoomin)
EVT_BUTTON(EList::zoomout, Zoomout)

EVT_SCROLLWIN(onTlScroll)

EVT_TIMER(EList::Timer, TimNextF)

EVT_TOGGLEBUTTON(EList::showx, ShowX)
EVT_TOGGLEBUTTON(EList::showy, ShowY)
EVT_TOGGLEBUTTON(EList::shows, ShowS)
EVT_TOGGLEBUTTON(EList::showr, ShowR)


wxEND_EVENT_TABLE()


void cMain::initPanels() {
	
	botPanel->SetBackgroundColour(wxColor(25, 0, 100));
	playPanel = new wxPanel(botPanel, wxID_ANY, wxPoint(500, 50), wxSize(50, 50));
	playPanel->SetBackgroundColour(wxColor(25, 25, 25));
	
	DisplayScroller = new wxScrolledWindow(frame, wxID_ANY, wxPoint(0, 0), wxSize(600, 600), wxHSCROLL | wxVSCROLL | wxALWAYS_SHOW_SB, wxT("scrolledWindow"));
	TimelineScroller = new wxScrolledWindow(botPanel, wxID_ANY, wxPoint(0, 0), wxSize(100, 21), wxHSCROLL, wxT("scrolledWindow"));
	TimelinePointScroller = new wxScrolledWindow(botPanel, EList::TlpScroll, wxPoint(0, 0), wxSize(20, 20), wxVSCROLL, wxT("scrolledWindow"));
	DisplayScroller->SetBackgroundColour(wxColor(200, 200, 200));
	TimelineScroller->SetBackgroundColour(wxColor(130, 130, 130));
	TimelinePointScroller->SetBackgroundColour(wxColor(25, 25, 25));
	frame2 = new wxPanel(DisplayScroller, wxID_ANY, wxPoint(0, 0), wxSize(1920, 1080));
	tlpframe = new wxPanel(TimelinePointScroller, wxID_ANY, wxPoint(0, 0), wxSize(500, 500));
	tlpframe->SetBackgroundColour(wxColor(250, 250, 250));
}
cMain::cMain() :wxFrame(nullptr, wxID_ANY, "name",wxPoint(0,0),wxSize(1200,1000)) {
	SetFont(wxFont(
		20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
						wxFONTWEIGHT_BOLD, true));

	assets = new assetMng();
	this->SetMinSize(wxSize(500,400));
	menuBar = initmenu();
	this->SetMenuBar(menuBar);
	
	wxInitAllImageHandlers();



	wxSplitterWindow* splitterV = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	botPanel = new wxPanel(splitterV, wxID_ANY, wxPoint(500, 50), wxSize(50, 50));
	frame = new wxPanel(splitterV, wxID_ANY, wxPoint(50, 50), wxSize(300, 300));
	initPanels();
	initControlls(playPanel);
	//tlPanel = new wxPanel(TimelineScroller, wxID_ANY, wxPoint(500, 50), wxSize(50, 50));
	//tlPanel->SetBackgroundColour(wxColor(25, 200, 50));


	PointDrawPanle = new TlSlider(tlpframe);
	
	//varius definers--------------------------------
	tim = new wxTimer(this, EList::Timer);
	

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
	wxBoxSizer* tlpSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
	//wxBoxSizer* sizer3stupidname = new wxBoxSizer(wxHORIZONTAL);
	
	playPanel->SetSizer(playSizer);
	//TimelineScroller->SetSizer(tlScrSizer);
	//tlPanel->SetSizer(tlSizer);
	botPanel->SetSizer(botSizer);
	//sizer->Add(drawPane, 1, wxEXPAND);
	frame->SetSizer(sizer);
	frame2->SetSizer(sizer2);
	//DisplayScroller->SetSizer(sizer3stupidname);
	


	DisplayScroller->SetVirtualSize(wxSize(1920, 1080));
	DisplayScroller->SetScrollRate(4, 4);
	TimelineScroller->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
	TimelineScroller->SetVirtualSize(wxSize(1920, 20));
	TimelineScroller->SetScrollRate(4, 4);
	TimelinePointScroller->SetVirtualSize(wxSize(1920, 1080));
	TimelinePointScroller->SetScrollRate(4, 4);

	//sizer2->Add(frame, 1, wxEXPAND | wxALL, 5);
	//sizer2->Add(topPanel, 1, wxEXPAND | wxALL, 5);
	//this->SetSizer(sizer2);

	//splitter balongas-----------------------------------------
	//splitter->SetMinimumPaneSize(100);
	//splitter->SetSashGravity(1);
	splitterV->SetSashGravity(1);
	//splitter->SplitVertically(frame, topPanel);
	splitterV->SetMinimumPaneSize(100);
	splitterV->SplitHorizontally(frame, botPanel);
	
	//splitter->SetSashPosition(128*3);
	//splitterV->SetSashPosition( 100);
	//sizer addition balongas-----------------------------------------
	//frame->GetSizer()->Add(drawPane, 1, wxEXPAND);
	

	botPanel->GetSizer()->Add(playPanel, 0, wxEXPAND);
	botPanel->GetSizer()->Add(TimelineScroller, 0, wxEXPAND);
	botPanel->GetSizer()->Add(TimelinePointScroller, 1, wxEXPAND);
	//TimelineScroller->GetSizer()->Add(tlPanel, 0, wxEXPAND);
	frame->GetSizer()->Add(DisplayScroller, 1, wxEXPAND);

	playPanel->GetSizer()->Add(prevf, 0, wxEXPAND);
	playPanel->GetSizer()->Add(play, 10, wxEXPAND);
	playPanel->GetSizer()->Add(nextf, 0, wxEXPAND);
	playPanel->GetSizer()->AddStretchSpacer(10);
	playPanel->GetSizer()->Add(zoomin, 0, wxEXPAND);
	playPanel->GetSizer()->Add(zoomout, 0, wxEXPAND);
	playPanel->GetSizer()->AddStretchSpacer(10);
	playPanel->GetSizer()->Add(showx, 0, wxEXPAND);
	playPanel->GetSizer()->Add(showy, 0, wxEXPAND);
	playPanel->GetSizer()->Add(shows, 0, wxEXPAND);
	playPanel->GetSizer()->Add(showr, 0, wxEXPAND);
	playPanel->GetSizer()->AddStretchSpacer(1);
	playPanel->GetSizer()->Add(interpTypeBox, 50, wxEXPAND);
	playPanel->GetSizer()->AddStretchSpacer(50);

	tlpframe->SetSizer(tlpSizer);
	tlpSizer->Add(PointDrawPanle, 1, wxEXPAND);

	//splitter->SetSashPosition(128 * 3);
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

void cMain::initControlls(wxPanel* parent) {
	nextf = new wxButton(parent, EList::Nextf, "->");
	play = new wxButton(parent, EList::play, ">");
	prevf = new wxButton(parent, EList::prevf, "<-");

	zoomin = new wxButton(parent, EList::zoomin, "+");
	zoomout = new wxButton(parent, EList::zoomout, "-");

	showx = new wxToggleButton(parent, EList::showx, "X");
	showy = new wxToggleButton(parent, EList::showy, "Y");
	shows = new wxToggleButton(parent, EList::shows, "S");
	showr = new wxToggleButton(parent, EList::showr, "R");

	showx->SetValue(1);
	showy->SetValue(1);
	shows->SetValue(1);
	showr->SetValue(1);
	const wxString choices[4] = { wxT("None"),wxT("Hard"),wxT("Linear"),wxT("Smooth") };
	interpTypeBox = new wxComboBox(playPanel, EList::interpTypeBox, "Linear", wxDefaultPosition, wxDefaultSize, 4,
								   choices, wxCB_READONLY,
								   wxDefaultValidator, wxT("InterTypeBox"));
}


void cMain::ZoomDisplay(double s) {
	int x; int y;
	DisplayScroller->GetVirtualSize(&x,&y);
	DisplayScroller->SetVirtualSize(x*s,y*s);
	frame2->SetSize(x*s, y*s);

	DisplayScroller->Layout();
}
void cMain::onTlScroll(wxScrollWinEvent& event) {
	exit(NULL);
	OutputDebugStringA("scrolllllllllllllllllllllllllllllllllllllllllllllllllll");
	TimelineScroller->Scroll(10,0);
	event.Skip();
}

void cMain::ShowX(wxCommandEvent& evt) {
	PointDrawPanle->show_point[EList::xp]= evt.IsChecked();
	PointDrawPanle->paintNow();
}
void cMain::ShowY(wxCommandEvent& evt) {
	PointDrawPanle->show_point[EList::yp] = evt.IsChecked();
	PointDrawPanle->paintNow();
}
void cMain::ShowS(wxCommandEvent& evt) {
	PointDrawPanle->show_point[EList::sp] = evt.IsChecked();
	PointDrawPanle->paintNow();
}
void cMain::ShowR(wxCommandEvent& evt) {
	PointDrawPanle->show_point[EList::rp] = evt.IsChecked();
	PointDrawPanle->paintNow();

}

void cMain::OnbtnClck(wxCommandEvent& evt) {
	//lst->AppendString(txt->GetValue());
	//OutputDebugStringA("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	evt.Skip();
}

void cMain::BtnNextF(wxCommandEvent& evt) {
	
	assets->nextFrame();
}

void cMain::Zoomout(wxCommandEvent& evt) {
	ZoomDisplay(.9);
}

void cMain::Zoomin(wxCommandEvent& evt) {
	ZoomDisplay(1.1);
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


	


	assets->addFolder(dirDial.GetPath().ToStdString(), TimelineScroller, frame2);
	PointDrawPanle->initTl(assets->tl);
	this->Layout();
	

		//std::cout << entry.path() << std::endl;
	ZoomDisplay(.9);
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
wxMenuBar* cMain::initmenu() {
	wxMenuBar* mb = new wxMenuBar();

	wxMenu* menuFile = new wxMenu;
	menuFile->Append(EList::MenuNew, "New");
	menuFile->Append(EList::MenuOpen, "Open");
	menuFile->Append(EList::MenuSave, "Save");
	menuFile->AppendSeparator();
	menuFile->Append(EList::MenuImport, "Import");
	menuFile->Append(EList::MenuExport, "Export");
	menuFile->AppendSeparator();
	menuFile->Append(EList::MenuExit, "Exit");

	mb->Append(menuFile, "File");

	return mb;
}
void cMain::MenuExit(wxCommandEvent& evt) {
	Close();
	evt.Skip();
}
