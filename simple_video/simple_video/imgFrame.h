#pragma once
#include "wx/wx.h"
class imgFrame : public wxMDIChildFrame{

public:
	imgFrame(wxMDIParentFrame* p, wxString name);
	~imgFrame();
};

