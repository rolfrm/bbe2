
#pragma once
#include <string>
#include <vector>
#include <armadillo>
#define INTEGER_CONVERSION_ERROR -2000000000
int integer_from_stdstring(std::string value);

class Vector3D;

class Vector2D{
	public:
		Vector2D(float,float);
		Vector2D();
		~Vector2D();
		bool isNull();
		void null();
		float length();
		float lengthSquared();
		void normalize();
		Vector2D produceNormalized();
		void rotate(float);
		void rotate90();
		Vector2D produceRotated(float);
		Vector2D produceRotated90();
		void setXY(float,float);
		void print();
		Vector2D projectVector(Vector2D);
		Vector2D projectVector(Vector2D *);
		float Crossproduct(Vector2D);
		Vector2D copy();
		//Vector2D minus(Vector2D other);
		//Vector2D plus(Vector2D other);
		
		Vector2D operator + (Vector2D);
		Vector3D operator + (Vector3D);

		void operator += (Vector2D);
		
		void operator = (Vector2D);
		void operator = (Vector2D *);
		
		Vector2D operator - (Vector2D);
		Vector3D operator - (Vector3D);
		//void operator - (Vector2D *);

		void operator -= (Vector2D);

		float operator * (Vector2D);
		float operator * (Vector2D	 *);
		float operator * (Vector3D);
		Vector2D operator * (float);
		void operator *= (float);

		bool operator == (Vector2D);
		bool operator == (Vector2D *);

		Vector2D operator / (float);
		void operator /= (float);
		float x,y; 
};

class Vector3D{
public:
	Vector3D(float x,float y,float z);
	Vector3D();

	Vector3D operator + (Vector3D);
	Vector3D operator - (Vector3D);
	Vector3D operator + (Vector2D);
	Vector3D operator - (Vector2D);
	void operator = (Vector3D);
	void operator = (Vector2D);
	float operator * (Vector3D);
	float operator * (Vector2D);
	void operator *=(float);
	Vector3D CrossProduct(Vector3D);
	Vector3D CrossProduct(Vector2D);
	float x,y,z;
	void print();
};
