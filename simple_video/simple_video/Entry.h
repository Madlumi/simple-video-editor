#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>
#include "wxImagePanel.h"
#define MAXPATH  260

struct entry {
    int hold;
    char path[MAXPATH];
    wxButton* btn;
    wxImagePanel* img;

};

struct entry* entry_create(const char* str, wxWindow* tl, wxPanel* imgframe,int i);


class Entry {
};

