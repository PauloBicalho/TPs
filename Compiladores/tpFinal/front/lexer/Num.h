/*
 * Num.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef NUM_H_
#define NUM_H_

#include "Token.h"
#include "Tag.h"

class Num: public Token {
public:
	const int value;

	Num(int v) :
			Token(Tag::NUM), value(v) {
	}

	friend ostream& operator<<(ostream &out, const Num &num) {
		out << num.value;
		return out;
	}

	virtual string toString() {
		return "const_i(" + to_string(value) + ")";
	}

	virtual ~Num() {
	}
	;
};

#endif /* NUM_H_ */
