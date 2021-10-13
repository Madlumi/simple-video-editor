#include "wxImagePanel.h"
#include "assetMng.h"


BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
// some useful events
/*
 EVT_MOTION(wxImagePanel::mouseMoved)
 EVT_LEFT_DOWN(wxImagePanel::mouseDown)
 EVT_LEFT_UP(wxImagePanel::mouseReleased)
 EVT_RIGHT_DOWN(wxImagePanel::rightClick)
 EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
 EVT_KEY_DOWN(wxImagePanel::keyPressed)
 EVT_KEY_UP(wxImagePanel::keyReleased)
 EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
 */

 // catch paint events
    EVT_PAINT(wxImagePanel::paintEvent)
    //Size event
    EVT_SIZE(wxImagePanel::OnSize)
END_EVENT_TABLE()


    // some useful events
    /*
     void wxImagePanel::mouseMoved(wxMouseEvent& event) {}
     void wxImagePanel::mouseDown(wxMouseEvent& event) {}
     void wxImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
     void wxImagePanel::mouseReleased(wxMouseEvent& event) {}
     void wxImagePanel::rightClick(wxMouseEvent& event) {}
     void wxImagePanel::mouseLeftWindow(wxMouseEvent& event) {}
     void wxImagePanel::keyPressed(wxKeyEvent& event) {}
     void wxImagePanel::keyReleased(wxKeyEvent& event) {}
     */

    wxImagePanel::wxImagePanel(wxPanel* parent, wxString file, wxBitmapType format) :
    wxPanel(parent) {
    // load the file... ideally add a check to see if loading was successful
    image.LoadFile(file, format);
    
    w = -1;
    h = -1;
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void wxImagePanel::paintEvent(wxPaintEvent& evt) {
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 */
void wxImagePanel::paintNow() {
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */





void wxImagePanel::render(wxDC& dc) {
    int neww, newh;
    dc.GetSize(&neww, &newh);

    if ((neww != w || newh != h ) ) {


        wxSize s = image.GetSize();
        asp = (1.0 * s.GetWidth()) / (1.0 * s.GetHeight());
        
        /*std::string ss = std::to_string(asp);
        char const* pchar = ss.c_str();  //use char const* as target type
        OutputDebugStringA(pchar);
        */
        //asp = s.GetWidth() / s.GetHeight();
        neww = newh * asp;
        
        
        resized = wxBitmap(image.Scale(neww, newh /*, wxIMAGE_QUALITY_HIGH*/));
        w = neww;
        h = newh;
        dc.DrawBitmap(resized, 0, 0, false);
       
    } else {
        dc.DrawBitmap(resized, 0, 0, false);
    }

    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.DrawRectangle(wxPoint(p.x/s,p.y/s),wxSize(w/s,h/s));
}

/*
 * Here we call refresh to tell the panel to draw itself again.
 * So when the user resizes the image panel the image should be resized too.
 */
void wxImagePanel::OnSize(wxSizeEvent& event) {
    Refresh();
    //skip the event.
    event.Skip();
}

void wxImagePanel::exportFrame(std::string p, int i, double scale, wxPoint loc, double r) {
    std::string pp = p +"/file_"+ std::to_string(i)+".png";
    //wxImage img = image.Rotate(0);
    wxImage iiii = image.Size(wxSize(image.GetWidth()/scale,image.GetHeight() / scale), loc);
    iiii.SaveFile(pp);
    iiii.Destroy();
}