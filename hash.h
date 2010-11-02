/*
 * hash.h
 *
 *  Created on: Sep 24, 2010
 *      Author: rolf
 */

#ifndef HASH_H_
#define HASH_H_
#include<string>
class hashValue{
public:
	hashValue(int hv);
	hashValue();
	hashValue(char * value);
	bool operator==(char * value);
	bool operator==(int value);
	bool operator==(hashValue other);

	bool operator<(hashValue& other);
	bool operator<(const hashValue other);
	bool operator>(hashValue& other);

	void operator=(int value);
	void operator=(char * value);
	void operator=(hashValue value);

	bool less(hashValue& other);
	bool less(hashValue& self, hashValue& other);

	int getInt();

private:
	int value_data;
};


int hash32(char * input);
int hash32(std::string input);
#endif /* HASH_H_ */
