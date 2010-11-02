/*
 * sprite.cpp
 *
 *  Created on: Jun 6, 2010
 *      Author: rolf
 */
#include "sprite.h"
#include "graphics/drawable.h"
#include "events/evented.h"
#include "physics/compositePhysobj.h"
#include "physics/phyArchetypes.h"
#include "physics/physics_core.h"

sprite::sprite():eventSlave("sprite"){
	gfx = NULL;
	phy = NULL;
	super_sprite = NULL;
	angle = 0;
	offsetAngle = 0;
	pickupable = false;
	set_id("sprite");
}

void sprite::run(){
	if(phy != NULL){
		Pos = phy->Base->Pos;
		angle = (phy->Base->angle)/3.147*180;
	}
}

void sprite::add_sprite(sprite * sp){
	if(sp != this){
	sub_sprites.push_back(sp);
	sp->super_sprite = this;
	}else{
		//std::cout << "Dont try to add 'this'\n";
	}
}

void sprite::set_physics(compositePhysobj * phy){
	add_child(phy);
	add_groups(phy->get_groups());
	this->phy = phy;
}

void sprite::set_drawable(drawable * gfx){
	add_child(gfx);
	add_groups(gfx->get_groups());
	this->gfx = gfx;
}


void sprite::calc_absolute_coords(){
	if(super_sprite !=NULL){
		Pos = OffsetPos;
		Pos += super_sprite->Pos;
		angle = offsetAngle + super_sprite->angle;
	}
	if(!sub_sprites.empty()){
	std::list<sprite *>::iterator i;
	for(i = sub_sprites.begin(); i != sub_sprites.end(); i++){
			(*i)->calc_absolute_coords();
		}
	}
}

void sprite::signal_graphics(int signal){
	if(gfx != NULL){
		gfx->handle_signal(signal);

	}
}
sprite * sprite::copy(){
	sprite * new_sprite = new sprite;

	if(gfx != NULL){
		new_sprite->set_drawable( gfx->copy() );
		new_sprite->gfx->Pos = &(new_sprite->Pos);
		new_sprite->gfx->angle = &new_sprite->angle;
	}

	if(phy != NULL){
		new_sprite->set_physics(phy->copy());
		new_sprite->phy->parent = new_sprite;
	}
	if(Parent != NULL){

		new_sprite->Parent = Parent->copy();
	}

	new_sprite->pickupable = pickupable;
	return new_sprite;
}

void sprite::set_pos(float x, float y){
	if(phy != NULL){
		phy->ChangePos(Vector2D(x,y));
	}else if(gfx != NULL){
		Pos.x = x;
		Pos.y = y;
	}
}

void sprite::set_pos(Vector2D position){
	if(phy != NULL){
		phy->SetPos(position);
	}else{
		Pos = position;
	}
}

void sprite::set_velocity(Vector2D new_velocity){
	if(phy != NULL){
		phy->Base->Velocity = new_velocity;
	}
}
#include "events/event_core.h"
#include "graphics/graphics_core.h"
#include "globals.h"
Vector2D sprite::getGameCurser(){
	if(event_core != NULL){
		return event_core->pointer_game;
	}
}

Vector2D sprite::getUICurser(){
	return event_core->pointer_game - graphics_core->cam.Pos;
}
