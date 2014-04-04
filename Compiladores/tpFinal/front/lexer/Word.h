/*
 * Word.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef WORD_H_
#define WORD_H_

#include "Token.h"
#include "Tag.h"
#include <string>

using namespace std;

class Word: public Token {
public:
	string lexeme;
	static Word And, Or, eq, ne, le, ge, minus, True, False, temp;

	Word(string s, Tag tag) :
			Token(tag), lexeme(s) {

	}

	Word(const Word& w) :
			Token(w.tag), lexeme(w.lexeme) {
	}

	virtual ~Word() {

	}
	;
	friend ostream& operator<<(ostream &out, const Word &token) {
		out << token.lexeme;
		return out;
	}

	virtual string toString() {
		return lexeme;
	}
};

#endif /* WORD_H_ */
