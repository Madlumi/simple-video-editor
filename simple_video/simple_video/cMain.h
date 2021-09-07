#pragma once
#include "wx/wx.h"

class cMain :public wxFrame {

public:
    cMain();
    ~cMain();

public:
    wxButton* btn = nullptr;
    wxTextCtrl* txt = nullptr;
    wxListBox* lst = nullptr;
    
    void OnbtnClck(wxCommandEvent &evt);

    wxDECLARE_EVENT_TABLE();
};

