/*
 * hash.cpp
 *
 *  Created on: Sep 24, 2010
 *      Author: rolf
 */
#include "hash.h"
#include <iostream>

int hash32(std::string input){
	static int counter = 0;
	counter++;
	//std::cout << "Hashing std string!\n" << counter << input;
	return hash32((char *)input.c_str());
}

int hash32(char * input){
	        unsigned long hash = 5381;
	        int c;

	        while (c = *input++) hash = ((hash*33)<<2)*33*c;

	        return hash;
}

hashValue::hashValue(int a){
	value_data = a;
}

hashValue::hashValue(){
	value_data = 0;
}
hashValue::hashValue(char * a){
	value_data = hash32(a);
}

bool hashValue::operator==(int value){
	return value_data == value;
}

bool hashValue::operator==(char * a){
	return value_data == hash32(a);
}

bool hashValue::operator==(hashValue value){
	return value_data == value.value_data;
}

bool hashValue::operator<(hashValue &value){
	return (this->value_data < value.value_data);
}

bool hashValue::operator<(const hashValue value){
	return this->value_data < value.value_data;
}

bool hashValue::operator>(hashValue &value){
	return (this->value_data > value.value_data);
}

void hashValue::operator=(int value){
	value_data = value;
}

void hashValue::operator=(hashValue hv){
	value_data = hv.value_data;
}

void hashValue::operator=(char * a){
	value_data = hash32(a);
}

bool hashValue::less(hashValue& other){
	return value_data < other.value_data;
}

bool hashValue::less(hashValue& self, hashValue& other){
	return self.value_data < other.value_data;
}

int hashValue::getInt(){
	return value_data;
}
