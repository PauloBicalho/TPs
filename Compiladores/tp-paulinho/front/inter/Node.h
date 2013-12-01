/*
 * Node.h
 *
 *  Created on: Nov 28, 2013
 *      Author: itamar
 */

#ifndef NODE_H_
#define NODE_H_

#include "../lexer/Lexer.h"
#include <string>
#include <iostream>

using namespace std;

class Node {
public:
	int lexline;
	static int labels;
	Node() :
			lexline(Lexer::line) {
	}
	virtual ~Node() {
	}
	;

	void error(string s) {
		string msg = string("near line ") + to_string(lexline) + s;
		throw msg;
	}

	int newlabel() {
		return ++labels;
	}

	void emitlabel(int i) {
		cout << "L" << i << ":";
	}

	void emit(string s) {
		cout << "\t" << s << "\n";
	}
};

#endif /* NODE_H_ */
