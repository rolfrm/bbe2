//#include "CollisionHandler.h"
#include <iostream>
#include <armadillo>
#include "physics_core.h"
#include "../sprite.h"

CollisionRespone::CollisionRespone(){
}

void CollisionRespone::reset(){
	collisionData.clear();
	CCD.clear();
	CollisionObjects.clear();
	collisionGroups.clear();
}

void CollisionRespone::run(){
	unsigned int i;
	findNeighbour();

	std::list<compositePhysobj *>::iterator it;
	for(it=parent->objects.begin();it!=parent->objects.end();it++){
		if((*it)->hasRigid){
			for(i=0;i<(*it)->CollsionContacts.size();i++){
				DataCarrier=(*it)->CollsionContacts[i];
				ImpulseResponse(DataCarrier.obj1,DataCarrier.obj2);
				Friction(DataCarrier.obj1,DataCarrier.obj2);
			}
		}
	}
	/*
	for(i=0;i<collisionGroups.size();i++){
		ActiveCollisionList=collisionGroups[i];
		ContactForceResponse();
	}
	*/
}

void CollisionRespone::AddCollisionData(SATData candidate){
	collisionData.push_back(candidate);
}

bool CollisionRespone::HandleCollision(){
	unsigned int i;
	Vector2D temp;
	float projected_velocity;
	for(i=0;i<CCD.size();i++){
		DataCarrier=CCD[i];
		temp=DataCarrier.obj1->getVelocity();
		temp-=DataCarrier.obj2->getVelocity();
		projected_velocity=fabs(temp*DataCarrier.CollisionAxis);
		if(projected_velocity>1){
			return false;
		}
	}
	return true;
}

void CollisionRespone::findNeighbour(){
	std::list<compositePhysobj *>::iterator itObj;
	for(itObj=parent->objects.begin();itObj!=parent->objects.end();itObj++){
		if((*itObj)->hasRigid && (*itObj)->CollsionContacts.size()!=0){
			CollisionObjects.push_back((*itObj));
		}
	}
	while(CollisionObjects.size()!=0){
		StartNewActiveCollisionList(0);
		collisionGroups.push_back(ActiveCollisionList);
	}
}

void CollisionRespone::StartNewActiveCollisionList(unsigned int entry){
	ActiveCollisionList.clear();
	LoadIntoActiveCollisionList(entry);

}

void CollisionRespone::LoadIntoActiveCollisionList(unsigned int entry){
	unsigned int i,j;
	for(i=0;i<CollisionObjects[entry]->CollsionContacts.size();i++){
		ActiveCollisionList.push_back(CollisionObjects[entry]->CollsionContacts[i]);
	}
	CollisionObjects.erase(CollisionObjects.begin()+entry);
	for(i=0;i<ActiveCollisionList.size();i++){
		for(j=0;j<CollisionObjects.size();j++){
			if(ActiveCollisionList[i].obj2==CollisionObjects[j]){
				LoadIntoActiveCollisionList(j);
				break;
			}
		}
	}
}

