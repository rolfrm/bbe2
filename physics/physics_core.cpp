#include "physics_core.h"
#include "phyArchetypes.h"
#include "compositePhysobj.h"
#include "../toolModule.h"
#include <math.h>
#include <iostream>



physicsCore::physicsCore(){

	DataCarrier.SeperatingVector.null();
	DataCarrier.ContactPoint.null();
	DataCarrier.CollisionAxis.null();
	DataCarrier.Collision=false;
	globalForce.null();
	gravity.setXY(0,1);
	CP.parent=this;
}

physicsCore::~physicsCore(){
}


void physicsCore::addObject(compositePhysobj * candidate){
	objects.push_front(candidate);
	candidate->world=this;
}

void physicsCore::removeObject(compositePhysobj * candidate){
	objects.remove(candidate);
}

void physicsCore::collisionDetection(){
	std::list<compositePhysobj *>::iterator it,it2,itend;
	std::list<polygonFrame >::iterator itf,itf2,itfend,itfend2;
	for (it=objects.begin(),itend=objects.end();it!=itend;it++){
		for (it2=it,it2++;it2!=itend;it2++){
	//		std::cout<<"detection "<<*it<<" "<<*it2<<"\n";
			if((*it)->hasRigid){
				for(itf=(*it)->phyFrame.begin(),itfend=(*it)->phyFrame.end();itf!=itfend;itf++){
				//	(*itf)->PrintVertex();

					if((*it2)->hasRigid){
						for(itf2=(*it2)->phyFrame.begin(),itfend2=(*it2)->phyFrame.end();itf2!=itfend2;itf2++){
						if (RAA_SAT(&*itf,&*itf2)){
								SAT(&*itf,&*itf2);
								if (DataCarrier.Collision){
									if((*it)->getMass()!=0){
										DataCarrier.obj1=*it;
										DataCarrier.obj2=*it2;
										(*it)->AddCollisionContact(DataCarrier);
									}
									else{
										DataCarrier.obj2=*it;
										DataCarrier.obj1=*it2;
										DataCarrier.axis_from*=-1;
										DataCarrier.SeperatingVector*=-1;
										if(DataCarrier.axis_from==1){
											DataCarrier.axis_from=2;
										}
										else{
											DataCarrier.axis_from=1;
										}
										(*it2)->AddCollisionContact(DataCarrier);
									}
							}
						}

						}
					}


					if((*it2)->hasEvent){
						for(itf2=(*it2)->eventFrame.begin(),itfend2=(*it2)->eventFrame.end();itf2!=itfend2;itf2++){
						if (RAA_SAT(&*itf,&*itf2)){
							SAT(&*itf,&*itf2);
								if (DataCarrier.Collision){
								}
						}
						}
					}

				}
				for(itf=(*it)->eventFrame.begin(),itfend=(*it)->eventFrame.end();itf!=itfend;itf++){


									if((*it2)->hasRigid){
										for(itf2=(*it2)->phyFrame.begin(),itfend2=(*it2)->phyFrame.end();itf2!=itfend2;itf2++){
											if (RAA_SAT(&*itf,&*itf2)){
												SAT(&*itf,&*itf2);
												if (DataCarrier.Collision){
													(&*itf)->onCollision(&*itf2);
													(&*itf2)->onCollision(&*itf);
												}
											}
										}
									}

									if((*it2)->hasEvent){
										for(itf2=(*it2)->eventFrame.begin(),itfend2=(*it2)->eventFrame.end();itf2!=itfend2;itf2++){
											if (RAA_SAT(&*itf,&*itf2)){
												SAT(&*itf,&*itf2);
												if (DataCarrier.Collision){
													itf->onCollision(&*itf2);
													itf2->onCollision(&*itf);
												}
											}
										}
									}

								}

			}

		}
		}
	//std::cout<<"ny runde\n";

}

