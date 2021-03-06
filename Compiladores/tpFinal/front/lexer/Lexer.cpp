/*
 * Lexer.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#include "Lexer.h"
#include "../symbols/Type.h"
#include "Real.h"
#include "Num.h"
#include <cstring>
#include <sstream>
#include <memory>

int Lexer::line = 1;

Lexer::Lexer() :
		peek(' ') {
	reserve(new Word("if", Tag::IF));
	reserve(new Word("else", Tag::ELSE));
	reserve(new Word("while", Tag::WHILE));
	reserve(new Word("do", Tag::DO));
	reserve(new Word("break", Tag::BREAK));

	reserve(&Word::True);
	reserve(&Word::False);

	reserve(&Type::Int);
	reserve(&Type::Char);
	reserve(&Type::Bool);
	reserve(&Type::Float);
}

Lexer::~Lexer() {
	// TODO Auto-generated destructor stub
}

inline int charToDigit(char c) {
	return c - '0';
}

Token* Lexer::scan() {
	for (;; readch()) {
		if (peek == ' ' || peek == '\t')
			continue;
		else if (peek == '\n')
			line = line + 1;
		else
			break;
	}
	switch (peek) {
	case '&':
		if (readch('&'))
			return &(Word::And);
		else
			return new Token('&');
	case '|':
		if (readch('|'))
			return &(Word::Or);
		else
			return new Token('|');
	case '=':
		if (readch('='))
			return &(Word::eq);
		else
			return new Token('=');
	case '!':
		if (readch('='))
			return &(Word::ne);
		else
			return new Token('!');
	case '<':
		if (readch('='))
			return &(Word::le);
		else
			return new Token('<');
	case '>':
		if (readch('='))
			return &(Word::ge);
		else
			return new Token('>');
	}
	if (isdigit(peek)) {

		int v = 0;
		do {
			v = 10 * v + charToDigit(peek);
			readch();
		} while (isdigit(peek));
		if (peek != '.')
			return new Num(v);
		float x = v;
		float d = 10;
		for (;;) {
			readch();
			if (!isdigit(peek))
				break;
			x = x + charToDigit(peek) / d;
			d = d * 10;
		}
		return new Real(x);
	}
	if (isalpha(peek)) {
		stringstream b;
		do {
			b << peek;
			readch();
		} while (isalnum(peek));
		string s = b.str();
		auto it = words.find(s);
		if (it != words.end()) {
			//cout << *it->second << endl;
			return it->second;
		}
		Word* w = new Word(s, Tag::ID);
		words.insert(pair<const string, Word*>(s, w));
		return w;
	}
	Token* tok = new Token(peek);
	peek = ' ';
	return tok;
}