void CollisionRespone::ImpulseResponse(compositePhysobj * obj1, compositePhysobj * obj2){
	if (obj1->phyBody->mass!=0 && obj2->phyBody->mass!=0){
		Vector2D axis=DataCarrier.CollisionAxis,Seperator = DataCarrier.SeperatingVector,r1=DataCarrier.ContactPoint,r2=DataCarrier.ContactPoint;
		Seperator/=2.0;
		float e;
		e=sqrt(obj1->phyBody->e*obj2->phyBody->e);
		r1-=obj1->Base->Pos;
		r2-=obj2->Base->Pos;
		Vector2D DiffVelocity,TotVelocity1(-obj1->Base->angleSpeed*r1.y,obj1->Base->angleSpeed*r1.x),TotVelocity2(-obj2->Base->angleSpeed*r2.y,obj2->Base->angleSpeed*r2.x);
		TotVelocity1+=obj1->Base->Velocity;
		TotVelocity2+=obj2->Base->Velocity;
		DiffVelocity=TotVelocity1;
		DiffVelocity-=TotVelocity2;
		float j=(-(1+e)*(DiffVelocity*axis)/(1/obj1->phyBody->mass+1/obj2->phyBody->mass+(r1.x*axis.y-r1.y*axis.x)*(r1.x*axis.y-r1.y*axis.x)/obj1->phyBody->inertia+(r2.x*axis.y-r2.y*axis.x)*(r2.x*axis.y-r2.y*axis.x)/obj2->phyBody->inertia));
		DataCarrier.j=j;
		obj1->HandleCollision(Seperator,j,r1,axis);
		Seperator*=-1;
		obj2->HandleCollision(Seperator,-j,r2,axis);
	}
	else if(obj1->phyBody->mass!=0 || obj2->phyBody->mass!=0){
		float e=(obj1->phyBody->e+obj2->phyBody->e)/2.0;
		compositePhysobj * obj,* infobj;
		Vector2D r=DataCarrier.ContactPoint,Seperator=DataCarrier.SeperatingVector,axis=DataCarrier.CollisionAxis;
		//Seperator*1.01;
		if (obj1->phyBody->mass!=0){
			obj=obj1;
			infobj=obj2;
			//*obj->Base->Pos+DataCarrier.SeperatingVector;
			//obj->ChangePos(*DataCarrier.SeperatingVector);
		}
		else{
			obj=obj2;
			infobj=obj1;
			//*obj->Base->Pos-DataCarrier.SeperatingVector;
			Seperator*=-1;
			//obj->ChangePos(Seperator);
		}
	//	std::cout<<"så sdtarter vi \n";
		//obj->Base->Velocity->print();
		r-=obj->Base->Pos;
		Vector2D Velocity_tot(0,0),Velocity_obj(-obj->Base->angleSpeed*r.y,obj->Base->angleSpeed*r.x);
		Velocity_obj+=obj->Base->Velocity;
		if (obj==obj1){
			Velocity_tot+=Velocity_obj;
		}
		else{
			Velocity_tot-=Velocity_obj;
		}
		float j;
		//std::cout<< "data: "<<e<<" "<<obj->phyBody->inertia<<" "<<obj<<"\n";
		j=(-(1+e)*(Velocity_tot*axis))/(1/obj->phyBody->mass+r.Crossproduct(axis)*r.Crossproduct(axis)/obj->phyBody->inertia);
		//std::cout<<"j inf "<<j<<" "<<j/obj->phyBody->mass<<"\n";
		//obj2->Base->Velocity.print();
		//axis=DataCarrier.SeperatingVector->produceNormalized();
		DataCarrier.j=j;
		if (obj==obj1){
			obj->HandleCollision(Seperator,j,r,axis);
			/*
			obj->Base->Velocity->x+=j*axis.x/obj->phyBody->mass;
			obj->Base->Velocity->y+=j*axis.y/obj->phyBody->mass;
			obj->Base->angleSpeed+=(r.x*j*axis.y-r.y*j*axis.x)/obj->phyBody->inertia;
			*/
		}
		else{
			obj->HandleCollision(Seperator,-j,r,axis);
			/*
			obj->Base->Velocity->x-=j*axis.x/obj->phyBody->mass;
			obj->Base->Velocity->y-=j*axis.y/obj->phyBody->mass;
			obj->Base->angleSpeed-=(r.x*j*axis.y-r.y*j*axis.x)/obj->phyBody->inertia;
			*/

		}

	}
}

