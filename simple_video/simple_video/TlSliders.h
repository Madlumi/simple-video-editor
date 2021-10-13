#pragma once
#include <wx/wx.h>
#include "assetMng.h"
#include "EList.h"
#include "Entry.h"
#include <wx/dcbuffer.h>
class TlSlider : public wxPanel {

public:
    int p_dist = 15;
    int p_diam = 6;
    
    int brush = EList::linear;
    TIMELINE points=NULL;
    frame* heldPoint = NULL;
    int point_types = 4;
    bool show_point[4] = { true,true,true,true };
    int mids[4] = { 200,300,300,400 };
    wxColor col[4] = { wxColor(255,0,0),wxColor(0, 255, 0),wxColor(0, 0, 255),wxColor(175, 0, 175) };

    TlSlider(wxPanel* parent);
    wxPoint wp = wxPoint(0,0);
    void mouseMoved(wxMouseEvent& event);

    void mouseDown(wxMouseEvent& event);

    void mouseReleased(wxMouseEvent& event);

    void paintEvent(wxPaintEvent& evt);

    void initTl(TIMELINE t);

    void paintNow();
    void drawPoint(wxDC& dc, frame* head, int i, int j);
    void drawPoints(wxDC& dc, struct frame* head);

    int scaleToY(double s, int j);
    double scaleToY_NEG(int i, int j);
    frame* getClickPoint(frame* head, wxPoint cp);
    void render(wxDC& dc);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()
};