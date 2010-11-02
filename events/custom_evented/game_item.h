#include "../evented.h"
#include "../events.h"
class Camera;
class game_item: public eventMaster{
public:
	game_item();
	evented * copy();
private:
	Camera * old_cam;
};
