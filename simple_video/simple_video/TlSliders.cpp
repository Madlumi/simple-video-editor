#include "TlSliders.h"
#include "wx/wx.h"
#include "wx/sizer.h"
#include <string.h>




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
    EVT_LEFT_DOWN(TlSlider::mouseDown)
    EVT_LEFT_UP(TlSlider::mouseReleased)
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
    if(heldPoint!=NULL){
        double d = scaleToY_NEG(event.GetPosition().y);

        heldPoint->camEntry->scale = d;
        paintNow();
    }
    
}
void TlSlider::mouseDown(wxMouseEvent& event) {
    frame *f=getClickPoint(points, event.GetPosition());
    if (f != NULL) {
        heldPoint = f;
        heldPoint->camEntry->type = brush;
    }
}
void TlSlider::mouseReleased(wxMouseEvent& event) {
    heldPoint = NULL;
}
void TlSlider::paintEvent(wxPaintEvent& evt) {
    //wxPaintDC dc(this);
    wxBufferedPaintDC dd(this);
    render(dd);
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
    //wxBufferedPaintDC dd(this);
    render(dc);
}

/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */

void TlSlider::drawPoints(wxDC& dc, struct frame* head) {
    int i = 0;

    while (head->next != NULL) {
        /* pointbrush */
        if (head->camEntry != NULL) {
            int d =  p_diam;
            if (head->camEntry->type == EList::derived) {
                dc.SetBrush(wxBrush(wxColor(100, 100, 100), wxBRUSHSTYLE_SOLID));
                dc.SetPen(wxPen(wxColor(200, 200, 25), -1));
                d--;
            }else if (head->camEntry->type == EList::hard) {
                dc.SetBrush(wxBrush(wxColor(200, 200, 25), wxBRUSHSTYLE_SOLID));
                dc.SetPen(wxPen(wxColor(200, 200, 25), -1));
            }
            else if (head->camEntry->type == EList::linear) {
                dc.SetBrush(wxBrush(wxColor(25, 200, 25), wxBRUSHSTYLE_SOLID));
                dc.SetPen(wxPen(wxColor(25, 200, 25), -1));
            }
            else if (head->camEntry->type == EList::smooth) {
                dc.SetBrush(wxBrush(wxColor(25, 50, 200), wxBRUSHSTYLE_SOLID));
                dc.SetPen(wxPen(wxColor(25, 200, 25), -1));
            }

            dc.DrawCircle(wxPoint(i * p_dist, scaleToY(head->camEntry->scale) ), d);

        }

        i += 1;
        head = head->next;


    }
}


int TlSlider::scaleToY(double s) {
    return midY + (1 - s) * 100 - 50;
}

// i = midY + (1 - s) * 100 - 50;
// s=(midY - 50-i)/100+1
double TlSlider::scaleToY_NEG(int i) {
   

    return (double(midY - 50 - i)/100)+1;
    //return midY + (1 - s) * 100 - 50;
}
void stupidvsoutput(int i) {
   

    char num_char[10 + sizeof(char)];

    std::sprintf(num_char, "%d", i);

    OutputDebugStringA(num_char);
    OutputDebugStringA("\n");
}
frame* TlSlider::getClickPoint(struct frame* head,wxPoint cp) {
    int i = 0;
    while (head->next != NULL) {
        /* pointbrush */
        if (head->camEntry != NULL) {
            if (
                 (cp.x - i * p_dist)
                *(cp.x - i * p_dist) +
                 (cp.y - scaleToY(head->camEntry->scale))
                *(cp.y - scaleToY(head->camEntry->scale))
         
                < (p_diam*p_diam)) {

                stupidvsoutput(i);

                return head;
            }
            
            //dc.DrawCircle(wxPoint(i * p_dist, midY + (1 - head->camEntry->scale) * 100 - 50), p_diam);

        }

        i += 1;
        head = head->next;


    }
    return NULL;
}
void drawBg(wxDC& dc) {
    dc.SetBrush(wxBrush(wxColor(200, 200, 200), wxBRUSHSTYLE_SOLID));
    dc.SetPen(wxPen(wxColor(150, 150, 150), 1));
    
    int boxsize = 100;
    for (int x = 0; x < dc.GetSize().GetWidth()/100; x++) {
        for (int y = 0; y < dc.GetSize().GetHeight() / 100; y++) {
            dc.DrawRectangle(x* boxsize, y* boxsize, boxsize, boxsize);
        }
    }
    //
}
void TlSlider::render(wxDC& dc) {
    //dc.Clear();
    drawBg(dc);



    if (points != NULL) { drawPoints(dc, points); };
    
    // draw some text
    dc.DrawText(wxT("Testing"), 40, 60);

    // draw a circle
    //dc.SetBrush(*wxGREEN_BRUSH); // green filling
    //dc.SetPen(wxPen(wxColor(255, 0, 0), 5)); // 5-pixels-thick red outline
    //dc.DrawCircle(wp, 5 /* radius */);

    // draw a rectangle


    // draw a line
    dc.SetPen(wxPen(wxColor(0, 0, 0), 3)); // black line, 3 pixels thick
    dc.DrawLine(300, 100, 700, 300); // draw line across the rectangle

    // Look at the wxDC docs to learn how to draw other stuff
}