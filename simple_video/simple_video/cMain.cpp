#include "cMain.h"
#include "EList.h"


wxBEGIN_EVENT_TABLE(cMain,wxFrame)
	EVT_BUTTON(10000, OnbtnClck)
	EVT_MENU(EList::MenuNew, MenuNew)
	EVT_MENU(EList::MenuOpen, MenuOpen)
	EVT_MENU(EList::MenuExit, MenuExit)
	EVT_MENU(EList::MenuImport, MenuImport)
wxEND_EVENT_TABLE()

cMain::cMain() :wxFrame(nullptr, wxID_ANY, "name",wxPoint(0,0),wxSize(600,400)) {
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
	wxSplitterWindow* splitterV = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	wxSplitterWindow* splitter = new wxSplitterWindow(splitterV, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	
	//wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
	topPanel = new wxPanel(splitter, wxID_ANY, wxPoint(500, 50), wxSize(50, 50));
	topPanel->SetBackgroundColour(wxColor(100,0,100));

	botPanel = new wxPanel(splitterV, wxID_ANY, wxPoint(500, 50), wxSize(50, 50));
	botPanel->SetBackgroundColour(wxColor(25, 0, 100));

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	frame = new wxPanel(splitter, wxID_ANY,  wxPoint(50, 50), wxSize(300, 300));
	// then simply create like this
	path = wxGetCwd() + wxT("/pot.png");
	drawPane = new wxImagePanel(frame, path, wxBITMAP_TYPE_PNG);

	sizer->Add(drawPane, 1, wxEXPAND);
	frame->SetSizer(sizer);
	//sizer2->Add(frame, 1, wxEXPAND | wxALL, 5);
	//sizer2->Add(topPanel, 1, wxEXPAND | wxALL, 5);
	//this->SetSizer(sizer2);
	splitter->SetMinimumPaneSize(200);
	splitter->SetSashGravity(1);
	splitterV->SetSashGravity(1);
	splitter->SplitVertically(frame, topPanel);
	splitterV->SetMinimumPaneSize(100);
	splitterV->SplitHorizontally(splitter, botPanel);

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
void cMain::OnbtnClck(wxCommandEvent& evt) {
	//lst->AppendString(txt->GetValue());
	//OutputDebugStringA("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	evt.Skip();
}

void cMain::MenuNew(wxCommandEvent& evt) {
}

void cMain::MenuOpen(wxCommandEvent& evt) {
}

void cMain::MenuSave(wxCommandEvent& evt) {
}

//TODO error handling
void cMain::MenuImport(wxCommandEvent& evt) {
	wxDirDialog dirDial(this, "chose frame folder", "c:/"/*def path*/, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST, wxDefaultPosition, wxDefaultSize, "chose frame folder");
	dirDial.ShowModal();
	//dirDial.GetPath();




	std::string path = dirDial.GetPath().ToStdString();
	for (const auto& entry : std::filesystem::directory_iterator(path)) {

		std::string sss{ entry.path().u8string() + "\n"};
		char const* ppchar = sss.c_str();  //use char const* as target type
		OutputDebugStringA(ppchar);
	}
		//std::cout << entry.path() << std::endl;
}

void cMain::MenuExport(wxCommandEvent& evt) {
}

void cMain::MenuExit(wxCommandEvent& evt) {
	Close();
	evt.Skip();
}
