#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>

#define MAXPATH  260

struct entry {
    int hold;
    char path[MAXPATH];
    wxButton* btn;
};

struct entry* entry_create(const char* str, wxWindow* parent,int i);


class Entry {
};

