#ifndef EVENTED_H
#define EVENTED_H
#include <queue>
#include <string>
#include <list>
#include <map>
#include "events.h"
#include "../utils/hash.h"
class Vector2D;


namespace events{
class evented
{
public:
    evented(std::string id);
    virtual void handle_event(event * evt) = 0;
	virtual void take_event(event * evt) = 0;
	void sendEvent(event * evt);
	void sendEventUp(event * evt);
	void sendCustomEvent(std::string reciever, std::string str_data, boost::any data, event_recv_type rtype = SINGLE);

	void add_group(std::string new_group);
	void remove_group(std::string del_group);
	bool has_group(std::string group_name);
	bool has_group(utils::hashValue group_name);
	void add_groups(std::list<std::string> groups);
	void distribute_groups();
	std::list<std::string> get_groups();

	void add_child(evented * child);
	void remove_child(evented * child);
	void set_parent(evented * parent);
	evented * get_first_child(std::string child_id);


	void print_children();

	void set_id(std::string id);
	std::string get_whole_id();
	std::string get_id();
	virtual evented * copy() = 0;
	std::queue <event *> event_queue;
	std::string id;
	utils::hashValue h_id;
	evented * Parent;

private:

	void sendEventUp_grouped(event * evt);

	std::list <std::string> group;
	std::map <int,bool > group_hashes;
	std::list<evented *> children;
	std::queue<std::string> split_id(std::string id);
	evented * get_first_child(std::queue<std::string> id_queue);
};

class eventMaster: public evented{
public:
	eventMaster(std::string id);
	eventMaster();
	virtual void handleCollisionEvent(collisionEvent evt);
	virtual void handleKeyEvent(keyEvent evt);
	virtual void handleMouseEvent(mouseEvent evt);
	virtual void handleCustomEvent(customEvent evt);
	virtual void handleTurnEvent(turnEvent evt);
	void take_event(event * evt);
	void handleEvents();
	void handle_event(event * evt);

private:

};

class eventSlave: public evented{
public:
	eventSlave(std::string id);
	eventSlave();
	void handle_event(event * evt);
	void take_event(event * evt);
};
}

#endif // EVENTED_H
