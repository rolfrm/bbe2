#ifndef EVENTED_H
#define EVENTED_H
#include <queue>
#include <string>
#include <list>
#include <map>
#include "events.h"
#include "../hash.h"
using namespace std;

class Vector2D;
class sprite;
class evented
{
public:
    evented(string id);
    virtual void handle_event(event * evt) = 0;
	virtual void take_event(event * evt) = 0;
	void sendEvent(event * evt);
	void sendEventUp(event * evt);
	void sendCustomEvent(std::string reciever, std::string str_data, boost::any data, event_recv_type rtype = SINGLE);

	void add_group(string new_group);
	void remove_group(string del_group);
	bool has_group(string group_name);
	bool has_group(hashValue group_name);
	void add_groups(list<std::string> groups);
	void distribute_groups();
	list<std::string> get_groups();

	void add_child(evented * child);
	void remove_child(evented * child);
	void set_parent(evented * parent);
	evented * get_first_child(string child_id);


	void print_children();

	void set_id(string id);
	string get_whole_id();
	string get_id();
	virtual evented * copy() = 0;
	queue <event *> event_queue;
	string id;
	hashValue h_id;
	evented * Parent;

private:

	void sendEventUp_grouped(event * evt);

	list <string> group;
	map <int,bool > group_hashes;
	list<evented *> children;
	std::queue<string> split_id(string id);
	evented * get_first_child(queue<string> id_queue);
};

class eventMaster: public evented{
public:
	eventMaster(string id);
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
	eventSlave(string id);
	eventSlave();
	void handle_event(event * evt);
	void take_event(event * evt);
};


#endif // EVENTED_H
