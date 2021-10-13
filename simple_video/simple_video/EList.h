#pragma once
class EList {
	public:
		enum id {
			MenuNew= 10001,
			MenuOpen = 10002, 
			MenuSave = 10003, 
			MenuImport = 10004, 
			MenuExport = 10005, 
			MenuExit = 10006,
			Nextf= 10007,
			prevf = 10008,
			play = 10009,
			Timer = 10010,
			TlpScroll = 10011,

			zoomin = 10012,
			zoomout = 10013,
			showx = 10014,
			showy = 10015,
			shows = 10016,
			showr = 10017,
			interpTypeBox= 10018
		};
		enum cam {
			derived = 0,
			hard = 1,
			linear = 2,
			smooth = 3,
		};
		enum pointtypes {
			xp = 0,
			yp = 1,
			sp = 2,
			rp = 3,
		};
		

};

