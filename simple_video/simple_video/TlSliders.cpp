#include "TlSliders.h"
#include "wx/wx.h"
#include "wx/sizer.h"





BEGIN_EVENT_TABLE(TlSlider, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

 // catch paint events
    EVT_MOTION(TlSlider::mouseMoved)
    EVT_PAINT(TlSlider::paintEvent)

END_EVENT_TABLE()


    // some useful events
    /*
     void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
     void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
     void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
     void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
     void BasicDrawPane::rightClick(wxMouseEvent& event) {}
     void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
     void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
     void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
     */

    TlSlider::TlSlider(wxPanel* parent) : wxPanel(parent) { SetBackgroundColour(wxColor(1, 2, 250)); }

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */


void TlSlider::mouseMoved(wxMouseEvent& event) {
    wp = event.GetPosition();
    paintNow();
}
void TlSlider::paintEvent(wxPaintEvent& evt) {
    wxPaintDC dc(this);
    render(dc);
}

void TlSlider::initTl(TIMELINE t) {
    points = t;
    this->GetParent()->Layout();

}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void TlSlider::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */

void TlSlider::drawPoints(wxDC& dc, struct frame* head) {
    int i = 0;
    int p_dist = 15;
    int p_diam = 5;
    while (head->next != NULL) {
        /* pointbrush */
        dc.SetBrush(*wxGREEN_BRUSH); // green filling
        dc.SetPen(wxPen(wxColor(255, 0, 0), 5)); // 5-pixels-thick red outline

        dc.DrawCircle(wxPoint(i*p_dist,100), p_diam /* radius */);

        i += 1;
        head = head->next;


    }
}

void TlSlider::render(wxDC& dc) {

    if (points != NULL) { drawPoints(dc, points); };
    OutputDebugStringA("123sdfgsdfgvsdfgdfsfds");
    // draw some text
    dc.DrawText(wxT("Testing"), 40, 60);

    // draw a circle
    dc.SetBrush(*wxGREEN_BRUSH); // green filling
    dc.SetPen(wxPen(wxColor(255, 0, 0), 5)); // 5-pixels-thick red outline
    dc.DrawCircle(wp, 5 /* radius */);

    // draw a rectangle
    //dc.SetBrush(*wxBLUE_BRUSH); // blue filling
    //dc.SetPen(wxPen(wxColor(255, 175, 175), 10)); // 10-pixels-thick pink outline
    //dc.DrawRectangle(0, 0, 200, 200);

    // draw a line
    dc.SetPen(wxPen(wxColor(0, 0, 0), 3)); // black line, 3 pixels thick
    dc.DrawLine(300, 100, 700, 300); // draw line across the rectangle

    // Look at the wxDC docs to learn how to draw other stuff
}