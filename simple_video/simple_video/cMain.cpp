#include "cMain.h"
#include "EList.h"

wxBEGIN_EVENT_TABLE(cMain,wxFrame)
	EVT_BUTTON(10000, OnbtnClck)
	EVT_MENU(EList::MenuNew, MenuNew)
	EVT_MENU(EList::MenuOpen, MenuOpen)
	EVT_MENU(EList::MenuExit, MenuExit)
wxEND_EVENT_TABLE()

cMain::cMain() :wxFrame(nullptr, wxID_ANY, "name",wxPoint(0,0),wxSize(600,400)) {
	//top bar-------------------------------------
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

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	frame = new wxPanel(this, wxID_ANY,  wxPoint(50, 50), wxSize(300, 300));

	// then simply create like this

	path = wxGetCwd() + wxT("/pot.png");
	drawPane = new wxImagePanel(frame, path, wxBITMAP_TYPE_PNG);
	sizer->Add(drawPane, 1, wxEXPAND);
	frame->SetSizer(sizer);

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

void cMain::MenuImport(wxCommandEvent& evt) {
}

void cMain::MenuExport(wxCommandEvent& evt) {
}

void cMain::MenuExit(wxCommandEvent& evt) {
	Close();
	evt.Skip();
}