void CollisionRespone::ContactForceResponse(){
	std::list<int> C,NC;
	int d=0;
	ReturnData sj;
	arma::fmat A,a,b,f(ActiveCollisionList.size(),1),df,da;
	f.zeros();
	A=CalculateMatrixA();
	b=CalculateMatrixB();
	a=b;
	std::cout<<"here A\n"<<A<<"\n";
//	std::cout<<"here a start\n"<<a<<"\n";
	std::cout<<"start\n";
	while(AllAccelerationZeroLess(a)){
		while(1){
			std::cout<<d<<" loop\n";
			std::cout<<"a her\n"<<a;
			std::cout<<"f er her\n"<<f;
			df=fdirection(d,A,C);
			da=A*df;
			sj=maxStep(f,a,df,da,d,C,NC);
			f+=sj.s*df;
			a+=sj.s*da;
			//std::cout<<"loop\n";
			//std::cout<<"here da\n"<<da<<"\n";
			//std::cout<<"med s "<<sj.s<<"\n";
			if(ValueInList(C,sj.j)){
				C.remove(sj.j);
				NC.push_back(sj.j);
			}
			else if(ValueInList(NC,sj.j)){
				NC.remove(sj.j);
				C.push_back(sj.j);
			}
			else{
				C.push_back(sj.j);
				break;
			}
		}
		d++;
		//std::cout<<"\n";
	}
	std::cout<<"a slut her\n"<<a;
	std::cout<<"heres f\n"<<f<<"\n";
	std::cout<<"slut\n";
	//std::cout<<"here a slut\n"<<a<<"\n";
	Vector2D r1,r2,n,sep;
	for(int i=0;i<ActiveCollisionList.size();i++){
		//std::cout<<f(i,0)<<" applying to "<<ActiveCollisionList[i].obj1->parent->id<<" and "<<ActiveCollisionList[i].obj1->parent->id<<"\n";
		r1=ActiveCollisionList[i].ContactPoint;
		r2=r1;
		r1-=ActiveCollisionList[i].obj1->getPosition();
		r2-=ActiveCollisionList[i].obj2->getPosition();
		n=ActiveCollisionList[i].CollisionAxis;
		if(ActiveCollisionList[i].axis_from==2){
			n*=-1;
		}
		sep=ActiveCollisionList[i].SeperatingVector;
		//sep.null();
		if(ActiveCollisionList[i].obj2->getMass()!=0){
			sep/=2;
			ActiveCollisionList[i].obj1->HandleCollision(sep,f(i,0),r1,n);
			sep*=-1;
			ActiveCollisionList[i].obj2->HandleCollision(sep,-f(i,0),r2,n);
		}
		else{
			ActiveCollisionList[i].obj1->HandleCollision(sep,f(i,0),r1,n);
		}
	}
}

bool CollisionRespone::ValueInList(std::list<int> N,int j){
	std::list<int>::iterator it;
	for(it=N.begin();it!=N.end();it++){
		if(*it==j){
			return true;
		}
	}
	return false;
}

ReturnData CollisionRespone::maxStep(arma::fmat f,arma::fmat a,arma::fmat df,arma::fmat da,int d,std::list<int> C,std::list<int> NC){
	/*
	std::cout<<"matrix f\n"<<f<<"\n";
	std::cout<<"matrix a\n"<<a<<"\n";
	std::cout<<"matrix df\n"<<df<<"\n";
	std::cout<<"matrix da\n"<<da<<"\n";
	std::cout<<"d "<<d<<"\n";
	std::cout<<"C "<<C.size()<<"\n";
	std::cout<<"NC "<<NC.size()<<"\n";
	*/
	float temp;
	std::list<int>::iterator it;
	ReturnData Return;
	bool first=true;
	if(da(d,0)>0){
		//std::cout<<"yes yes\n";
		first=false;
		Return.j=d;
		Return.s=-a(d,0)/da(d,0);
	}
	for(it=C.begin();it!=C.end();it++){
		if(df(*it,0)<0){
			temp=-f(*it,0)/df(*it,0);
			if(temp<Return.s || first){
				first=false;
				Return.s=temp;
				Return.j=*it;
			}
		}
	}
	for(it=NC.begin();it!=NC.end();it++){
		if(da(*it,0)<0){
			temp=-a(*it,0)/da(*it,0);
			if(temp<Return.s || first){
				first=false;
				Return.s=temp;
				Return.j=*it;
			}
		}
	}
	//std::cout<<"return s="<<Return.s<<" j="<<Return.j<<"\n";
	return Return;
}

