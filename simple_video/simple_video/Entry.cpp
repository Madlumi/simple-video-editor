#include "Entry.h"

struct entry* entry_create(const char* str, wxWindow* tl, wxPanel* imgframe, int i) {
	struct entry* e = (struct entry*) malloc(sizeof(struct entry));
	e->hold = 1;
	e->btn = new wxButton(tl, wxID_ANY,"-",wxPoint(7*i, 15), wxSize(7, 15));
	//tl->GetSizer()->Add(e->btn, 1, wxEXPAND);
	//wxString path = wxGetCwd() + wxT("/pot.png");
	wxString path = wxString::FromUTF8(str);
	OutputDebugString(L"" + (path)+"\n");
	
	e->img = new wxImagePanel(imgframe, path, wxBITMAP_TYPE_PNG);
	imgframe->GetSizer()->Add(e->img, 1, wxEXPAND);
		//btn = new wxButton(this, 10000, ":)",wxPoint(30, 15), wxSize(75, 50));
	
	imgframe->Layout();
	e->img->Hide();
	//e->btn->Bind(wxEVT_BUTTON, &Entry::clicked, &tl->GetParent, -1, e->img);
	return e;
}

/*
void hide(entry* e) {
	e->img->Show(false);
	e->btn->Enable(true);
}
void show(entry* e) {
	e->img->Show(true);
	e->btn->Enable(false);
}*/

void Entry::clicked(){
	OutputDebugString(L"dasasasasasasasasasasasasasasasasasasasas\n");
}

void entry::hide() {
	img->Show(false);
	btn->Enable(true);
}

void entry::show() {
	img->Show(true);
	btn->Enable(false);
}
