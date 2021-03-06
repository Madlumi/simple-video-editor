#include "assetMng.h"
#include "EList.h"
#include "Entry.h"
#include < windows.h >
#include <wx/progdlg.h>

assetMng::assetMng() {
}

assetMng::~assetMng() {
}


struct frame* mkTimeline() {
	struct frame* f = (struct frame*) malloc(sizeof(struct frame));
	f->next = NULL;
	f->entry = NULL;
	f->camEntry = NULL;
	return f;

}

void timelineAdd(TIMELINE head, struct entry* p,struct camEntry* ce, int loc) {
	struct frame* f = (struct frame*) malloc(sizeof(struct frame));
	f->next = NULL;
	f->entry = p;
	f->camEntry = ce;
	if (head->next == NULL) {
		head->next = f;
		return;
	}

	struct frame* nav = head;

	for(int i=0; i < loc; ){
		if (nav->next == NULL) {
			break;
		}
		i+=nav->entry->hold;
		nav = nav->next;
	}
	f->next = nav->next;
	nav->next = f;
}

void timelineAddEnd(TIMELINE head, struct entry* p, struct camEntry* ce) {
	struct frame* f = (struct frame*) malloc(sizeof(struct frame));
	f->next = NULL;
	f->entry = p;
	f->camEntry = ce;
	if (head->next == NULL) {
		head->next = f;
		return;
	}

	struct frame* nav = head;

	while (1){
		if (nav->next == NULL) {
			break;
		}
		nav = nav->next;
	}
	f->next = nav->next;
	nav->next = f;
}

int tlLength(struct frame* head) {
	int i = 0;
	while (head->next != NULL) {
		i+=head->entry->hold;
		head = head->next;
	}
	return i;
}

//struct entry* getFrame(TIMELINE head, int loc);

void deleteTimeline(struct frame* f) {
	if (f->next != NULL)deleteTimeline(f->next);
	free(f->entry);
	free(f);
}

void deleteFrame(struct frame* f) {
	if (f->next != NULL)deleteTimeline(f->next);
	free(f->entry);
	free(f);
}
int mLoad = 96;

void assetMng::addFolder(std::string p, wxWindow* tlpar, wxPanel* impar) {
	if(tl==NULL)tl = mkTimeline();
	
	int iii = 0;
	//entry* e[10];
	//for (int i = 0; i < 10; i++) {
	//	e[i] = entry_create(":)", tlpar,impar, i);
	//}
	OutputDebugString(L":DDDDD0\n");
	wxProgressDialog *progress = new 
	wxProgressDialog("Loading...",
		"Importing files",
		mLoad,
		NULL, 
		wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_REMAINING_TIME
		);

	for (const auto& entry : std::filesystem::directory_iterator(p)) {
		std::string sss{ entry.path().u8string() };
		OutputDebugString(L""+(sss)+"\n");
		timelineAddEnd(tl, entry_create(sss.c_str(), tlpar, impar, iii), camEntry_create(0, 0, 0, 1, 0, EList::derived));
		progress->Update(iii);
		//TODO remove 
		iii++;
		tlLen += 15;
		if (iii >=mLoad) {
			break;
		}
		//timelineAddEnd(tl, mkEntry(sss));
	}
	OutputDebugString(L":DDDDD1\n");
	progress->Destroy();
	OutputDebugString(L":DDDDD2\n");
}

bool assetMng::exportFolder(std::string p) {
	frame* head = tl->next;



	if (head == NULL) {
		OutputDebugString(L"nextFrame: no head\n");
		return false;
	}
	wxProgressDialog* progress = new
		wxProgressDialog("Rendering...",
			"Exporting files",
			mLoad,
			NULL,
			wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_REMAINING_TIME
		);
	int frameN = 0;
	while (head->next != NULL) {
		//head->next->entry->img->Show(true);
		//head->entry->img->Show(false);
		//head->next->entry->img->Layout();
		head->entry->img->exportFrame(p,frameN,head->camEntry->scale,wxPoint(head->camEntry->x, head->camEntry->y), head->camEntry->r);
		frameN++;
		progress->Update(frameN);
		head = head->next;
	}
	progress->Destroy();
	return true;
}

void assetMng::nextFrame() {
	if (tl == NULL) { return; };
	frame* head = tl->next;
	if (head == NULL) {
		OutputDebugString(L"nextFrame: no head\n");
		return;
	}
	int frameN = 0;
	while (head->next != NULL) {
		if (head->entry->img->IsShown()) {
			head->next->entry->show();
			head->next->camEntry->update(head->next->entry);
			head->entry->hide();
			return;
		}
		frameN++;
		head = head->next;
	}
	tl->next->entry->show();
	tl->next->camEntry->update(tl->next->entry);
	head->entry->hide();
}
void assetMng::prevFrame() {
	

	if (tl == NULL) { return; };
	frame* head = tl->next;
	if (head == NULL) {
		OutputDebugString(L"nextFrame: no head\n");
		return;
	}
	frame* prev = tl->next;//getlast
	while (prev->next != NULL) {
		prev = prev->next;
	}
	int frameN = 0;
	while (head->next != NULL) {
		if (head->entry->img->IsShown()) {
			prev->entry->show();
			prev->camEntry->update(prev->entry);
			head->entry->hide();
			return;
		}
		frameN++;
		prev = head;
		head = head->next;
	}
	prev->entry->show();
	prev->camEntry->update(prev->entry);
	head->entry->hide();
}
