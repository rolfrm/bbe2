/*
 * globals.h
 *
 *  Created on: May 7, 2010
 *      Author: rolf
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_
class graphicsCore;
class core;
class eventCore;
class physicsCore;
class soundCore;
class resource_bank;
class xmlCore;

extern graphicsCore * graphics_core;
extern core * main_core;
extern eventCore * event_core;
extern physicsCore * physics_core;
extern physicsCore *physics_ui;
extern soundCore * sound_core;
extern resource_bank * bank;
extern xmlCore * xml_core;

#endif /* GLOBALS_H_ */
