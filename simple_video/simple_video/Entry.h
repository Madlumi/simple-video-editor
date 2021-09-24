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
    void hide();
    void show();

};

struct entry* entry_create(const char* str, wxWindow* tl, wxPanel* imgframe,int i);

//why class?
class Entry {
public:
    
    void clicked();
};

