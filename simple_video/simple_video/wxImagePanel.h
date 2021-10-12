#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>


class wxImagePanel : public wxPanel {
    wxImage image;
    wxBitmap resized;
    int w, h;
    double asp;

public:
    wxPoint p = wxPoint(0, 0);
    double s = 1;
    wxImagePanel(wxPanel* parent, wxString file, wxBitmapType format);

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);
    void exportFrame(std::string p, int i, double scale, wxPoint loc, double r);
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