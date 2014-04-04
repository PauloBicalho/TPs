/*
 * Env.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef ENV_H_
#define ENV_H_

#include <unordered_map>

using namespace std;

#include "../inter/Id.h"
#include "../lexer/Token.h"

class Env {
protected:
	Env* prev;
private:
	unordered_map<string, Id*> table;
public:
	Env(Env* n) {
		prev = n;
	}
	virtual void put(string w, Id* i) {
		table[w] = i;
	}

	virtual Id* get(string w) {
		for (Env* e = this; e != 0; e = e->prev) {
			auto it = e->table.find(w);
			if (it != e->table.end()) {
				return it->second;
			}
		}
		return 0;
	}

	virtual ~Env() {
	}
};

#endif /* ENV_H_ */
