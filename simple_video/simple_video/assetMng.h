#pragma once
#include "wx/wx.h"
#include "imgFrame.h"
#include "wxImagePanel.h"
#include <wx/splitter.h>
#include "filesystem"
#include "wx/filedlg.h"
#include <string>
#include <iostream>

typedef struct frame* TIMELINE; //+

struct frame {
	struct entry* entry;
	struct frame* next;
};
TIMELINE mkTimeline();

void timelinAdd(TIMELINE head, struct entry* e, int loc);


void deleteTimeline(TIMELINE head);


class assetMng {
public:
	assetMng();
	~assetMng();

//list of imported files in arrays(1)
//array(2) of struct with image and pointer to file in array(1) 
//array(1) can be normal array[]
//array(2):easy removal,adding, moving around sections
	//linked list?
public:
	TIMELINE tl= NULL;
	void addFolder(std::string p, wxWindow* tlpar, wxPanel* impar);
	void nextFrame();
	void prevFrame();
};

