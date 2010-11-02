#include "compositePhysobj.h"
#include "../toolModule.h"
#include "phyArchetypes.h"
#include "physics_core.h"
#include <iostream>
#include <math.h>
compositePhysobj::compositePhysobj(float x, float y):eventSlave("body") {
	Base = new basePhy(x, y);
	hasEvent = false;
	hasRigid = false;
	rotable = true;
	stat=false;
	phyBody = NULL;
	ui_element = false;
}

compositePhysobj::compositePhysobj(Vector2D pos):eventSlave("body") {
	Base = new basePhy(pos.x, pos.y);
	hasEvent = false;
	hasRigid = false;
	rotable = true;
	stat=false;
	phyBody = NULL;
}

compositePhysobj::~compositePhysobj() {

}

void compositePhysobj::Rotate(float time) {
	std::list<polygonFrame>::iterator it, itend;
	std::list<Vector2D>::iterator vit, vitend;
	//std::cout<<"her er vinkel :"<<Base->angle<<" "<<Base->angleSpeed<<"\n";
	if (fabs(Base->angleSpeed) > 0.036 || true) {
		Base->angle += Base->angleSpeed / PhySteps;
		if (hasEvent) {
			for (it = eventFrame.begin(), itend = eventFrame.end(); it != itend; it++) {
				for (vit = it->vertex.begin(), vitend = it->vertex.end(); vit
						!= vitend; vit++) {
					*vit -= Base->Pos;
					vit->rotate(Base->angleSpeed / PhySteps);
					*vit += Base->Pos;

				}
			}
		}
		if (hasRigid) {
			for (it = phyFrame.begin(), itend = phyFrame.end(); it != itend; it++) {
				for (vit = it->vertex.begin(), vitend = it->vertex.end(); vit
						!= vitend; vit++) {
					*vit -= Base->Pos;
					vit->rotate(Base->angleSpeed / PhySteps);
					*vit += Base->Pos;
				}
			}
		}
		//	*Base->PrePos=Base->Pos;
	} else {
		Base->angleSpeed=0;
	}
}

void compositePhysobj::Move(float time) {
	std::list<polygonFrame>::iterator it, itend;
	std::list<Vector2D>::iterator vit, vitend;
	Vector2D tempVel(0, 0);
	AnalyzeForces();
	/*
	if (phyBody->mass != 0) {
		Base->Velocity + gravity;
		phyBody->Force / phyBody->mass;
		Base->Velocity + phyBody->Force;
		phyBody->Force.null();
		phyBody->Force + gravity;
		phyBody->Force * phyBody->mass;
	}
	*/
	//std::cout<<"e "<<phyBody->e<<"\n";

	tempVel = Base->Velocity;
	/*
	if(fabs(tempVel.x)<0.1){
		tempVel.x=0;
	}
	else if(fabs(tempVel.y)<0.1){
		tempVel.x=0;
	}
	*/
	//tempVel.print();
	tempVel /= PhySteps;
	//tempVel.print();
	//std::cout << phyBody->mass << " " << phyBody->inertia << "\n";

	Base->Pos += tempVel;
	if (hasEvent) {
		for (it = eventFrame.begin(), itend = eventFrame.end(); it != itend; it++) {
			for (vit = it->vertex.begin(), vitend = it->vertex.end(); vit
					!= vitend; vit++) {
				*vit -= Base->PrePos;
				*vit += Base->Pos;

			}
		}
	}
	if (hasRigid) {
		for (it = phyFrame.begin(), itend = phyFrame.end(); it != itend; it++) {
			for (vit = it->vertex.begin(), vitend = it->vertex.end(); vit
					!= vitend; vit++) {
				*vit -= Base->PrePos;
				*vit += Base->Pos;
			}
		}
	}
	Base->PrePos = Base->Pos;
	Rotate(1);
	//std::cout<<"\n";
	//std::cout<<"\n";
}

void compositePhysobj::ChangePos(Vector2D V) {
	std::list<polygonFrame>::iterator it, itend;
	std::list<Vector2D>::iterator vit, vitend;
	Base->Pos += V;
	if (hasEvent) {
		for (it = eventFrame.begin(), itend = eventFrame.end(); it != itend; it++) {
			for (vit = it->vertex.begin(), vitend = it->vertex.end(); vit
					!= vitend; vit++) {

				*vit += V;
			}
		}
	}
	if (hasRigid) {
		for (it = phyFrame.begin(), itend = phyFrame.end(); it != itend; it++) {
			for (vit = it->vertex.begin(), vitend = it->vertex.end(); vit
					!= vitend; vit++) {
				*vit += V;
			}
		}
	}
	Base->PrePos = Base->Pos;

	//	std::list<polygonFrame *>::iterator it,itend;
	if (hasEvent) {
		for (it = eventFrame.begin(), itend = eventFrame.end(); it != itend; it++) {
			//	(*it)->AxisCalculated=false;
			it->RAABCalculated = false;
		}
	}
	if (hasRigid) {
		for (it = phyFrame.begin(), itend = phyFrame.end(); it != itend; it++) {
			//	(*it)->AxisCalculated=false;
			it->RAABCalculated = false;
		}
	}
}

