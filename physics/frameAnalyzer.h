#pragma once
#include "../toolModule.h"
#include <list>
#include <vector>
#include "phyArchetypes.h"
#include "compositePhysobj.h"

class frameAnalyzer{// the purpose of this class is to analyze a list of vertex in order to eliminate concave angles
public:
	frameAnalyzer();
	bool preAnalysis();
	void postAnalysis(polygonFrame *);
	void analysisFrame(polygonFrame *);
	bool directionAnalysis(polygonFrame *);
	bool analyzeProbes();
	bool isNotch(unsigned int);
	void run(polygonFrame *);
	void decompose(polygonFrame *);
	void synchronousProbing();
	void copyFrame(polygonFrame *);
	void printIFC();
	void printCPF();
	void writePartialFrame(unsigned int,unsigned int,Vector2D,Vector2D,polygonFrame *);
	//polygonFrame * IngoingFrame;
	std::list<polygonFrame> output_frames;
private:
	bool clockwise;
	std::vector<Vector2D> IFC,CPF; //IngoingFrameCopy
	std::vector<unsigned int> notches;
	unsigned int middleProbe,preProbe,postProbe;
	Vector2D A,B,C,D;
	//polygonFrame currentPartialFrame;
};
