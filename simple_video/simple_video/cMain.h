#pragma once
#include "wx/wx.h"
#include "imgFrame.h"
#include "wxImagePanel.h"
#include <wx/splitter.h>
#include "filesystem"
#include "wx/filedlg.h"
#include <string>
#include <iostream>
#include <wx/timer.h>
#include <wx/scrolwin.h>

#include "assetMng.h"

class cMain :public wxFrame {

public:
    cMain();
    ~cMain();

public:
    //wxButton* btn = nullptr;
    //wxTextCtrl* txt = nullptr;
    //wxListBox* lst = nullptr;
    wxMenuBar* menuBar = nullptr;
    wxButton* nextf = nullptr;
    wxButton* prevf = nullptr;
    wxButton* play = nullptr;
    wxTimer* tim = nullptr;
    
    void ZoomDisplay(double s);
    void OnbtnClck(wxCommandEvent &evt);
    
    void BtnNextF(wxCommandEvent& evt);
    void BtnPrevF(wxCommandEvent& evt);
    void BtnPlay(wxCommandEvent& evt);

    void TimNextF(wxTimerEvent& evt);

    void MenuNew(wxCommandEvent& evt);
    void MenuOpen(wxCommandEvent& evt);
    void MenuSave(wxCommandEvent& evt);

    void MenuImport(wxCommandEvent& evt);
    void MenuExport(wxCommandEvent& evt);
    void MenuExit(wxCommandEvent& evt);

    assetMng* assets;
    wxPanel* topPanel;
    wxPanel* botPanel;
    wxPanel* playPanel;
    wxPanel* tlPanel;

    wxScrolledWindow* tlScroller;
    wxScrolledWindow* DisplayScroller;
    //new wxScrolled(NULL, wxID_ANY, wxPoint(500, 50), wxSize(50, 50),wxHSCROLL | wxVSCROLL, wxT("scrolledWindow"));

    wxString path;
    wxPanel* frame;
    wxPanel* frame2;
    wxImagePanel* drawPane;
    wxPanel* panel2;
    wxImagePanel* drawPane2;

    wxDECLARE_EVENT_TABLE();
};

