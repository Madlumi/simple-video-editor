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
#include "TlSliders.h"
#include "assetMng.h"
#include <wx/combobox.h>
#include <wx/tglbtn.h>
class cMain :public wxFrame {

public:
    cMain();
    ~cMain();

public:
    wxMenuBar* menuBar = nullptr;
    wxButton* nextf = nullptr;
    wxButton* prevf = nullptr;
    wxButton* play = nullptr;
    wxTimer* tim = nullptr;
    

    wxButton* zoomin = nullptr;
    wxButton* zoomout = nullptr;
    wxToggleButton* showx = nullptr;
    wxToggleButton* showy = nullptr;
    wxToggleButton* shows = nullptr;
    wxToggleButton* showr = nullptr;

    wxComboBox* interpTypeBox = nullptr;
    void ZoomDisplay(double s);
    void initControlls(wxPanel* parent);
    void onTlScroll(wxScrollWinEvent& event);
    void SetInter(wxCommandEvent& evt);
    void initPanels();
    void ShowX(wxCommandEvent& evt);

    void ShowY(wxCommandEvent& evt);

    void ShowS(wxCommandEvent& evt);

    void ShowR(wxCommandEvent& evt);

    
    void BtnNextF(wxCommandEvent& evt);
    void Zoomout(wxCommandEvent& evt);
    void Zoomin(wxCommandEvent& evt);
    void BtnPrevF(wxCommandEvent& evt);
    void BtnPlay(wxCommandEvent& evt);

    void TimNextF(wxTimerEvent& evt);

    void MenuNew(wxCommandEvent& evt);
    void MenuOpen(wxCommandEvent& evt);
    void MenuSave(wxCommandEvent& evt);

    void MenuImport(wxCommandEvent& evt);
    void MenuExport(wxCommandEvent& evt);
    void MenuExit(wxCommandEvent& evt);
    wxMenuBar* initmenu();

    assetMng* assets;
    wxPanel* topPanel;
    wxPanel* botPanel;
    wxPanel* playPanel;
    wxPanel* tlPanel;
    
    wxScrolledWindow* TimelineScroller;
    wxScrolledWindow* TimelinePointScroller;
    wxScrolledWindow* DisplayScroller;
    TlSlider* PointDrawPanle;
    //new wxScrolled(NULL, wxID_ANY, wxPoint(500, 50), wxSize(50, 50),wxHSCROLL | wxVSCROLL, wxT("scrolledWindow"));

    wxString path;
    wxPanel* frame;
    wxPanel* frame2;
    wxPanel* tlpframe;
    wxImagePanel* drawPane;
    wxPanel* panel2;
    wxImagePanel* drawPane2;

    wxDECLARE_EVENT_TABLE();

};

