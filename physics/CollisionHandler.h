#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include <armadillo>
#include "../toolModule.h"
#include "compositePhysobj.h"
#include "phyArchetypes.h"

class physicsCore;

struct ReturnData{
	int j;
	float s;
};

class CollisionRespone{
public:
	CollisionRespone();
	void AddCollisionData(SATData);
	void run();
	void reset();
	physicsCore * parent;
	SATData DataCarrier;
private:
	void ImpulseResponse(compositePhysobj *,compositePhysobj *);
	void ContactForceResponse();
	void Friction(compositePhysobj *,compositePhysobj *);
	void findNeighbour();
	bool HandleCollision();
	arma::fmat CalculateMatrixA();
	arma::fmat CalculateMatrixB();
	arma::fmat fdirection(int d,arma::fmat A,std::list<int> C);
	ReturnData maxStep(arma::fmat f,arma::fmat a,arma::fmat delta_f,arma::fmat delta_a,int d,std::list<int> C,std::list<int> NC);
	bool AllAccelerationZeroLess(arma::fmat);
	bool ValueInList(std::list<int> N,int j);
	void StartNewActiveCollisionList(unsigned int);
	void LoadIntoActiveCollisionList(unsigned int);
	std::vector<SATData> CCD;
	std::vector<SATData> collisionData;
	std::vector<SATData> ActiveCollisionList;
	std::vector<std::vector<SATData>> collisionGroups;
	std::vector<compositePhysobj *> CollisionObjects;
};