void compositePhysobj::SetPos(Vector2D newPos){
	std::list<polygonFrame>::iterator it, itend;
	std::list<Vector2D>::iterator vit, vitend;
	Base->Pos = newPos;
	if (hasEvent) {
		for (it = eventFrame.begin(), itend = eventFrame.end(); it != itend; it++) {
			for (vit = it->vertex.begin(), vitend = it->vertex.end(); vit
					!= vitend; vit++) {

				*vit -= Base->PrePos;
				*vit += newPos;
			}
		}
	}
	if (hasRigid) {
		for (it = phyFrame.begin(), itend = phyFrame.end(); it != itend; it++) {
			for (vit = it->vertex.begin(), vitend = it->vertex.end(); vit
					!= vitend; vit++) {
				*vit -= Base->PrePos;
				*vit += newPos;
			}
		}
	}
	Base->PrePos = Base->Pos;

	//	std::list<polygonFrame *>::iterator it,itend;
	if (hasEvent) {
		for (it = eventFrame.begin(), itend = eventFrame.end(); it != itend; it++) {
			//	(*it)->AxisCalculated=false;
			it->RAABCalculated = false;
		}
	}
	if (hasRigid) {
		for (it = phyFrame.begin(), itend = phyFrame.end(); it != itend; it++) {
			//	(*it)->AxisCalculated=false;
			it->RAABCalculated = false;
		}
	}
}

void compositePhysobj::LoadPhyFrame(polygonFrame * frame) {
	frame->parent = this;
	if (frame->rigid == true) {
		phyFrame.push_back(*frame);
	} else {
		eventFrame.push_back(*frame);
	}
	CalculateMomentofInertia();
}

void compositePhysobj::LoadPhyFrame(polygonFrame* frame, float x, float y) {
	frame->parent = this;
	std::list<Vector2D>::iterator it, itend;
	for (it = frame->vertex.begin(), itend = frame->vertex.end(); it != itend; it++) {
		it->x += x;
		it->y += y;

	}
	if (frame->rigid == true) {
		phyFrame.push_back(*frame);
	} else {
		eventFrame.push_back(*frame);
	}

	CalculateMomentofInertia();
}

void compositePhysobj::LoadPhyFrame(std::list<polygonFrame> frames, float offx,
		float offy) {
	std::list<polygonFrame>::iterator it;
	for (it = frames.begin(); it != frames.end(); it++) {
		LoadPhyFrame(*it, offx, offy);
	}
}

void compositePhysobj::LoadEventFrame(polygonFrame * frame) {
	frame->parent = this;
	eventFrame.push_back(*frame);
	hasEvent = true;
}

void compositePhysobj::LoadEventFrame(polygonFrame* frame, float x, float y) {
	frame->parent = this;
	std::list<Vector2D>::iterator it, itend;
	for (it = frame->vertex.begin(), itend = frame->vertex.end(); it != itend; it++) {
		it->x += x;
		it->y += y;
	}
	eventFrame.push_back(*frame);
	hasEvent = true;
}

void compositePhysobj::LoadRigid(rigidBody * body) {
	phyBody = body;
	hasRigid = true;
	CalculateMomentofInertia();
}

void compositePhysobj::Reset() {
	std::list<polygonFrame>::iterator it, itend;
	if (hasEvent) {
		for (it = eventFrame.begin(), itend = eventFrame.end(); it != itend; it++) {
			it->AxisCalculated = false;
			it->RAABCalculated = false;
		}
	}
	if (hasRigid) {
		for (it = phyFrame.begin(), itend = phyFrame.end(); it != itend; it++) {
			it->AxisCalculated = false;
			it->RAABCalculated = false;
		}
	}
	/*
	CollisionForces.clear();
	CollisionArms.clear();
	KineticFrictionForces.clear();
	KineticFrictionArms.clear();
	StaticFrictionForces.clear();
	*/
	CollisionOffset.null();
	CollsionContacts.clear();
	//Base->angleSpeed=0;
}

