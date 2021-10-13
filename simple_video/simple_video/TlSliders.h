#pragma once
#include <wx/wx.h>
#include "assetMng.h"
#include "EList.h"
#include "Entry.h"
class TlSlider : public wxPanel {

public:
    TIMELINE points=NULL;
    
    TlSlider(wxPanel* parent);
    wxPoint wp = wxPoint(0,0);
    void mouseMoved(wxMouseEvent& event);

    void paintEvent(wxPaintEvent& evt);

    void initTl(TIMELINE t);

    void paintNow();
    void drawPoints(wxDC& dc, struct frame* head);
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