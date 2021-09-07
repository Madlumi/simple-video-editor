#include "cApp.h"
#include <wx/filefn.h>

wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}

cApp::~cApp() {
}

bool cApp::OnInit() {



    mf = new cMain();
    mf->Show();
    return true;

	/*mf = new cMain();
	mf->Show();
	return true;*/
}
