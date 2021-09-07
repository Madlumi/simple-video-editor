#include "cApp.h"
#include <wx/filefn.h>

wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}

cApp::~cApp() {
}

bool cApp::OnInit() {

    // make sure to call this first
    wxInitAllImageHandlers();

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame(NULL, wxID_ANY, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(800, 600));

    // then simply create like this
    
    path = wxGetCwd() + wxT("/pot.png");


    drawPane = new wxImagePanel(frame, path, wxBITMAP_TYPE_PNG);
    sizer->Add(drawPane, 1, wxEXPAND);

    frame->SetSizer(sizer);

    frame->Show();

    mf = new cMain();
    mf->Show();
    return true;

	/*mf = new cMain();
	mf->Show();
	return true;*/
}
