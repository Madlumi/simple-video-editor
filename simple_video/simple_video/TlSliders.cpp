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
        
        if (heldType == EList::sp) { double d = scaleToY_NEG(event.GetPosition().y, heldType); heldPoint->camEntry->scale = d; }
        if (heldType == EList::xp) { int    d = scaleToY_NEG(event.GetPosition().y, heldType); heldPoint->camEntry->x     = d; }
        if (heldType == EList::yp) { int    d = scaleToY_NEG(event.GetPosition().y, heldType); heldPoint->camEntry->y     = d; }
        if (heldType == EList::rp) { int    d = scaleToY_NEG(event.GetPosition().y, heldType); heldPoint->camEntry->r     = d; }
        interpCam(points);
        paintNow();
    }
    
}
void TlSlider::mouseDown(wxMouseEvent& event) {
    frame *f=getClickPoint(points, event.GetPosition());
    if (f != NULL) {
        heldPoint = f;
        heldPoint->camEntry->type[heldType] = brush;
    }
    mouseMoved(event);
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

void TlSlider::drawPoint(wxDC& dc, struct frame* head,int i, int j) {
    if (head->next->camEntry != NULL) {
        dc.SetPen(wxPen(col[j], 3));
        
        if (j == EList::sp)dc.DrawLine(i * p_dist, scaleToY(head->camEntry->scale,j), (i + 1) * p_dist, scaleToY(head->next->camEntry->scale,j));
        if (j == EList::xp)dc.DrawLine(i * p_dist, scaleToY(head->camEntry->x, j), (i + 1) * p_dist, scaleToY(head->next->camEntry->x, j));
        if (j == EList::yp)dc.DrawLine(i * p_dist, scaleToY(head->camEntry->y, j), (i + 1) * p_dist, scaleToY(head->next->camEntry->y, j));
        if (j == EList::rp)dc.DrawLine(i * p_dist, scaleToY(head->camEntry->r, j), (i + 1) * p_dist, scaleToY(head->next->camEntry->r, j));
    }

    int d = p_diam;
    if (head->camEntry->type[j] == EList::derived) {
        dc.SetBrush(wxBrush(wxColor(100, 100, 100), wxBRUSHSTYLE_SOLID));
        dc.SetPen(wxPen(col[j], 2));
        d--;
    } else if (head->camEntry->type[j] == EList::hard) {
        dc.SetBrush(wxBrush(wxColor(200, 200, 25), wxBRUSHSTYLE_SOLID));
        dc.SetPen(wxPen(col[j], 2));
    } else if (head->camEntry->type[j] == EList::linear) {
        dc.SetBrush(wxBrush(wxColor(25, 200, 25), wxBRUSHSTYLE_SOLID));
        dc.SetPen(wxPen(col[j], 2));
    } else if (head->camEntry->type[j] == EList::smooth) {
        dc.SetBrush(wxBrush(wxColor(25, 200, 200), wxBRUSHSTYLE_SOLID));
        dc.SetPen(wxPen(col[j], 2));
    }

    if (j == EList::sp) { dc.DrawCircle(wxPoint(i * p_dist, scaleToY(head->camEntry->scale, j)), d); }
    if (j == EList::xp) { dc.DrawCircle(wxPoint(i * p_dist, scaleToY(head->camEntry->x, j)), d); }
    if (j == EList::yp) { dc.DrawCircle(wxPoint(i * p_dist, scaleToY(head->camEntry->y, j)), d); }
    if (j == EList::rp) { dc.DrawCircle(wxPoint(i * p_dist, scaleToY(head->camEntry->r, j)), d); }

}
void TlSlider::drawPoints(wxDC& dc, struct frame* head) {
    int i = 0;

    while (head->next != NULL) {
        if (head->camEntry != NULL) {

            for (int j = 0; j < point_types;j++) {
                dc.SetPen(wxPen(col[j], 1, wxPENSTYLE_DOT));
                if(j == EList::sp) { 
                    dc.DrawLine(0, scaleToY(1,j), dc.GetSize().GetWidth(), scaleToY(1, j)); 
                } else { 
                    dc.DrawLine(0, mids[j], dc.GetSize().GetWidth(), mids[j]); 
                }
                if (show_point[j])drawPoint(dc, head, i, j);
            }

        }
        i += 1;
        head = head->next;

    }
}


int TlSlider::scaleToY(double s, int j) {
    if (j == EList::sp){return mids[j] + (1 - s) * 100 - 50;}
    return mids[j] + s;
}

double TlSlider::scaleToY_NEG(int i, int j) {
   

    if (j == EList::sp) { return (double(double(mids[j]) - 50 - i) / 100) + 1; }
    return i- double(mids[j]) ;
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
        if (head->camEntry != NULL) {
            
            double d;
            for (int j = 0; j < point_types; j++) {

                if (j == EList::sp) { d = head->camEntry->scale;
                } else if (j == EList::xp) { d = head->camEntry->x;
                } else if (j == EList::yp) { d = head->camEntry->y;
                } else if (j == EList::rp) { d = head->camEntry->r; }

                if (
                    (cp.x - i * p_dist)
                * (cp.x - i * p_dist) +
                (cp.y - scaleToY(d, j))
                * (cp.y - scaleToY(d, j))

                < (p_diam * p_diam)) {

                    heldType = j;
                    return head;
                }

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
    for (int x = 0; x <= dc.GetSize().GetWidth()/100; x++) {
        for (int y = 0; y <= dc.GetSize().GetHeight() / 100; y++) {
            dc.DrawRectangle(x* boxsize, y* boxsize, boxsize, boxsize);
        }
    }
    //
}
void TlSlider::render(wxDC& dc) {
    drawBg(dc);
    if (points != NULL) { drawPoints(dc, points); };
}
void interpCam(struct frame* head) {
    int i = 0;

    for (int j = 0; j < 4; j++) {
        struct frame* nav = head;
        while (nav->next != NULL) {
            if (nav->camEntry != NULL) {
                if (nav->camEntry->type[j] != EList::derived) {
                    int len = untilNextPoint(nav, j);
                    interpCamSpan(nav, len, j);
                }
            }
            nav = nav->next;
        }
    }
}
void interpCamSpan(struct frame* head, int len, int j) {
    double start;
    double end;
    struct frame* nav = head;
    int type = nav->camEntry->type[j];
    if (j == EList::sp) { start = nav->camEntry->scale; 
    } else if (j == EList::xp) { start = nav->camEntry->x; 
    } else if (j == EList::yp) { start = nav->camEntry->y; 
    } else if (j == EList::rp) { start = nav->camEntry->r; }

    for (int i = 0; i < len; i++) { nav = nav->next; }
    if (j == EList::sp) { end = nav->camEntry->scale; 
    } else if (j == EList::xp) { end = nav->camEntry->x; 
    } else if (j == EList::yp) { end = nav->camEntry->y; 
    } else if (j == EList::rp) { end = nav->camEntry->r; }

    nav = head;
    if (len > 1) {
        for (int i = 0; i < len; i++) {

            double val = calcInter(start, end, len, i, type);

            if (j == EList::sp) {
                nav->camEntry->scale = val;
            } else if (j == EList::xp) {
                nav->camEntry->x = val;
            } else if (j == EList::yp) {
                nav->camEntry->y = val;
            } else if (j == EList::rp) { 
                nav->camEntry->r = val; 
            }
            nav = nav->next;
        }
    }
}
double calcInter(double start, double end, int len, int curr, int type) {
    if (type == EList::hard) {
        return start;
    } else if (type == EList::linear) {
        return start + ((end - start) / len) * curr;
    } else if (type == EList::smooth) {
        /*unimplemented*/
        double t =(curr*1.0) / (len*1.0);
        float sqt = t * t;
        return start +  (sqt / (2.0 * (sqt - t) + 1.0))*((end - start));
    }
    return start;
}

int untilNextPoint(struct frame* head, int j) {
    int i = 0;
    while (head->next != NULL) {
        i += head->entry->hold;
        head = head->next;
        if (head->camEntry->type[j] != EList::derived) { return i; }
    }
    return i;
}