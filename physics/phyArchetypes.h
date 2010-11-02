#pragma once
#include <list>
#include "compositePhysobj.h"
#include "../toolModule.h"
#include <string>
//#include "factory.h"
#define PIDIV2 1.570796326794896619231
#define PI 3.1415926535897932384626433
//class Vector2D;
class factory;
//class list;
struct design_scheme;
class rigidBody{ //Denne klasse indeholder data for alle fysiske objekter

	public:
		rigidBody(float,float,float,float);
		~rigidBody();


		float mass; //objektets masse
		float density; //objektets densitet
		float inertia; //objektets inerti moment
		float kimu; //objektets kinetiske gnidnings koffecient
		float statmu; //objektets statiske gnidnings koeffecient
		float e; //objektets elasticitet
		Vector2D Force;
		float Torque;

		rigidBody * copy();

};

class basePhy{ //Denne klasse indeholder base data for alle objekter såsom velocity, position etc.
	public:
		basePhy(float x,float y);
		~basePhy();
		Vector2D Velocity;
		Vector2D PrePos;
		Vector2D Pos;
		float angleSpeed;
		float angle;
		basePhy * copy();


};

class baseFrame{ //Denne klass gøre virtuel, skal indeholde udstrækningen for alle objekter
	public:
		virtual void onCollision(baseFrame * other)=0;
		int collisionDepth;
		compositePhysobj * parent;
		std::string id;
		bool rigid;
};

class polygonFrame:public baseFrame{
public:
	polygonFrame();
	~polygonFrame();
	void onCollision(baseFrame * other);
	void CalculateAxis();
	void CalculateAbsoluteAxisAlignedBox();
	void CalculateRelativeAxisAlignedBox();
	void PrintVertex();
	void PrintAxis();
	void PrintRAAB();
	void AddVertex(float,float);
	void AddVertex(Vector2D);
	void EmptyVertex();
	polygonFrame * copy();
	Vector2D AAAB[2], RAAB[2]; //axis aligned box
	std::list<Vector2D> vertex;
	std::list<Vector2D> axis;
	bool AxisCalculated,RAABCalculated;

private:
	float periphial;
};

class circularFrame:public baseFrame{
public:
	circularFrame();
	circularFrame(float radius,float centerx,float centery);
	void onCollision(baseFrame * other);
	float radius;
	Vector2D Center;
private:
};

class PolygonframeFactory{
public:
		PolygonframeFactory();
		void manufacture(design_scheme *);


};

class Spring{
public:
	Spring(float,float);
	void ApplySpringForce();
	void SetFirstActachment(compositePhysobj * obj1);
	void SetSecondActachment(compositePhysobj * obj2);

private:
	float springConstant,restLength;
	compositePhysobj * obj1,* obj2;

};
