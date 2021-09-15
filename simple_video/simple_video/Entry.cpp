#include "Entry.h"

struct entry* entry_create(const char* str, wxWindow* tl, wxPanel* imgframe, int i) {
	struct entry* e = (struct entry*) malloc(sizeof(struct entry));
	e->hold = 1;
	e->btn = new wxButton(tl, wxID_ANY,str, wxPoint(30*i, 15));

	wxString path = wxGetCwd() + wxT("/pot.png");
	e->img = new wxImagePanel(imgframe, path, wxBITMAP_TYPE_PNG);
	imgframe->GetSizer()->Add(e->img, 1, wxEXPAND);
		//btn = new wxButton(this, 10000, ":)",wxPoint(30, 15), wxSize(75, 50));
	return e;
}