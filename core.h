#ifndef CORE_H
#define CORE_H
#include "toolModule.h"
#include <string>
#include <list>
	#include "threaded.h"
class point_cloud;
class sp_object;
namespace events{
class evented;
class eventCore;
}
class physicsCore;
namespace graphics{
class graphicsCore;
}
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
				void add_entity(events::eventMaster * evt);
				void add_entity(compositePhysobj * cpo);
								void run();
				std::list <sprite *> sprite_list;

};

#endif // CORE_H