void physicsCore::SAT(polygonFrame * frame1,polygonFrame * frame2){
	bool first=true;
	//std::cout<<"Sat starting\n";
//	frame1->PrintVertex();
//	frame2->PrintVertex();
	if (!frame1->AxisCalculated){
		frame1->CalculateAxis();
		frame1->AxisCalculated=true;
	}
	if (!frame2->AxisCalculated){
		frame2->CalculateAxis();
		frame2->AxisCalculated=true;
	}
	std::list<Vector2D>::iterator it,itend,it2,itend2;
	//std::list<float> frame1Projection,frame2Projection,contactlist1,contactlist2;
	float frame1Projection[frame1->vertex.size()],frame2Projection[frame2->vertex.size()],contactlist1[frame1->vertex.size()],contactlist2[frame2->vertex.size()];
	float maxframe1,maxframe2,minframe1,minframe2;
	int i;
	Vector2D candidate1(0,0),candidate2(0,0);
	for (it=frame1->axis.begin(),itend=frame1->axis.end();it!=itend;it++){
		//frame1Projection.clear();
		//frame2Projection.clear();
		//it->print();
		for (it2=frame1->vertex.begin(),itend2=frame1->vertex.end(),i=0;it2!=itend2;it2++,i++){
			//frame1Projection.push_back((*it)*(*it2));
			frame1Projection[i]=(*it)*(*it2);
		}
		for (it2=frame2->vertex.begin(),itend2=frame2->vertex.end(),i=0;it2!=itend2;it2++,i++){
			//frame2Projection.push_back((*it)*(*it2));
			frame2Projection[i]=(*it)*(*it2);
		}
		maxframe1=FindMax(frame1Projection,frame1->vertex.size());
		minframe1=FindMin(frame1Projection,frame1->vertex.size());
		maxframe2=FindMax(frame2Projection,frame2->vertex.size());
		minframe2=FindMin(frame2Projection,frame2->vertex.size());

		//std::cout<<"projections "<<maxframe1<<" "<<maxframe2<<" "<<minframe1<<" "<<minframe2<<"\n";
		if (minframe2>maxframe1 || maxframe2<minframe1){
			//std::cout<<"Aborted\n";
			DataCarrier.Collision=false;
			DataCarrier.SeperatingVector.null();
			return;
		}
		candidate1=*it;
		candidate2=*it;
		candidate1*=(maxframe2-minframe1);
		candidate2*=(minframe2-maxframe1);
		//std::cout<<"canidates "<<candidate1.length()<<" "<<candidate2.length()<<" "<<DataCarrier.SeperatingVector->length()<<"\n";
		if (fabs(maxframe2-minframe1)<fabs(minframe2-maxframe1)){
			if(first || DataCarrier.SeperatingVector.length()>candidate1.length()){
				DataCarrier.SeperatingVector=candidate1;
				DataCarrier.CollisionAxis=*it;
				DataCarrier.Collision=true;
				first=false;
				DataCarrier.axis_from=1;
			}
		}
		else{
			if(first || DataCarrier.SeperatingVector.length()>candidate2.length()){
				DataCarrier.SeperatingVector=candidate2;
				DataCarrier.CollisionAxis=*it;
				DataCarrier.Collision=true;
				first=false;
				DataCarrier.axis_from=1;
			}
		}

	}
	for (it=frame2->axis.begin(),itend=frame2->axis.end();it!=itend;it++){
				//frame1Projection.clear();
				//frame2Projection.clear();
				for (it2=frame1->vertex.begin(),itend2=frame1->vertex.end(),i=0;it2!=itend2;it2++,i++){
					//frame1Projection.push_back((*it)*(*it2));
					frame1Projection[i]=(*it)*(*it2);
				}
				for (it2=frame2->vertex.begin(),itend2=frame2->vertex.end(),i=0;it2!=itend2;it2++,i++){
					//frame2Projection.push_back((*it)*(*it2));
					frame2Projection[i]=(*it)*(*it2);
				}
				maxframe1=FindMax(frame1Projection,frame1->vertex.size());
				minframe1=FindMin(frame1Projection,frame1->vertex.size());
				maxframe2=FindMax(frame2Projection,frame2->vertex.size());
				minframe2=FindMin(frame2Projection,frame2->vertex.size());
			//	std::cout<<"projections "<<maxframe1<<" "<<maxframe2<<" "<<minframe1<<" "<<minframe2<<"\n";
				if (minframe2>maxframe1 || maxframe2<minframe1){
					//std::cout<<"ABORTED\n";
					DataCarrier.Collision=false;
					DataCarrier.SeperatingVector.null();
					return;
				}
				candidate1=*it;
				candidate2=*it;
				candidate1*=(maxframe2-minframe1);
				candidate2*=(minframe2-maxframe1);
				if (fabs(maxframe2-minframe1)<fabs(minframe2-maxframe1)){
					if(DataCarrier.SeperatingVector.length()>candidate1.length()){
						DataCarrier.SeperatingVector=candidate1;
						DataCarrier.CollisionAxis=*it;
						DataCarrier.Collision=true;
						first=false;
						DataCarrier.axis_from=2;
					}
				}
				else{
					if(DataCarrier.SeperatingVector.length()>candidate2.length()){
						DataCarrier.SeperatingVector=candidate2;
						DataCarrier.CollisionAxis=*it;
						DataCarrier.Collision=true;
						first=false;
						DataCarrier.axis_from=2;
					}
				}
			}//det var så collisionsdetektionen, nu kommer findelsen af kontakt punkt
	//DataCarrier.CollisionAxis.print();
	float threshold=0.1,proj1,proj2,dis;
	Vector2D axis(0,0);
	axis = DataCarrier.CollisionAxis;
	dis = DataCarrier.SeperatingVector.length();
	Vector2D intersectingVertex1[2],intersectingVertex2[4];
	int i1=0,i2=0;
	bool appended;
	for (it=frame1->vertex.begin(),itend=frame1->vertex.end();it!=itend;it++){
		proj1=*it*axis;
		appended=false;
		for (it2=frame2->vertex.begin(),itend2=frame2->vertex.end();it2!=itend2;it2++){
				proj2=(*it2)*axis;

				if (fabs(proj1-proj2)-dis<=threshold){
					if (i1<2 && !appended){
						appended = true;
						intersectingVertex1[i1]=*it;
						i1++;
					}
					if (i2<4){
						intersectingVertex2[i2]=*it2;
						i2++;
					}
				}
		}
	}

	if (i1==1 && i2>=1){
	//	std::cout<<"and now\n";
		DataCarrier.ContactPoint=intersectingVertex1[0];
		return;
	}
	else if(i1==2 && i2==2){
	//	std::cout<<"number one\n";
		DataCarrier.ContactPoint=intersectingVertex2[0];
		return;
	}
	else{

		axis.rotate90();
		float edgeProjection1[2],edgeProjection2[2];
		edgeProjection1[0]=axis*intersectingVertex1[0];
		edgeProjection1[1]=axis*intersectingVertex1[1];
		edgeProjection2[0]=axis*intersectingVertex2[0];
		edgeProjection2[1]=axis*intersectingVertex2[1];
		if (edgeProjection1[0]<edgeProjection1[1]){
			Vector2D tempCarrier;
			float tempCarrierf;
			tempCarrierf=edgeProjection1[0];
			edgeProjection1[0]=edgeProjection1[1];
			edgeProjection1[1]=tempCarrierf;
			tempCarrier=intersectingVertex1[0];
			intersectingVertex1[0]=intersectingVertex1[1];
			intersectingVertex1[1]=tempCarrier;
		}
		if (edgeProjection2[0]<edgeProjection2[1]){
					Vector2D tempCarrier;
					float tempCarrierf;
					tempCarrierf=edgeProjection2[0];
					edgeProjection2[0]=edgeProjection2[1];
					edgeProjection2[1]=tempCarrierf;
					tempCarrier=intersectingVertex2[0];
					intersectingVertex2[0]=intersectingVertex2[1];
					intersectingVertex2[1]=tempCarrier;
		}


		//		std::cout<<edgeProjection1[0]<<" "<<edgeProjection1[1]<<" "<<edgeProjection2[0]<<" "<<edgeProjection2[1]<<"\n";


				if (edgeProjection1[1]>=edgeProjection2[1] && edgeProjection1[0]<=edgeProjection2[0]){
					//std::cout<<"kontakt1 er her\n";
					DataCarrier.ContactPoint=intersectingVertex1[0];
					DataCarrier.ContactPoint+=intersectingVertex1[1];
					DataCarrier.ContactPoint/=2.0;
					return;
				}
				else if (edgeProjection1[1]<=edgeProjection2[1] && edgeProjection1[0]>=edgeProjection2[0]){
					//std::cout<<"kontakt2 er her\n";
					DataCarrier.ContactPoint=intersectingVertex2[0];
					DataCarrier.ContactPoint+=intersectingVertex2[1];
					DataCarrier.ContactPoint/=2.0;
					return;
				}
				else if (edgeProjection1[1]<=edgeProjection2[1] && edgeProjection1[0]<edgeProjection2[0]){
					//std::cout<<"kontakt3 er her\n";
					DataCarrier.ContactPoint=intersectingVertex1[0];
					DataCarrier.ContactPoint+=intersectingVertex2[1];
					DataCarrier.ContactPoint/=2.0;
					return;
				}
				else if (edgeProjection1[1]>edgeProjection2[1] && edgeProjection1[0]>=edgeProjection2[0]){
					//std::cout<<"kontakt4 er her\n";
					DataCarrier.ContactPoint=intersectingVertex1[1];
					DataCarrier.ContactPoint+=intersectingVertex2[0];
					DataCarrier.ContactPoint/=2.0;
					return;
				}
	}
}




