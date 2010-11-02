#pragma once
#include <list>
#include <vector>
#include <string>
//#include "phyArchetypes.h"
#include "../toolModule.h"
//#include "physics_core.h"
class basePhy;
class baseFrame;
class rigidBody;
class polygonFrame;
class sprite;
class physicsCore;
class compositePhysobj;

struct SATData{
	Vector2D SeperatingVector;
	Vector2D ContactPoint;
	Vector2D CollisionAxis;
	compositePhysobj * obj1, * obj2;
	int axis_from;
	bool Collision;
	float j;
};

struct CollisionData{
	compositePhysobj * ContactObj;
	Vector2D SeperatingVector,ContactPoint,CollisionAxis;
	compositePhysobj * contact;
};
#include "../events/evented.h"
class compositePhysobj: public eventSlave{

	public:
		compositePhysobj(float x,float y);
		compositePhysobj(Vector2D);
		~compositePhysobj();
		void Rotate(float);
		void Move(float);
		void Reset();
		void LoadPhyFrame(polygonFrame *);
		void LoadPhyFrame(polygonFrame *,float,float);
		void LoadPhyFrame(polygonFrame);
		void LoadPhyFrame(polygonFrame,float,float);
		void LoadPhyFrame(std::list<polygonFrame>,float,float);
		void LoadEventFrame(polygonFrame *);
		void LoadEventFrame(polygonFrame *,float,float);
		void LoadRigid(rigidBody*);
		void CalculateMomentofInertia();
		void PrintPhyFrames();
		void ChangePos(Vector2D);
		void SetPos(Vector2D);
		void HandleCollision(Vector2D offset,float impulsemomentum,Vector2D r,Vector2D axis);
		void EmptyPhyframes();
		void EmptyEventframes();
		void ApplyForce(Vector2D force);
		void ApplyForce(Vector2D force,Vector2D arm);
		void ApplyGravity(Vector2D gravity);
		Vector2D ApplyStaticFriction(Vector2D force);
		void HandleStaticFriction(Vector2D force);
		void AnalyzeForces();
		void AddCollisionContact(SATData);
		compositePhysobj * copy();
		bool MassInf();
		float getMass();
		float getInertia();
		float getAnglespeed();
		Vector2D getVelocity();
		Vector2D getAccelleration();
		Vector2D getPosition();

		basePhy * Base;
		std::list<polygonFrame> phyFrame; //Ideen er her at frameen udgør den fysiske body
		rigidBody * phyBody; //denne klasse indeholder de fysiske data
		std::list<polygonFrame> eventFrame; //Disse frames er polygoner der trigger events
		bool hasRigid; //
		bool hasEvent; // Denne boolske værdi sammen med den herover skal gøre collision detektion mere effektiv
		bool rotable;
		bool stat; //statisk
		std::vector<SATData> CollsionContacts;
	//	std::vector<Vector2D> CollisionForces,KineticFrictionForces,StaticFrictionForces,CollisionArms,KineticFrictionArms;
		Vector2D CollisionOffset;
		std::string id;
		sprite * parent;
		physicsCore * world;
		bool ui_element;
};
