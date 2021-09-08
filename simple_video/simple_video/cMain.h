#pragma once
#include "wx/wx.h"
#include "imgFrame.h"
#include "wxImagePanel.h"
#include <wx/splitter.h>
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
    wxPanel* topPanel;
    wxPanel* botPanel;
    wxString path;
    wxPanel* frame;
    wxImagePanel* drawPane;
    wxPanel* panel2;
    wxImagePanel* drawPane2;

    wxDECLARE_EVENT_TABLE();
};

