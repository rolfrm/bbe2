#ifndef CORE_H
#define CORE_H
#include "toolModule.h"
#include <string>
#include <list>
	#include "threaded.h"
class point_cloud;
class sp_object;
class evented;
class eventCore;
class physicsCore;
class graphicsCore;
class drawable;
class soundCore;
class compositePhysobj;
class eventMaster;
class sprite;
class core:public threaded
{
public:
    core();
				int start_modules();
				int kill_modules();
				//int outnr;
				void add_entity(drawable * dw);
				void add_entity(eventMaster * evt);
				void add_entity(compositePhysobj * cpo);
				void add_entity(sprite * sp);
				sprite * get_closest_pickupable(int x, int y);
				void remove_entity(sprite *sp);

				sprite * getFirstSprite(std::string id);

				void run();
				std::list <sprite *> sprite_list;

};

#endif // CORE_H
