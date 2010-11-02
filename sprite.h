/*
 * sprite.h
 *
 *  Created on: Jun 6, 2010
 *      Author: rolf
 */

#ifndef SPRITE_H_
#define SPRITE_H_
#include <list>
#include <string>
#include "toolModule.h"
class compositePhysobj;
class drawable;
#include "events/evented.h"

class sprite: public eventSlave{

public:
   sprite();
   void add_sprite(sprite *);
   void set_drawable(drawable * gfx);
   void set_physics(compositePhysobj * phy);
   void calc_absolute_coords();
   void run();
   void signal_graphics(int signal);

   //Game specific
   void set_pos(float x, float y);
   void set_pos(Vector2D position);
   void set_velocity(Vector2D new_vel);

   static Vector2D getGameCurser();
   static Vector2D getUICurser();
   static Vector2D getScreenCurser();

   sprite * copy();

   drawable * gfx;
   compositePhysobj * phy;

   Vector2D Pos;
   Vector2D OffsetPos;
   float angle;
   float offsetAngle;
   std::list <sprite *> sub_sprites;
   sprite *  super_sprite;

   bool pickupable;

};
#endif /* SPRITE_H_ */