arma::fmat CollisionRespone::fdirection(int d,arma::fmat A,std::list<int> C){
	int i=0,j=0;
	arma::fmat delta_f(ActiveCollisionList.size(),1),V1(C.size(),1),A_11(C.size(),C.size()),X;
	delta_f.zeros();
	delta_f(d,0)=1;
//	std::cout<<"matrix delta_f\n"<<delta_f<<"\n";
	if(C.size()!=0){

		for(std::list<int>::iterator it=C.begin();it!=C.end();it++){
			j=0;
			for(std::list<int>::iterator it2=C.begin();it2!=C.end();it2++){
				//std::cout<<"A_11 accesing "<<*it<<","<<*it2<<" at "<<i<<","<<j<<"\n";
				A_11(i,j)=A(*it,*it2);
				j++;
			}
			V1(i,0)=A(*it,d);
			i++;
		}
		X=-inv(A_11)*V1;
		i=0;
	//	std::cout<<"matrix x"<<X<<"\n";
		for(std::list<int>::iterator it=C.begin();it!=C.end();it++){
		//	std::cout<<"inserting into "<<*it<<"\n";
			delta_f(*it,0)=X(i,0);
			i++;
		}
	}
	//std::cout<<"matrix delta_f\n"<<delta_f<<"\n";
	return delta_f;
}

bool CollisionRespone::AllAccelerationZeroLess(arma::fmat a){
	for(unsigned int i;i<ActiveCollisionList.size();i++){
		if(a(i,0)<-0.005){
			return true;
		}
	}
	return false;
}


arma::fmat CollisionRespone::CalculateMatrixA(){
	arma::fmat A(ActiveCollisionList.size(),ActiveCollisionList.size());
	A.zeros();
	unsigned int i,j;
	compositePhysobj * mainObj;
	Vector2D MainCollisionAxis,AffectingCollisionAxis,MainArm,AffectingArm;
	float x,y,z;
	for(i=0;i<ActiveCollisionList.size();i++){
		for(j=0;j<ActiveCollisionList.size();j++){
			if(j!=i){
				if(ActiveCollisionList[i].obj1==ActiveCollisionList[j].obj1 || ActiveCollisionList[i].obj2==ActiveCollisionList[j].obj1){
					if(ActiveCollisionList[i].obj1==ActiveCollisionList[j].obj1){
						mainObj=ActiveCollisionList[i].obj1;
					}
					else{
						mainObj=ActiveCollisionList[i].obj2;
					}
					MainCollisionAxis=ActiveCollisionList[i].CollisionAxis;
					if(ActiveCollisionList[i].axis_from==2){
						MainCollisionAxis*=-1;
					}
					AffectingCollisionAxis=ActiveCollisionList[j].CollisionAxis;
					if(ActiveCollisionList[j].axis_from==2){
						AffectingCollisionAxis*=-1;
					}
					MainArm=ActiveCollisionList[i].ContactPoint-mainObj->getPosition();
					AffectingArm=ActiveCollisionList[j].ContactPoint-mainObj->getPosition();
					x=MainArm.x,y=MainArm.y,z=AffectingArm.Crossproduct(AffectingCollisionAxis);
					A(i,j)=MainCollisionAxis*(AffectingCollisionAxis/mainObj->getMass()+Vector2D(-y*z,x*z)/mainObj->getInertia());
				}
				else if(ActiveCollisionList[i].obj1==ActiveCollisionList[j].obj2 || ActiveCollisionList[i].obj2==ActiveCollisionList[j].obj2){
					if(ActiveCollisionList[i].obj1==ActiveCollisionList[j].obj2){
						mainObj=ActiveCollisionList[i].obj1;
					}
					else{
						mainObj=ActiveCollisionList[i].obj2;
					}
					if(mainObj->getMass()!=0){
						MainCollisionAxis=ActiveCollisionList[i].CollisionAxis;
						AffectingCollisionAxis=ActiveCollisionList[j].CollisionAxis;
						MainArm=ActiveCollisionList[i].ContactPoint-mainObj->getPosition();
						AffectingArm=ActiveCollisionList[j].ContactPoint-mainObj->getPosition();
						x=MainArm.x,y=MainArm.y,z=AffectingArm.Crossproduct(AffectingCollisionAxis);
						if(ActiveCollisionList[i].axis_from==2){
							MainCollisionAxis*=-1;
						}
						if(ActiveCollisionList[j].axis_from==1){
							AffectingCollisionAxis*=-1;
						}
						A(i,j)=-1*(MainCollisionAxis*(AffectingCollisionAxis/mainObj->getMass()+Vector2D(-y*z,x*z)/mainObj->getInertia()));
					}
				}
			}
			else{
				mainObj=ActiveCollisionList[i].obj1;
				MainCollisionAxis=ActiveCollisionList[i].CollisionAxis;
				AffectingCollisionAxis=ActiveCollisionList[j].CollisionAxis;
				MainArm=ActiveCollisionList[i].ContactPoint-ActiveCollisionList[i].obj1->getPosition();
				AffectingArm=ActiveCollisionList[j].ContactPoint-ActiveCollisionList[i].obj1->getPosition();
				x=MainArm.x,y=MainArm.y,z=AffectingArm.Crossproduct(AffectingCollisionAxis);
				if(ActiveCollisionList[i].axis_from=2){
					MainCollisionAxis*=-1;
				}
				if(ActiveCollisionList[j].axis_from==2){
					AffectingCollisionAxis*=-1;
				}
				A(i,j)=(MainCollisionAxis*(AffectingCollisionAxis/mainObj->getMass()+Vector2D(-y*z,x*z)/mainObj->getInertia()));
				if(ActiveCollisionList[i].obj2->getMass()!=0){
					A(i,j)*=2;
				}
			}
		}
	}
	return A;
}


