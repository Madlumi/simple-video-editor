#pragma once
#include "wx/wx.h"
#include "imgFrame.h"
#include "wxImagePanel.h"

class cMain :public wxFrame {

public:
    cMain();
    ~cMain();

public:
    //wxButton* btn = nullptr;
    //wxTextCtrl* txt = nullptr;
    //wxListBox* lst = nullptr;
    wxMenuBar* menuBar = nullptr;

    void OnbtnClck(wxCommandEvent &evt);
    void MenuNew(wxCommandEvent& evt);
    void MenuOpen(wxCommandEvent& evt);
    void MenuSave(wxCommandEvent& evt);

    void MenuImport(wxCommandEvent& evt);

    void MenuExport(wxCommandEvent& evt);
    void MenuExit(wxCommandEvent& evt);

    wxString path;
    wxPanel* frame;
    wxImagePanel* drawPane;


    wxDECLARE_EVENT_TABLE();
};

