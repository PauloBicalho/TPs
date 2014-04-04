/*
 * Type.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef TYPE_H_
#define TYPE_H_

#include "../lexer/Word.h"

class Type: public Word {
public:
	int width; // width is used for storage allocation

	static Type Int, Float, Char, Bool;

	Type(string s, Tag tag, int w) :
			Word(s, tag), width(w) {
	}

	friend bool operator ==(const Type& lhs, const Type& rhs) {
		return lhs.lexeme == rhs.lexeme;
	}

	friend bool operator !=(const Type& lhs, const Type& rhs) {
		return lhs.lexeme != rhs.lexeme;
	}

	static bool numeric(const Type& p) {
		if (p == Type::Char || p == Type::Int || p == Type::Float)
			return true;
		else
			return false;
	}

	static Type* max(const Type& p1, const Type& p2) {
		if (!numeric(p1) || !numeric(p2))
			return NULL;
		else if (p1 == Type::Float || p2 == Type::Float)
			return &Type::Float;
		else if (p1 == Type::Int || p2 == Type::Int)
			return &Type::Int;
		else
			return &Type::Char;
	}
	virtual ~Type() {
	}
	;
};

#endif /* TYPE_H_ */