void compositePhysobj::CalculateMomentofInertia() {

	if (phyBody != NULL) {

		float fracMass = phyBody->mass / phyFrame.size();
		std::list<polygonFrame>::iterator it, itend;
		std::list<Vector2D>::iterator vitf, vit, vitend;
		float PartInertia, TopFrac, BottomFrac;
		phyBody->inertia = 0;

		for (it = phyFrame.begin(), itend = phyFrame.end(); it != itend; it++) {
			PartInertia = 0, TopFrac = 0, BottomFrac = 0;
			for (vit = it->vertex.begin(), vitend = it->vertex.end(), vitf
					= vit, vitf++; vit != vitend; vit++, vitf++) {
				if (vitf != vitend) {
					TopFrac += ((*vitf).Crossproduct(*vit) * (*vitf * *vitf
							+ *vitf * *vit + *vit * *vit));
					BottomFrac += (*vitf).Crossproduct(*vit);
				} else {
					vitf = it->vertex.begin();
					TopFrac += ((*vitf).Crossproduct(*vit) * (*vitf * *vitf
							+ *vitf * *vit + *vit * *vit));
					BottomFrac += (*vitf).Crossproduct(*vit);
				}
			}
			PartInertia = (fracMass / 6.0) * (TopFrac / BottomFrac);
			phyBody->inertia += PartInertia;
		}

	//std::cout << "her er intertia :" << phyBody->inertia << "\n";
	}
}

void compositePhysobj::PrintPhyFrames() {
	std::list<polygonFrame>::iterator it, itend;
	Base->Pos.print();
	for (it = phyFrame.begin(), itend = phyFrame.end(); it != itend; it++) {
		it->PrintVertex();
		it->PrintAxis();
		it->PrintRAAB();
	}

}

void compositePhysobj::EmptyPhyframes() {
	phyFrame.clear();
}

void compositePhysobj::EmptyEventframes() {
	eventFrame.clear();
}

void compositePhysobj::LoadPhyFrame(polygonFrame candidate) {
	if (candidate.rigid == true) {
		phyFrame.push_back(candidate);
	} else {
		eventFrame.push_back(candidate);
	}
	CalculateMomentofInertia();

}

void compositePhysobj::LoadPhyFrame(polygonFrame candidate, float x, float y) {
	std::list<Vector2D>::iterator it, itend;
	for (it = candidate.vertex.begin(), itend = candidate.vertex.end(); it
			!= itend; it++) {

		it->x += x;
		it->y += y;

	}
	if (candidate.rigid == true) {
		phyFrame.push_back(candidate);
	} else {
		eventFrame.push_back(candidate);
	}
	//std::cout << "size " << phyFrame.size() << "\n";
	//PrintPhyFrames();
	//PrintPhyFrames();
	CalculateMomentofInertia();
}

void compositePhysobj::ApplyForce(Vector2D force) {
	ApplyForce(force,Vector2D(0,0));
}

void compositePhysobj::ApplyForce(Vector2D force,Vector2D arm){
	if (hasRigid) {
	//	std::cout<<"applying force\n";
	//	force.print();
		if (rotable) {
			Base->angleSpeed += arm.Crossproduct(force)/phyBody->inertia;
		}
		force /= phyBody->mass;
		Base->Velocity += force;
	}
}

void compositePhysobj::ApplyGravity(Vector2D gravity){
	Base->Velocity+=gravity;
}

compositePhysobj * compositePhysobj::copy() {
	compositePhysobj * temp;
	temp = new compositePhysobj(Base->Pos);
	temp->phyBody = phyBody->copy();
	temp->phyFrame = phyFrame;
	temp->eventFrame = eventFrame;
	temp->hasRigid = hasRigid;
	temp->hasEvent = hasEvent;
	temp->rotable = rotable;
	temp->id = id;
	temp->parent = parent;
	temp->ui_element = ui_element;
	return temp;
}


void compositePhysobj::HandleCollision(Vector2D offset, float j, Vector2D r,
		Vector2D axis) {
	CollisionOffset+=offset;
	ChangePos(offset);
	axis*=j;
	ApplyForce(axis,r);
}

void compositePhysobj::HandleStaticFriction(Vector2D force){
}

void compositePhysobj::AnalyzeForces(){
	if(phyBody->mass!=0){
		ApplyForce(ApplyStaticFriction(world->gravity*getMass()));
	}


}

Vector2D compositePhysobj::ApplyStaticFriction(Vector2D force){
	unsigned int i;
	float force_projection;
	Vector2D edge;
	return force;
}


bool compositePhysobj::MassInf(){
	if(hasRigid){
		if(phyBody->mass==0){
			return true;
		}
	}
	return false;
}

float compositePhysobj::getMass(){
	if(hasRigid){
		return phyBody->mass;
	}
	return 0;
}

float compositePhysobj::getInertia(){
	if(hasRigid){
		return phyBody->inertia;
	}
	return 0;
}

float compositePhysobj::getAnglespeed(){
	return Base->angleSpeed;
}

Vector2D compositePhysobj::getVelocity(){
	return Base->Velocity;
}

Vector2D compositePhysobj::getAccelleration(){
	if(getMass()!=0){
		Vector2D temp;
		temp=world->globalForce;
		temp/=getMass();
		temp+=world->gravity;
		return temp;
	}
	else{
		return Vector2D(0,0);
	}
}

Vector2D compositePhysobj::getPosition(){
	return Base->Pos;
}

void compositePhysobj::AddCollisionContact(SATData inputData){
	CollsionContacts.push_back(inputData);
}

