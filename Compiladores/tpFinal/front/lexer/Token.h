/*
 * Token.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <ostream>
#include <sstream>
#include "Tag.h"

using namespace std;

class Token {
public:
	const int tag;

	Token(const Token& token) :
			tag(token.tag) {
	}

	Token(int t) :
			tag(t) {
	}
	;

	Token(Tag t) :
			tag(static_cast<int>(t)) {
	}
	;

	virtual ~Token() {
	}
	;

	virtual bool operator==(const Token &other) const {
		return tag == other.tag;
	}

	friend ostream& operator<<(ostream &out, const Token &token) {
		out << (char) token.tag;
		return out;
	}

	virtual string toString() {
		stringstream ss;
		ss << *this;
		return ss.str();
	}
};

namespace std {
template<>
struct hash<Token> {
	std::size_t operator()(const Token& k) const {
		return hash<int>()(k.tag);
	}
};

}

#endif /* TOKEN_H_ */
