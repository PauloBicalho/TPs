/*
 * Temp.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef TEMP_H_
#define TEMP_H_

#include "Expr.h"
#include "../lexer/Word.h"

class Temp: public Expr {
public:
	static int count;
	int number;

	Temp(Type* p) :
			Expr(&Word::temp, p) {
		number = ++count;
	}

	virtual string toString() {
		return "t" + to_string(number);
	}

	virtual ~Temp() {
	}
	;
};

#endif /* TEMP_H_ */