void physicsCore::MoveObjects(){
	std::list<compositePhysobj *>::iterator it,itend;
	for (it=objects.begin(),itend=objects.end();it!=itend;it++){
		(*it)->Move(1);
	}
}

void physicsCore::RotateObjects(){
	std::list<compositePhysobj *>::iterator it,itend;
		for (it=objects.begin(),itend=objects.end();it!=itend;it++){
			(*it)->Rotate(1);
		}
}

void physicsCore::ResetObjects(){
	std::list<compositePhysobj *>::iterator it,itend;
		for (it=objects.begin(),itend=objects.end();it!=itend;it++){
			(*it)->Reset();
		}
	CP.reset();
}

bool physicsCore::RAA_SAT(polygonFrame * frame1, polygonFrame * frame2){
	if (!(frame1->RAABCalculated)){
		frame1->CalculateRelativeAxisAlignedBox();
		frame1->RAABCalculated=true;

	}
	if (!(frame2->RAABCalculated)){
		frame2->CalculateRelativeAxisAlignedBox();
		frame2->RAABCalculated=true;
	}
	if (frame2->RAAB[0].x>frame1->RAAB[1].x || frame1->RAAB[0].x>frame2->RAAB[1].x || frame2->RAAB[0].y>frame1->RAAB[1].y || frame1->RAAB[0].y>frame2->RAAB[1].y){
		return false;
	}
	else{
		return true;
	}

}

