#include "Entry.h"
#include <wx/bitmap.h>
#include "cMain.h"
struct entry* entry_create(const char* str, wxWindow* tl, wxPanel* imgframe, int i) {
	struct entry* e = (struct entry*) malloc(sizeof(struct entry));
	e->hold = 1;
	int btnSize = 15;
	int btnH = 20;

	wxBitmap bitmap(btnSize, btnH, -1);// Create a memory device context
	wxMemoryDC dc; 
	// Select the bitmap into the DC 
	dc.SelectObject(bitmap); 
	// Set the background 
	dc.SetBackground(*wxLIGHT_GREY_BRUSH);
	// Color the bitmap white 
	std::vector<wxPoint> points;
	points.push_back(wxPoint(0, 0));
	points.push_back(wxPoint(0, btnH));
	dc.Clear(); 
	dc.SetBackground(*wxGREY_BRUSH);
	dc.DrawLines(points.size(), &points[0], 0, 0);
	// Select the bitmap out of the DC 
	dc.SelectObject(wxNullBitmap); 

	e->btn = new wxButton(tl, wxID_ANY,"",wxPoint(btnSize *i, 0), wxSize(btnSize, btnH), wxBORDER_NONE);
	e->btn->SetBitmap(bitmap);
	e->btn->SetBitmapMargins(-4,0);
	e->btn->SetBitmapPosition(wxLEFT);
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

camEntry* camEntry_create(int frame, double x, double y, double scale, double r, int type) {
	struct camEntry* e = (struct camEntry*) malloc(sizeof(struct camEntry));
	e->hold = frame;
	e->x = x;
	e->y = y;
	e->scale = scale;
	e->r = r;
	//wow so lazy
	e->type[0] = type;
	e->type[1] = type;
	e->type[2] = type;
	e->type[3] = type;
	return e;
}

wxWindow* GetTopParent(wxWindow* pWindow) {
	wxWindow* pWin = pWindow;
	while (true) {
		if (pWin->GetParent())
			pWin = pWin->GetParent();
		else
			break;
	}
	return pWin;
}
void btnClk(){
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
	img->GetParent()->Layout();
	//img->paintNow();//idk bout thois one mate
}

void entry::show() {
	//
	
	
	img->Show(true);
	
	btn->Enable(false);
}

void camEntry::update(entry* e) {
	e->img->p = wxPoint(x, y);
	e->img->s = scale;
}
