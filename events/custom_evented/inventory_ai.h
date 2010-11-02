/*
 * inventory_ai.h
 *
 *  Created on: Sep 5, 2010
 *      Author: rolf
 */

#ifndef INVENTORY_AI_H_
#define INVENTORY_AI_H_

#include "../evented.h"

class inventory_ai: public eventMaster {
public:
	inventory_ai();
	virtual ~inventory_ai();
	evented * copy();
	void handleCustomEvent(customEvent evt);
};

#endif /* INVENTORY_AI_H_ */