void physicsCore::run(){
	collisionDetection();
	CP.run();
	MoveObjects();
	ResetObjects();
}

float physicsCore::FindMax(float liste[],int stop){
	bool first=true;
	int i=0;
	float max;
	for(;i!=stop;i++){
		if(first){
			first=false;
			max=liste[i];
		}
		else if(max<liste[i]){
			max=liste[i];
		}
	}
	return max;
}

float physicsCore::FindMin(float liste[],int stop){
	bool first=true;
	int i=0;
	float min;
	for(;i!=stop;i++){
		if(first){
			first=false;
			min=liste[i];
		}
		else if(min>liste[i]){
			min=liste[i];
		}
	}
	return min;
}



void physicsCore::PrintAll(){
	std::list<compositePhysobj *>::iterator it,itend;
	for(it=objects.begin(),itend=objects.end();it!=itend;it++){
		if((*it)->getMass()==10){
			(*it)->PrintPhyFrames();
		}
	}
}
void physicsCore::ForceAll(){
	std::list<compositePhysobj *>::iterator it,itend;
	std::list<polygonFrame >::iterator it1,itend1;
		for(it=objects.begin(),itend=objects.end();it!=itend;it++){
			for (it1=(*it)->phyFrame.begin(),itend1=(*it)->phyFrame.end();it1!=itend1;it1++){
				it1->CalculateRelativeAxisAlignedBox();
				it1->CalculateAxis();
			}
		}
}

