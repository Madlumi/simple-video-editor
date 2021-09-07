#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain,wxFrame)
	EVT_BUTTON(10001, OnbtnClck)
wxEND_EVENT_TABLE()

cMain::cMain() :wxFrame(nullptr, wxID_ANY, "name",wxPoint(0,0),wxSize(600,400)) {
	btn = new wxButton(this, 10001, ":)",wxPoint(30, 15), wxSize(75, 50));
	txt = new wxTextCtrl(this, wxID_ANY, "", wxPoint(15, 90), wxSize(150, 50));
	lst = new wxListBox(this, wxID_ANY, wxPoint(250, 15), wxSize(500, 200));
}

cMain::~cMain() {}
void cMain::OnbtnClck(wxCommandEvent& evt) {
	lst->AppendString(txt->GetValue());
	//OutputDebugStringA("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
	evt.Skip();
}