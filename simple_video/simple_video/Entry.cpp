#include "Entry.h"

struct entry* entry_create(const char* str, wxWindow* parent) {
	struct entry* e = (struct entry*) malloc(sizeof(struct entry));
	e->hold = 1;
	e->btn = new wxButton(parent, wxID_ANY);
		//btn = new wxButton(this, 10000, ":)",wxPoint(30, 15), wxSize(75, 50));
	return e;
}