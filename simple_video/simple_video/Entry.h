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
struct camEntry {
    int hold;
    double x;
    double y;
    double scale;
    double r;
    int type;
};

struct entry* entry_create(const char* str, wxWindow* tl, wxPanel* imgframe,int i);

struct camEntry* camEntry_create(int frame, double x, double y, double scale, double r, int type);

//why class?
class Entry {
public:
    
    void clicked();
};

