#include "assetMng.h"
#include "Entry.h"
#include < windows.h >
assetMng::assetMng() {
}

assetMng::~assetMng() {
}


struct frame* mkTimeline() {
	struct frame* f = (struct frame*) malloc(sizeof(struct frame));
	f->next = NULL;
	f->entry = NULL;
	return f;

}

void timelineAdd(TIMELINE head, struct entry* p, int loc) {
	struct frame* f = (struct frame*) malloc(sizeof(struct frame));
	f->next = NULL;
	f->entry = p;
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

void timelineAddEnd(TIMELINE head, struct entry* p) {
	struct frame* f = (struct frame*) malloc(sizeof(struct frame));
	f->next = NULL;
	f->entry = p;
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

void assetMng::addFolder(std::string p, wxWindow* tlpar, wxPanel* impar) {
	if(tl==NULL)tl = mkTimeline();
	int iii = 0;
	//entry* e[10];
	//for (int i = 0; i < 10; i++) {
	//	e[i] = entry_create(":)", tlpar,impar, i);
	//}

	for (const auto& entry : std::filesystem::directory_iterator(p)) {
		std::string sss{ entry.path().u8string() };
		OutputDebugString(L""+(sss)+"\n");
		timelineAddEnd(tl, entry_create(sss.c_str(), tlpar, impar, iii));

		//TODO remove 
		iii++;
		if (iii >= 24) {
			break;
		}
		//timelineAddEnd(tl, mkEntry(sss));
	}
}

bool assetMng::exportFolder(std::string p) {
	frame* head = tl->next;
	if (head == NULL) {
		OutputDebugString(L"nextFrame: no head\n");
		return false;
	}
	int frameN = 0;
	while (head->next != NULL) {
		//head->next->entry->img->Show(true);
		//head->entry->img->Show(false);
		//head->next->entry->img->Layout();
		head->entry->img->exportFrame(p,frameN);
		frameN++;
		head = head->next;
	}
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
			head->next->entry->img->Show(true);
			head->entry->img->Show(false);
			head->next->entry->img->Layout();
			
			return;
		}
		frameN++;
		head = head->next;
	}
	tl->next->entry->img->Show(true);
	head->entry->img->Show(false);
	tl->next->entry->img->Layout();
	
}
void assetMng::prevFrame() {
	
}
