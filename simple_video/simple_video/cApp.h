#pragma once

#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp {

public:
	cApp();
	~cApp();

public:
	bool OnInit();
private:
	cMain* mf = nullptr;

};


