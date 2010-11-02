#pragma once
#include <list>
#include "CollisionHandler.h"
#include "../threaded.h"
#include "../toolModule.h"
class compositePhysobj;
class polygonFrame;
class circularFrame;

static float PhySteps=20.0;


class physicsCore:public threaded{

	public:
		physicsCore();
		~physicsCore();
		void addObject(compositePhysobj *);
		void removeObject(compositePhysobj *);
		void collisionDetection();
		void SAT(polygonFrame *,polygonFrame *);
		void SAT(polygonFrame *,circularFrame *);
		void SAT(circularFrame *,polygonFrame *);
		void SAT(circularFrame *,circularFrame *);
		bool AA_SAT(polygonFrame *, polygonFrame *); //Axis aligned seperating axis theorem
		bool RAA_SAT(polygonFrame *,polygonFrame *); //relative axis aligned seperating axis theorem
		void MoveObjects();
		void RotateObjects();
		void ResetObjects();
		void PrintAll();
		void ForceAll();
		void run();
		Vector2D gravity;
		Vector2D globalForce;
		std::list<compositePhysobj *> objects;
		sprite * PointInsideOfSprite(float x,float y);
		sprite * PointInsideOfSprite(Vector2D);
		private:
		bool PointInsideFrame(Vector2D,polygonFrame);
		SATData DataCarrier;
		CollisionRespone CP;
		float FindMax(float liste[],int);
		float FindMin(float liste[],int);

};