/*
arma::fmat CollisionRespone::CalculateMatrixA(){
	arma::fmat A(ActiveCollisionList.size(),ActiveCollisionList.size());
	A.zeros();
	unsigned int i,j;
	compositePhysobj * mainObj;
	Vector2D MainCollisionAxis,AffectingCollisionAxis,MainArm,AffectingArm;
	float x,y,z;
	for(i=0;i<ActiveCollisionList.size();i++){
		for(j=0;j<ActiveCollisionList.size();j++){
			if(j!=i){
				if(ActiveCollisionList[i].obj1==ActiveCollisionList[j].obj1 || ActiveCollisionList[i].obj1==ActiveCollisionList[j].obj2){
					mainObj=ActiveCollisionList[i].obj1;
					MainCollisionAxis=ActiveCollisionList[i].CollisionAxis;
					if(ActiveCollisionList[i].axis_from==2){
						MainCollisionAxis*=-1;
					}
					AffectingCollisionAxis=ActiveCollisionList[j].CollisionAxis;
					if(ActiveCollisionList[j].axis_from==2){
						AffectingCollisionAxis*=-1;
					}
					MainArm=ActiveCollisionList[i].ContactPoint-ActiveCollisionList[i].obj1->getPosition();
					AffectingArm=ActiveCollisionList[j].ContactPoint-ActiveCollisionList[i].obj1->getPosition();
					x=MainArm.x,y=MainArm.y,z=AffectingArm.Crossproduct(AffectingCollisionAxis);
					A(i,j)=MainCollisionAxis*(AffectingCollisionAxis/mainObj->getMass()+Vector2D(-y*z,x*z)/mainObj->getInertia());
				}
				else if(ActiveCollisionList[i].obj2==ActiveCollisionList[j].obj1 || ActiveCollisionList[i].obj2==ActiveCollisionList[j].obj2){
					mainObj=ActiveCollisionList[i].obj2;
					if(mainObj->getMass()!=0){
						MainCollisionAxis=ActiveCollisionList[i].CollisionAxis;
						AffectingCollisionAxis=ActiveCollisionList[j].CollisionAxis;
						MainArm=ActiveCollisionList[i].ContactPoint-ActiveCollisionList[i].obj2->getPosition();
						AffectingArm=ActiveCollisionList[j].ContactPoint-ActiveCollisionList[i].obj2->getPosition();
						x=MainArm.x,y=MainArm.y,z=AffectingArm.Crossproduct(AffectingCollisionAxis);
						if(ActiveCollisionList[i].axis_from==2){
							MainCollisionAxis*=-1;
						}
						if(ActiveCollisionList[j].axis_from==2){
							AffectingCollisionAxis*=-1;
						}
						A(i,j)=-1*(MainCollisionAxis*(AffectingCollisionAxis/mainObj->getMass()+Vector2D(-y*z,x*z)/mainObj->getInertia()));
					}
				}
			}
			else{
				mainObj=ActiveCollisionList[i].obj1;
				MainCollisionAxis=ActiveCollisionList[i].CollisionAxis;
				AffectingCollisionAxis=ActiveCollisionList[j].CollisionAxis;
				MainArm=ActiveCollisionList[i].ContactPoint-ActiveCollisionList[i].obj1->getPosition();
				AffectingArm=ActiveCollisionList[j].ContactPoint-ActiveCollisionList[i].obj1->getPosition();
				x=MainArm.x,y=MainArm.y,z=AffectingArm.Crossproduct(AffectingCollisionAxis);
				if(ActiveCollisionList[i].axis_from=2){
					MainCollisionAxis*=-1;
				}
				if(ActiveCollisionList[j].axis_from==2){
					AffectingCollisionAxis*=-1;
				}
				A(i,j)=(MainCollisionAxis*(AffectingCollisionAxis/mainObj->getMass()+Vector2D(-y*z,x*z)/mainObj->getInertia()));
				if(ActiveCollisionList[i].obj2->getMass()!=0){
					A(i,j)*=2;
				}
			}
		}
	}
	return A;
}
*/
arma::fmat CollisionRespone::CalculateMatrixB(){
	arma::fmat b(ActiveCollisionList.size(),1);
	b.zeros();
	Vector3D a1,wa1,r1,w1,a2,wa2,r2,w2,n;
	compositePhysobj * obj1,* obj2;
	for(unsigned int i=0;i<ActiveCollisionList.size();i++){
		obj1=ActiveCollisionList[i].obj1;
		obj2=ActiveCollisionList[i].obj2;
		n=ActiveCollisionList[i].CollisionAxis;
		if(ActiveCollisionList[i].axis_from==2){
			n*=-1;
		}
		a1=obj1->getAccelleration();
		r1=ActiveCollisionList[i].ContactPoint-obj1->getPosition();
		w1=Vector2D(-obj1->Base->angleSpeed*r1.y,obj1->Base->angleSpeed*r1.x);
		a2=obj2->getAccelleration();
		r2=ActiveCollisionList[i].ContactPoint-obj2->getPosition();
		w2=Vector2D(-obj2->Base->angleSpeed*r2.y,obj2->Base->angleSpeed*r2.x);
		wa1*=0;
		wa2*=0;
		b(i,0)=n*(a1+w1.CrossProduct(w1.CrossProduct(r1))-(a2+w2.CrossProduct(w2.CrossProduct(r2))));
		if(obj2->getMass()!=0){
			b(i,0)+=(w2.CrossProduct(n))*(obj1->getVelocity()+w1.CrossProduct(r1)-(obj2->getVelocity()+w2.CrossProduct(r2)))*2;
		}
	}

	return b;

}