sprite * physicsCore::PointInsideOfSprite(float x,float y){
	Vector2D point(x,y);
	PointInsideOfSprite(point);
}

sprite * physicsCore::PointInsideOfSprite(Vector2D point){
	//std::cout<<"getting point ";
	//point.print();
	std::list<compositePhysobj *>::iterator it;
	std::list<polygonFrame>::iterator itf;
	for(it=objects.begin();it!=objects.end();it++){
		if((*it)->hasRigid){
			for(itf=(*it)->phyFrame.begin();itf!=(*it)->phyFrame.end();itf++){
				if(PointInsideFrame(point,*itf)){
					return (*it)->parent;
				}
			}
		}
	}
	return NULL;
}


bool physicsCore::PointInsideFrame(Vector2D Point,polygonFrame frame){
	unsigned int i,IntersectionCount,j;
	Vector2D temp,Seperating_lines[3],A,B,C,D;
	float t,s;
	std::vector<Vector2D> Linesegments;
	std::list<Vector2D>::iterator it,it_plus;
	for (it=frame.vertex.begin(),it_plus=it,it_plus++;it_plus!=frame.vertex.end();it++,it_plus=it,it_plus++){
		temp=*it_plus;
		temp-=*it;
		Linesegments.push_back(temp);
	}
	temp=*frame.vertex.begin();
	it=frame.vertex.end();
	it--;
	temp-=*it;
	Linesegments.push_back(temp);
	Seperating_lines[0].setXY(1,0);
	Seperating_lines[1].setXY(1,1);
	Seperating_lines[2].setXY(0,1);
	for(j=0;j<3;j++){
		IntersectionCount=0;
		D=Seperating_lines[j];
		C=Point;
		it=frame.vertex.begin();
		for(i=0;i!=Linesegments.size();i++,it++){
			A=*it;
			B=Linesegments[i];
			if(D.y!=0){
				t=(C.x+(D.x/D.y)*A.y-(D.x/D.y)*C.y-A.x)/(B.x-(D.x/D.y)*B.y);
				s=(A.y+t*B.y-C.y)/D.y;
			}
			else{
				if(B.y!=0){
					t=(C.y-A.y)/B.y;
				}
				else{
					t=-1;
				}
				s=(A.x+t*B.x-C.x)/D.x;
			}
		//	std::cout<<"s = "<<s<<" t= "<<t<<"\n";
			if((t==0 || t>0) && t<1 && (s>0 || s==0)){
				//if(t < 1){
			//	std::cout<<"s = "<<s<<" t= "<<t<<" dobbelt\n";
			//	std::cout<<"intersection up\n";
				IntersectionCount++;
			//	}
			}
		}
		if(IntersectionCount%2==0){
			return false;
		}
	}


	return true;
}
