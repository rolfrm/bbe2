#ifndef EVENT_CORE_H
#define EVENT_CORE_H
#include "evented.h"
#include <list>
#include <queue>
//#include "../threaded.h"
//#include "../toolModule.h"
namespace events {

class evented;
class event;
class eventMaster;
class eventCore//:public threaded
{

public:
	eventCore();
	void add_unit(eventMaster * evt);
	void remove_unit(eventMaster * evt);
	void run();
	void take_event(event * evt);
	void send_event(event * evt);
	eventMaster * get_evented(int number_in_list);
	eventMaster * get_evented(std::string name); //first occurence
	void send_events();

private:
	std::list<eventMaster *> evented_list;
	std::queue<event *> event_queue;
	//boost::mutex take_event_lock;
};

}
#endif // EVENT_CORE_H
