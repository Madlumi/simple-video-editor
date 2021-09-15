#include "Entry.h"

struct entry* entry_create(const char* str, wxWindow* parent, int i) {
	struct entry* e = (struct entry*) malloc(sizeof(struct entry));
	e->hold = 1;
	e->btn = new wxButton(parent, wxID_ANY,str, wxPoint(30*i, 15));
		//btn = new wxButton(this, 10000, ":)",wxPoint(30, 15), wxSize(75, 50));
	return e;
}