void CollisionRespone::Friction(compositePhysobj * obj1, compositePhysobj * obj2){
 	float mu_av=sqrt(obj1->phyBody->kimu*obj2->phyBody->kimu),mu_stat_av=sqrt(obj1->phyBody->statmu*obj2->phyBody->statmu);
	if(obj1->phyBody->mass!=0 && obj2->phyBody->mass!=0){
		Vector2D axis=DataCarrier.CollisionAxis,edge=axis,carrier,r1=DataCarrier.ContactPoint,r2=DataCarrier.ContactPoint;
		edge.rotate90();
		r1-=obj1->Base->Pos;
		r2-=obj2->Base->Pos;
		Vector2D DiffVelocity,TotVelocity1(-obj1->Base->angleSpeed*r1.y,obj1->Base->angleSpeed*r1.x), TotVelocity2(-obj2->Base->angleSpeed*r2.y,obj2->Base->angleSpeed*r2.x);
		TotVelocity1+=obj1->Base->Velocity;
		TotVelocity2+=obj2->Base->Velocity;
		DiffVelocity=TotVelocity2;
		DiffVelocity-=TotVelocity1;
		float Diffedge=DiffVelocity*edge,j=DataCarrier.j,edge1=TotVelocity1*edge,edge2=TotVelocity2*edge;
		if (Diffedge<0){//hvis diffedfe er negativ skal j også være det
			if(j>0){
				j=-j;
			}
		}
		if (Diffedge>0){//hvis diffedge er positiv skal j også være det
			if(j<0){
				j=-j;
			}
		}
		Vector2D Velocity1_post=obj1->Base->Velocity,Velocity2_post=obj2->Base->Velocity,carrier1,carrier2;
		float anglespeed1_post=obj1->Base->angleSpeed,anglespeed2_post=obj2->Base->angleSpeed;
		carrier1=edge;
		carrier1*=j*mu_av;
		//carrier1*mu_av;
		anglespeed1_post+=r1.Crossproduct(carrier1)/obj1->phyBody->inertia;
		carrier1/=obj1->phyBody->mass;
		Velocity1_post+=carrier1;

		carrier2=edge;
		carrier2*=-j*mu_av;
		//carrier2*mu_av;
		anglespeed2_post+=r2.Crossproduct(carrier2)/obj2->phyBody->inertia;
		carrier2/=obj2->phyBody->mass;
		Velocity2_post+=carrier2;

		Vector2D DiffVelocity_post,TotVelocity1_post(-anglespeed1_post*r1.y,anglespeed1_post*r1.x), TotVelocity2_post(-anglespeed2_post*r2.y,anglespeed2_post*r2.x);

		TotVelocity1_post+=Velocity1_post;
		TotVelocity2_post+=Velocity2_post;
		DiffVelocity_post=TotVelocity2_post;
		DiffVelocity_post-=TotVelocity1_post;
		float Diffedge_post=DiffVelocity_post*edge;
		//std::cout<<Diffedge<<" "<<Diffedge_post<<" meh\n";
		if(Diffedge*Diffedge_post<=0){

			float c=(-obj2->getAnglespeed()*(r2.produceRotated90()*edge)+obj1->getAnglespeed()*(r1.produceRotated90()*edge)-(obj2->getVelocity()*edge)+(obj1->getVelocity()*edge))/(r2.Crossproduct(edge)*(r2.produceRotated90()*edge)/obj2->getInertia()+r1.Crossproduct(edge)*(r1.produceRotated90()*edge)/obj1->getInertia()+1/obj1->getMass()+1/obj2->getMass());
			carrier=edge;
			carrier*=c;
			obj2->ApplyForce(carrier,r2);
			carrier*=-1;
			obj1->ApplyForce(carrier,r1);
		}
		else{
			carrier=edge;
			carrier*=j*mu_av;
			 //carrier*mu_av;
			obj1->ApplyForce(carrier,r1);
			carrier=edge;
			carrier*=-j*mu_av;
			//carrier*mu_av;
			obj2->ApplyForce(carrier,r2);
		}
		TotVelocity1.setXY(-obj1->Base->angleSpeed*r1.y,obj1->Base->angleSpeed*r1.x);
		TotVelocity2.setXY(-obj2->Base->angleSpeed*r2.y,obj2->Base->angleSpeed*r2.x);
		TotVelocity1+=obj1->Base->Velocity;
		TotVelocity2+=obj2->Base->Velocity;
		DiffVelocity=TotVelocity2;
		DiffVelocity-=TotVelocity1;
		if(fabs(DiffVelocity*edge)<1){
			carrier=edge;
			carrier*=-j*mu_stat_av;
			//carrier*mu_stat_av;
			obj2->HandleStaticFriction(carrier);
			obj1->HandleStaticFriction(carrier);
		}
	}
	else if(obj1->phyBody->mass!=0 || obj2->phyBody->mass!=0){
		float j=DataCarrier.j;
		compositePhysobj * temp;
		if(obj1->phyBody->mass!=0){ // hvis obj2 har uendelig masse sættes obj1 til være obj2 og visa verca
			temp=obj2;
			obj2=obj1;
			obj1=temp;
			j=-j;
		}
		Vector2D axis=DataCarrier.CollisionAxis,edge=axis,carrier,r1=DataCarrier.ContactPoint,r2=DataCarrier.ContactPoint;
		edge.rotate90();
		r1-=obj1->Base->Pos;
		r2-=obj2->Base->Pos;
		Vector2D DiffVelocity,TotVelocity1(-obj1->Base->angleSpeed*r1.y,obj1->Base->angleSpeed*r1.x), TotVelocity2(-obj2->Base->angleSpeed*r2.y,obj2->Base->angleSpeed*r2.x);
		TotVelocity1+=obj1->Base->Velocity;
		TotVelocity2+=obj2->Base->Velocity;
		DiffVelocity=TotVelocity2;
		DiffVelocity-=TotVelocity1;
		float Diffedge=DiffVelocity*edge,edge1=TotVelocity1*edge,edge2=TotVelocity2*edge;
		if (Diffedge<0){//hvis diffedfe er negativ skal j også være det
			if(j>0){
				j=-j;
			}
		}
		if (Diffedge>0){//hvis diffedge er positiv skal j også være det
			if(j<0){
				j=-j;
			}
		}
		Vector2D Velocity1_post=obj1->Base->Velocity,Velocity2_post=obj2->Base->Velocity,carrier1,carrier2;
		float anglespeed1_post=obj1->Base->angleSpeed,anglespeed2_post=obj2->Base->angleSpeed;

		carrier2=edge;
		carrier2*=-j*mu_av;
		//carrier2*mu_av;
		anglespeed2_post+=r2.Crossproduct(carrier2)/obj2->phyBody->inertia;
		carrier2/=obj2->phyBody->mass;
		Velocity2_post+=carrier2;

		Vector2D DiffVelocity_post,TotVelocity1_post(-anglespeed1_post*r1.y,anglespeed1_post*r1.x), TotVelocity2_post(-anglespeed2_post*r2.y,anglespeed2_post*r2.x);

		TotVelocity1_post+=Velocity1_post;
		TotVelocity2_post+=Velocity2_post;
		DiffVelocity_post=TotVelocity2_post;
		DiffVelocity_post-=TotVelocity1_post;
		float Diffedge_post=DiffVelocity_post*edge;
		if(Diffedge*Diffedge_post<=0){
			float c=(-obj2->getAnglespeed()*(r2.produceRotated90()*edge)+obj1->getAnglespeed()*(r1.produceRotated90()*edge)-(obj2->getVelocity()*edge)+(obj1->getVelocity()*edge))/(r2.Crossproduct(edge)*(r2.produceRotated90()*edge)/obj2->getInertia()+1/obj2->getMass());;
			carrier=edge;
			carrier*=c;
			obj2->ApplyForce(carrier,r2);
		}
		else{
			carrier=edge;
			carrier*=-j*mu_av;
			//carrier*mu_av;
			obj2->ApplyForce(carrier,r2);

		}
		TotVelocity1.setXY(-obj1->Base->angleSpeed*r1.y,obj1->Base->angleSpeed*r1.x);
		TotVelocity2.setXY(-obj2->Base->angleSpeed*r2.y,obj2->Base->angleSpeed*r2.x);
		TotVelocity1+=obj1->Base->Velocity;
		TotVelocity2+=obj2->Base->Velocity;
		DiffVelocity=TotVelocity2;
		DiffVelocity-=TotVelocity1;
		if(fabs(DiffVelocity*edge)<1){
			carrier=edge;
			carrier*=-j*mu_stat_av;
			//carrier*mu_stat_av;
			obj2->HandleStaticFriction(carrier);
		}
	}
}
