#include "assetMng.h"
#include "Entry.h"

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
struct entry* mkEntry(std::string s) {
	struct entry* e = (struct entry*) malloc(sizeof(struct entry));
	return e;
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
struct entry* getFrame(struct frame* head, int loc) {
	if (loc > tlLength(head) || loc < 1) {
		return NULL;
	}

	for (int i = 0; i < loc;) {
		
		head = head->next;
		i += head->entry->hold;
	}
	return head->entry;
}
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

void assetMng::addFolder(std::string p) {
	TIMELINE tl = mkTimeline();

	for (const auto& entry : std::filesystem::directory_iterator(p)) {
		std::string sss{ entry.path().u8string() + "\n" };
		timelineAddEnd(tl, mkEntry(sss));
	}
}
