#include "toolModule.h"
#include <math.h>
#include <iostream>

#include <sstream>

int integer_from_stdstring(std::string value) {
	int output;
	if (std::istringstream(value) >> output) {
		return output;
	}
	return INTEGER_CONVERSION_ERROR;
}

Vector2D::Vector2D(float x_in,float y_in){
	x=x_in;
	y=y_in;
}

Vector2D::Vector2D(){
	x = 0;
	y = 0;
}

Vector2D::~Vector2D(){
}

bool Vector2D::isNull(){
	if (x==0 && y==0){
		return true;
	}
	else{
		return false;
	}

}

void Vector2D::null(){
	x=0;
	y=0;
}

float Vector2D::length(){
	return sqrt(x*x+y*y);
}

float Vector2D::lengthSquared(){
	return x*x+y*y;
}

void Vector2D::normalize(){
	float l=length();
	if(l==0){
		x=1;
		y=0;
	}
	else{
			x/=l;
			y/=l;
	}
}

Vector2D Vector2D::produceNormalized(){
	if(!isNull()){
	float l=length();
	return Vector2D(x/l,y/l);
	}
	else{
		return Vector2D(0,0);
	}
	}

void Vector2D::rotate(float angle){
	float tempx=x,tempy=y;
	x=cos(angle)*tempx-sin(angle)*tempy;
	y=sin(angle)*tempx+cos(angle)*tempy;
}

void Vector2D::rotate90(){
	float temp;
	temp=x;
	x=-y;
	y=temp;
}

Vector2D Vector2D::produceRotated(float angle){
	return Vector2D(cos(angle)*x-sin(angle)*y,sin(angle)*x+cos(angle)*y);
}

void Vector2D::setXY(float x_in,float y_in){
	x=x_in;
	y=y_in;
}
Vector2D Vector2D::operator+ (Vector2D other){
	return Vector2D(x+other.x,y+other.y);
}

/*
Vector2D Vector2D::operator+ (Vector2D * other){
	return Vector2D(x+other->x,y+other->y);
}
*/
void Vector2D::operator += (Vector2D other){
	x+=other.x;
	y+=other.y;
}

void Vector2D::operator= (Vector2D other){
	x=other.x;
	y=other.y;
}
void Vector2D::operator =(Vector2D * other){
	x=other->x;
	y=other->y;
}

Vector2D Vector2D::operator- (Vector2D other){
	return Vector2D(x-other.x,y-other.y);
}

void Vector2D::operator -= (Vector2D other){
	x-=other.x;
	y-=other.y;

}

Vector2D Vector2D::operator /(float scale){
	return Vector2D(x/scale,y/scale);
}

float Vector2D::operator* (Vector2D other){
	return x*other.x+y*other.y;
}

float Vector2D::operator *(Vector2D * other){
	return x*other->x+y*other->y;
}

Vector2D Vector2D::operator *(float scale){
	return Vector2D(x*scale,y*scale);
}

void Vector2D::operator *=(float scale){
	x*=scale;
	y*=scale;
}

void Vector2D::operator /=(float scale){
	x/=scale;
	y/=scale;
}

bool Vector2D::operator ==(Vector2D other){
	//if (x==other.x && y==other.y){
	if(fabs(x-other.x)<0.0001 && fabs(y-other.y)<0.0001){
		return true;
	}
	else{
		return false;
	}
}

bool Vector2D::operator ==(Vector2D * other){
	if (x==other->x && y==other->y){
		return true;
	}
	else{
		return false;
	}
}


void Vector2D::print (){
	std::cout<<"("<<x<<","<<y<<")"<<"\n";
}

Vector2D Vector2D::projectVector(Vector2D onto){
	Vector2D unit=onto.produceNormalized();
	unit*=(x*unit.x+y*unit.y);
	return unit;
}

Vector2D Vector2D::projectVector(Vector2D * onto){
	Vector2D unit=onto->produceNormalized();
	unit*=(x*unit.x+y*unit.y);
	return unit;
}

float Vector2D::Crossproduct(Vector2D other){
	return x*other.y-y*other.x;
}

Vector2D Vector2D::copy(){
	return Vector2D(x,y);
}

Vector2D Vector2D::produceRotated90(){
	return Vector2D(-y,x);
}

Vector3D Vector2D::operator +(Vector3D other){
	return Vector3D(x+other.x,y+other.y,other.z);
}

Vector3D Vector2D::operator -(Vector3D other){
	return Vector3D(x-other.x,y-other.y,-other.z);
}

float Vector2D::operator *(Vector3D other){
	return x*other.x+y*other.y;
}

Vector3D::Vector3D(float xin,float yin,float zin){
 x=xin;
 y=yin;
 z=zin;
}

Vector3D::Vector3D(){
	Vector3D(0,0,0);
}

void Vector3D::operator =(Vector3D other){
	x=other.x;
	y=other.y;
	z=other.z;
}

void Vector3D::operator =(Vector2D other){
	x=other.x;
	y=other.y;
	z=0;
}

float Vector3D::operator *(Vector2D other){
	return x*other.x+y*other.y;
}

float Vector3D::operator *(Vector3D other){
	return x*other.x+y*other.y+z*other.z;
}

Vector3D Vector3D::CrossProduct(Vector3D other){
	return Vector3D(y*other.z-other.y*z,z*other.x-other.z*x,x*other.y-y*other.x);
}

Vector3D Vector3D::CrossProduct(Vector2D other){
	return Vector3D(-other.y*z,z*other.x,x*other.y-y*other.x);
}

Vector3D Vector3D::operator +(Vector3D other){
	return Vector3D(x+other.x,y+other.y,z+other.z);
}

Vector3D Vector3D::operator +(Vector2D other){
	return Vector3D(x+other.x,y+other.y,z);
}

Vector3D Vector3D::operator -(Vector3D other){
	return Vector3D(x-other.x,y-other.y,z-other.z);
}

Vector3D Vector3D::operator -(Vector2D other){
	return Vector3D(x-other.x,y-other.y,z);
}

void Vector3D::operator *=(float scale){
	x*=scale;
	y*=scale;
	z*=scale;
}


void Vector3D::print(){
	std::cout<<"("<<x<<","<<y<<","<<z<<")\n";
}
