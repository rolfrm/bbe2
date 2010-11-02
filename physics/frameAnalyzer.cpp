#include "frameAnalyzer.h"
#include <iostream>

frameAnalyzer::frameAnalyzer(){
	clockwise=false;
}



void frameAnalyzer::analysisFrame(polygonFrame * candidate){
	postAnalysis(candidate);
	copyFrame(candidate);
	if(!preAnalysis()){
		if(candidate->vertex.size()>2){
			output_frames.push_back(*candidate);
		}
	}
	else{
		decompose(candidate);
	}
}

void frameAnalyzer::run(polygonFrame * candidate){
	std::list<polygonFrame>::iterator it;
	//if(output_frames.size()!=0){
	if(directionAnalysis(candidate)){
		candidate->vertex.reverse();
	}
	output_frames.clear();
	//}
	analysisFrame(candidate);
}

bool frameAnalyzer::directionAnalysis(polygonFrame * patient){
	float sum=0;
	std::list<Vector2D>::iterator it,it2;
	for(it=patient->vertex.begin();it!=patient->vertex.end();it++){
		it2=it;
		it2++;
		sum+=it->Crossproduct(*it2);
	}
	it--;
	it2=patient->vertex.begin();
	sum+=it->Crossproduct(*it2);
	sum/=2;
	if(sum<0){
		return true;
	}
	else{
		return false;
	}
}

bool frameAnalyzer::preAnalysis(){
	unsigned int i;
	notches.clear();
	preProbe=IFC.size()-1;
	middleProbe=0;
	postProbe=1;
	for (i=0;i!=IFC.size();i++){
		if(analyzeProbes()){
			notches.push_back(middleProbe);
		}
		synchronousProbing();
	}
	if(notches.size()==0){
		return false;
	}
	return true;
}

void frameAnalyzer::postAnalysis(polygonFrame * frame){
	frame->vertex.unique();
	std::list<Vector2D>::iterator it1,it2,itend,itend2;
	/*
	it1=frame->vertex.begin();
	it2=it1;
	it2++;
	if(*it1==*it2){
		frame->vertex.pop_front();
	}
	it1=frame->vertex.end();
	it1--;
	it2=it1;
	it2--;
	if(*it1==*it2){
		frame->vertex.pop_back();
	}
	*/
	//frame->vertex.unique();
	it1=frame->vertex.begin();
	itend=frame->vertex.end();
	itend--;
	itend2=itend;
	itend--;
	for(;it1!=itend;it1++){
		for(it2=it1,it2++;it2!=itend2;it2++){
			//std::cout<<"comparing\n";
			//it1->print();
			//it2->print();
			if(*it1==*it2){
		//	if(it1->x==it2->x && it1->y==it2->y){
				//std::cout<<"removing\n";
				//it2->print();
				frame->vertex.erase(it2);
				break;
			}
		}
	}

}

bool frameAnalyzer::analyzeProbes(){
	//std::cout<<"probes :"<<preProbe<<" "<<middleProbe<<" "<<postProbe<<"\n";
	A=IFC[preProbe];
	B=IFC[postProbe];
	A-=IFC[middleProbe];
	B-=IFC[middleProbe];
	//std::cout<<"analysing probes "<<A.Crossproduct(B)<<"\n";
	if(A.Crossproduct(B)>0){
		return true;
	}
	else{
		return false;
	}
}

bool frameAnalyzer::isNotch(unsigned int candidate){
	unsigned int i;
	/*
	if(candidate<0 || candidate>=IFC.size()){
		candidate=IFC.size();
	}
	*/
	candidate=(unsigned int) candidate;
	for (i=0;i!=notches.size();i++){
		if (candidate==notches[i]){
			return true;
		}
	}
	return false;
}

void frameAnalyzer::synchronousProbing(){
	middleProbe++;
	preProbe++;
	postProbe++;
	if (postProbe==IFC.size()){
		postProbe=0;
	}
	else if(middleProbe==IFC.size()){
		middleProbe=0;
	}
	else if(preProbe==IFC.size()){
		preProbe=0;
	}
}

void frameAnalyzer::copyFrame(polygonFrame * frame){
	std::list<Vector2D>::iterator it;
	IFC.clear();
	for (it=frame->vertex.begin();it!=frame->vertex.end();it++){
		IFC.push_back(*it);
	}
}


void frameAnalyzer::printIFC(){
	unsigned int i;
	std::cout<<"printing IFC\n";
	for(i=0;i<IFC.size();i++){
		IFC[i].print();
	}
}

void frameAnalyzer::printCPF(){
	unsigned int i;
	std::cout<<"printing CPF\n";
	for(i=0;i<CPF.size();i++){
		CPF[i].print();
	}
}

void frameAnalyzer::decompose(polygonFrame * ingoing_frame){
	//ingoing_frame->PrintVertex();
	unsigned int i,current_notch,nabo;
	Vector2D temp,Seperating_line;
	float t,s,s_lowest=1000000;
	std::vector<Vector2D> Linesegments;
	polygonFrame frame1,frame2;
	for (i=0;i!=IFC.size()-1;i++){
		temp=IFC[i+1];
		temp-=IFC[i];
		Linesegments.push_back(temp);
	}
	temp=IFC[0];
	temp-=IFC[IFC.size()-1];
	Linesegments.push_back(temp);
	/*
	for(i=0;i!=Linesegments.size();i++){
		Linesegments[i].print();
	}
	*/
	//std::cout<<"size "<<notches.size()<<"\n";
	current_notch=notches[0];
	if(current_notch==0){
		nabo=IFC.size();
	}
	else{
		nabo=current_notch;
	}
	nabo--;
	Seperating_line=Linesegments[current_notch].produceNormalized();
	Seperating_line+=Linesegments[nabo].produceNormalized();
	Seperating_line.normalize();
	Seperating_line.rotate90();
	//Seperating_line.print();
	D=Seperating_line;
	C=IFC[current_notch];
	for(i=0;i!=IFC.size();i++){
		A=IFC[i];
		B=Linesegments[i];
		t=(C.x+(D.x/D.y)*A.y-(D.x/D.y)*C.y-A.x)/(B.x-(D.x/D.y)*B.y);
		if(D.y!=0){
			s=(A.y+t*B.y-C.y)/D.y;
		}
		else{
			s=(A.x+t*B.x-C.x)/D.x;
		}
		//std::cout<<"t="<<t<<" "<<"s="<<s<<"\n";
		if(t>=0 && t<=1 && s>0){
			temp=D;
			temp*=s;
			temp+=C;
			if(s<s_lowest){
				s_lowest=s;
				writePartialFrame(current_notch+1,i,C,temp,&frame1);
				writePartialFrame(i+1,current_notch-1,temp,C,&frame2);
			}
		}
	}
	frame1.rigid=ingoing_frame->rigid;
	frame2.rigid=ingoing_frame->rigid;
	//frame1.PrintVertex();
	//frame2.PrintVertex();
	analysisFrame(&frame1);
	analysisFrame(&frame2);
}

void frameAnalyzer::writePartialFrame(unsigned int from,unsigned int to,Vector2D start,Vector2D end,polygonFrame * frame){
	frame->EmptyVertex();
	if(from>=IFC.size()){
		from=0;
	}
	if(to>=IFC.size()){
		to=0;
	}
	unsigned int i;
	frame->EmptyVertex();
	frame->AddVertex(start);
	for(i=from;i!=to+1;i++){
		if(i==IFC.size()){
			i=0;
		}
		frame->AddVertex(IFC[i]);
	}
	frame->AddVertex(end);
//	std::cout<<"result\n";
//	frame->PrintVertex();
}

