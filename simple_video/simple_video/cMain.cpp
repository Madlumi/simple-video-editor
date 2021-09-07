#include "cMain.h"
#include "EList.h"
wxBEGIN_EVENT_TABLE(cMain,wxFrame)
	EVT_BUTTON(10000, OnbtnClck)
	EVT_MENU(EList::MenuNew, MenuNew)
	EVT_MENU(EList::MenuOpen, MenuOpen)
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



	btn = new wxButton(this, 10000, ":)",wxPoint(30, 15), wxSize(75, 50));
	txt = new wxTextCtrl(this, wxID_ANY, "", wxPoint(15, 90), wxSize(150, 50));
	lst = new wxListBox(this, wxID_ANY, wxPoint(250, 15), wxSize(500, 200));
}

cMain::~cMain() {}
void cMain::OnbtnClck(wxCommandEvent& evt) {
	lst->AppendString(txt->GetValue());
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
}
