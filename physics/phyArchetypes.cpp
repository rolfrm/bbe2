#include "phyArchetypes.h"
#include "../toolModule.h"
#include <iostream>
#include <string>


rigidBody::rigidBody(float mass_in,float kimu_in,float statmu_in,float e_in){
	mass=mass_in;
	kimu=kimu_in;
	statmu=statmu_in;
	e=e_in;
	inertia = mass_in*100000;
}

rigidBody::~rigidBody(){

}

basePhy::basePhy(float x,float y){
	Velocity.null();
	PrePos.null();
	Pos.setXY(x,y);
	angle=0;
	angleSpeed=0;
}

polygonFrame::polygonFrame(){
	AxisCalculated=false;
	RAABCalculated=false;
	periphial=0;
	AAAB[0].null();
	AAAB[1].null();
	RAAB[0].null();
	RAAB[1].null();
}
polygonFrame::~polygonFrame(){
	vertex.clear();
	axis.clear();
	/*
	delete AAAB[0];
	delete AAAB[1];
	delete RAAB[0];
	delete RAAB[1];
	*/
}
void polygonFrame::onCollision(baseFrame * other){

}

void polygonFrame::AddVertex(float x,float y){
	vertex.push_back(Vector2D(x,y));
	if ((--vertex.end())->length()>periphial){
		periphial=(--vertex.end())->length();
		AAAB[0].x=-periphial;
		AAAB[0].y=-periphial;
		AAAB[1].x=periphial;
		AAAB[1].y=periphial;
	}
}

void polygonFrame::AddVertex(Vector2D candidate){
	vertex.push_back(candidate);
	if(candidate.length()>periphial){
		periphial=candidate.length();
		AAAB[0].x=-periphial;
		AAAB[0].y=-periphial;
		AAAB[1].x=periphial;
		AAAB[1].y=periphial;
	}
}

void polygonFrame::CalculateAxis(){
	axis.clear();
	Vector2D carrier(0,0);
	std::list<Vector2D>::iterator it,itend,itu,itendu;
	itendu=vertex.end();
	itendu--;
	for(it=vertex.begin(),itend=vertex.end();it!=itend;it++){
		itu=it;
		itu++;
		//it->print();
		//itu->print();
		if(itu==itend){
			//std::cout<<"meh\n";
			carrier=*(itendu);
			carrier-=*vertex.begin();
			//carrier.print();
			carrier.normalize();
			carrier.rotate90();
			//carrier.print();
			axis.push_back(carrier.copy());
		}
		else{
//			std::cout<<"shizzle\n";

			carrier=*it;
			carrier-=*(itu);
			//carrier.print();
			carrier.normalize();
			//carrier.print();
			carrier.rotate90();
			axis.push_back(carrier.copy());
		}
	//	std::cout<<"\n";

	}
	//parent->Base->Pos->print();
	//PrintVertex();
	//PrintAxis();
}

void polygonFrame::PrintVertex(){
	std::list<Vector2D>::iterator it,itend;
	std::cout<<"vertex:\n";
	for(it=vertex.begin(),itend=vertex.end();it!=itend;it++){
		(*it).print();
	}
	std::cout<<"\n";
}

void polygonFrame::PrintAxis(){
	std::list<Vector2D>::iterator it,itend;
	std::cout<<"axis:\n";
	for(it=axis.begin(),itend=axis.end();it!=itend;it++){
		(*it).print();
	}
	std::cout<<"\n";
}

void polygonFrame::PrintRAAB(){
	std::cout<<"RAAB :\n";
	RAAB[0].print();
	RAAB[1].print();
	std::cout<<"\n";
}

void polygonFrame::EmptyVertex(){
	vertex.clear();
}

void polygonFrame::CalculateRelativeAxisAlignedBox(){
	//std::cout<<"hejehjehj\n";
	float maxX,minX,maxY,minY;
	bool first=false;
	std::list<Vector2D>::iterator it,itend;
	for(it=vertex.begin(),itend=vertex.end();it!=itend;it++){
		if(!first){
			maxX=it->x;
			minX=it->x;
			maxY=it->y;
			minY=it->y;
			first=true;
		}
		if(maxX<it->x){
			maxX=it->x;
		}
		if(minX>it->x){
			minX=it->x;
		}
		if(maxY<it->y){
			maxY=it->y;
		}
		if(minY>it->y){
			minY=it->y;
		}
	}
	RAAB[0].x=minX;
	RAAB[0].y=minY;
	RAAB[1].x=maxX;
	RAAB[1].y=maxY;
}

PolygonframeFactory::PolygonframeFactory(){

}
/*
void PolygonframeFactory::manufacture(design_scheme * ds){
	std::list<std::string>::iterator it,itend;
	//std::string test="hejhej";
	for (it=ds->values->begin(),itend=ds->values->end();it!=itend;it++){
			std::cout<<*it<<"\n";

	}
}
*/

circularFrame::circularFrame(){
	Center.null();
	radius=0;
}

circularFrame::circularFrame(float radius_in,float centerx,float centery){
	Center.setXY(centerx,centery);
	radius=radius_in;
}

void circularFrame::onCollision(baseFrame * other){

}

Spring::Spring(float springConst,float rest){
	springConstant=springConst;
	restLength=rest;
}

void Spring::SetFirstActachment(compositePhysobj * obj){
	obj1=obj;
}

void Spring::SetSecondActachment(compositePhysobj * obj){
	obj2=obj;
}

void Spring::ApplySpringForce(){
	Vector2D displacement,force;
	float x=-restLength;
	displacement=obj2->Base->Pos;
	displacement-=obj1->Base->Pos;
	force=displacement.produceNormalized();
	x+=displacement.length();
	force*=x;
	force*=springConstant;

}

rigidBody * rigidBody::copy(){
	rigidBody * temp;
	temp=new rigidBody(mass,kimu,statmu,e);
	temp->inertia=inertia;
	temp->density=density;
	temp->Force=Force;
	temp->Torque=Torque;
	return temp;
}

basePhy * basePhy::copy(){
	basePhy * temp=new basePhy(Pos.x,Pos.y);
	temp->Velocity=Velocity;
	temp->PrePos=PrePos;
	temp->angleSpeed=angleSpeed;
	temp->angle=angle;
	return temp;
}

polygonFrame * polygonFrame::copy(){
	polygonFrame * temp= new polygonFrame;
	temp->vertex=vertex;
	return temp;
}
