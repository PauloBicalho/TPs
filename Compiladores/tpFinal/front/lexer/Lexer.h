/*
 * Lexer.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef LEXER_H_
#define LEXER_H_

#include "Word.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>

class Lexer {
public:
	static int line;
	char peek;
	unordered_map<string, Word*> words;

	void reserve(Word* w) {
		words.insert(pair<const string, Word*>(w->lexeme, w));
	}

	void readch() {
		cin.get(peek);
		//if( peek != ' ')
		//	std::cout << "PEEK | " << peek << "\n";
		if (cin.fail()) {
			peek = 0;
			//throw string("Reading end of file");
		}
		/*cout << peek;*/}

	bool readch(char c) {
		readch();
		if (peek != c)
			return false;
		peek = ' ';
		return true;
	}

	Token* scan();

	Lexer();

	virtual ~Lexer();
};

#endif /* LEXER_H_ */
