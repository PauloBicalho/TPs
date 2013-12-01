/*
 * Parser.h
 *
 *  Created on: Nov 28, 2013
 *      Author: paulo
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "../lexer/Lexer.h"
#include "../lexer/Token.h"
#include "../lexer/Num.h"
#include "../symbols/Env.h"
#include "../symbols/Array.h"
#include "../inter/Do.h"
#include "../inter/While.h"
#include "../inter/Rel.h"
#include "../inter/Not.h"
#include "../inter/Seq.h"
#include "../inter/If.h"
#include "../inter/Else.h"
#include "../inter/Break.h"
#include "../inter/Set.h"
#include "../inter/SetElem.h"
#include "../inter/Or.h"
#include "../inter/And.h"
#include "../inter/Rel.h"
#include "../inter/Arith.h"
#include "../inter/Unary.h"
#include "../inter/Not.h"
#include "../inter/Constant.h"

#include <memory>

class Parser {
private:
	Lexer* lex; // lexical analyzer for this parser
	Token* look; // lookahead tagen

public:
	Env* top;       // current or top symbol table
	int used;         // storage used for declarations

	Parser(Lexer* l) :
			top(NULL), used(0) {
		lex = l;
		move();
	}

	virtual void move() {
		look = lex->scan();
		//std::cout << "Inside move: " << look->tag << "\n";
	}

	virtual void error(string s) {
		throw string("near line " + to_string(lex->line) + ": " + s);
	}

	virtual void match(int t) {
		//	std::cout << "\n\n Inside match= " << look->tag << "\n\n";
		if (look->tag == t) {
			move();
		} else
			error("syntax error");
	}

	virtual void program() {  // program -> block
		Stmt* s = block();
		int begin = s->newlabel();
		int after = s->newlabel();
		s->emitlabel(begin);
		s->gen(begin, after);
		s->emitlabel(after);
	}

	virtual Stmt* block() {  // block -> { decls stmts }
		match('{');
		Env* savedEnv = top;
		top = new Env(top);
		decls();
		Stmt* s = stmts();
		match('}');
		top = savedEnv;
		return s;
	}

	virtual void decls() {

		while (look->tag == static_cast<int>(Tag::BASIC)) {   // D -> type ID ;
			Type* p = type();
			Token* tok = look;
			match(static_cast<int>(Tag::ID));
			match(';');
			Word* word = (Word*) tok;
			Id* id = new Id(word, p, used);
			top->put(word->lexeme, id);
			used = used + p->width;
		}
	}

	virtual Type* type() {

		Type* p = (Type*) look;            // expect look.tag == Tag.BASIC
		match(static_cast<int>(Tag::BASIC));
		if (look->tag != '[')
			return p; // T -> basic
		else
			return dims(p);            // return array type
	}

	virtual Type* dims(Type* &p) {
		match('[');
		Token* tok = look;
		match(static_cast<int>(Tag::NUM));
		match(']');
		if (look->tag == '[')
			p = dims(p);
		int v = static_cast<Num*>(tok)->value;
		return new Array(v, p);
	}

	virtual Stmt* stmts() {
		if (look->tag == '}')
			return Stmt::Null;
		else
			return new Seq(stmt(), stmts());
	}

	virtual Stmt* stmt() {
		Expr* x;
		//Stmt *s,
		Stmt *s1, *s2;
		Stmt* savedStmt;         // save enclosing loop for breaks
		While* whilenode;
		Do* donode;

		switch (look->tag) {

		case ';':
			move();
			return Stmt::Null;

		case (int) Tag::IF:

			match(static_cast<int>(Tag::IF));
			match('(');
			x = cbool();
			//	std::cout << "\n\nffffffffffffffffff 1= " << (char)look->tag << "\n\n";
			match(')');
			s1 = stmt();

			if (look->tag != (int) Tag::ELSE)
				return new If(x, s1);

			match(static_cast<int>(Tag::ELSE));

			s2 = stmt();

			return new Else(x, s1, s2);

		case (int) Tag::WHILE:
			whilenode = new While();
			savedStmt = Stmt::Enclosing;
			Stmt::Enclosing = whilenode;
			match((int) Tag::WHILE);
			match('(');
			x = cbool();
			match(')');
			s1 = stmt();
			whilenode->init(x, s1);
			Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
			return whilenode;

		case (int) Tag::DO:
			donode = new Do();
			savedStmt = Stmt::Enclosing;
			Stmt::Enclosing = donode;
			match((int) Tag::DO);
			s1 = stmt();
			match((int) Tag::WHILE);
			match('(');
			x = cbool();
			match(')');
			match(';');
			donode->init(s1, x);
			Stmt::Enclosing = savedStmt;  // reset Stmt.Enclosing
			return donode;

		case (int) Tag::BREAK:
			match((int) Tag::BREAK);
			match(';');
			return new Break();

		case '{':
			return block();

		default:
			return assign();
		}
	}

	virtual Stmt* assign() {
		Stmt* stmt;
		Token* t = look;
		match((int) Tag::ID);
		Word* word = (Word*) t;
		Id* id = top->get(word->lexeme);
		if (id == NULL)
			error(t->toString() + " undeclared");

		if (look->tag == '=') {       // S -> id = E ;
			move();
			stmt = new Set(id, cbool());
		} else {                        // S -> L = E ;
			Access* x = offset(id);
			match('=');
			stmt = new SetElem(x, cbool());
		}
		match(';');
		return stmt;
	}

	virtual Expr* cbool() {
		Expr* x = join();
		while (look->tag == (int) Tag::OR) {
			Token* tok = look;
			move();
			x = new Or(tok, x, join());
		}
		return x;
	}

	virtual Expr* join() {
		Expr* x = equality();
		while (look->tag == (int) Tag::AND) {
			Token* tok = look;
			move();
			x = new And(tok, x, equality());
		}
		return x;
	}

	virtual Expr* equality() {
		Expr* x = rel();
		while (look->tag == (int) Tag::EQ || look->tag == (int) Tag::NE) {
			Token* tok = look;
			move();
			x = new Rel(tok, x, rel());
		}
		return x;
	}

	virtual Expr* rel() {
		//	std::cout << "\nRel1 = " << look->tag << "--" << (char)look->tag << "\n\n";
		Expr* x = expr();
		Token* tok;
		//	std::cout << "\nRel2 = " << look->tag << "--" << (char)look->tag << "\n\n";
		switch (look->tag) {
		case '<':
			tok = look;
			move();
			break;
		case (int) Tag::LE:
			tok = look;
			move();
			break;
		case (int) Tag::GE:
			tok = look;
			move();
			break;
		case '>':
			tok = look;
			move();
			break;
		default:
			return x;
		}
		return new Rel(tok, x, expr());
	}

	virtual Expr* expr() {
		Expr* x = term();
		while (look->tag == '+' || look->tag == '-') {
			Token* tok = look;
			move();
			x = new Arith(tok, x, term());
		}
		return x;
	}

	virtual Expr* term() {
		//std::cout << "\nTerm1 = " << look->tag << "--" << (char)look->tag << "\n\n";
		Expr* x = unary();
		//std::cout << "\nTerm2 = " << look->tag << "--" << (char)look->tag << "\n\n";
		while (look->tag == '*' || look->tag == '/') {
			Token* tok = look;
			move();
			x = new Arith(tok, x, unary());
		}
		return x;
	}

	virtual Expr* unary() {

		if (look->tag == '-') {
			move();
			return new Unary(&Word::minus, unary());
		} else if (look->tag == '!') {
			Token* tok = look;
			move();
			return new Not(tok, unary());
		} else
			return factor();
	}

	virtual Expr* factor() {
		//	std::cout << "Factor = " << look->tag << "--" << (char) look->tag << "\n\n";
		Expr* x = NULL;
		switch (look->tag) {
		case '(':
			move();
			x = cbool();
			match(')');
			return x;
		case (int) Tag::NUM:
			x = new Constant(look, &Type::Int);
			move();
			return x;
		case (int) Tag::REAL:
			x = new Constant(look, &Type::Float);
			move();
			return x;
		case (int) Tag::TRUE:
			x = const_cast<Constant*>(Constant::True);
			move();
			return x;
		case (int) Tag::FALSE:
			x = const_cast<Constant*>(Constant::False);
			move();
			return x;
		default:
			error("syntax error");
			return x;
		case (int) Tag::ID:
//			std::cout << "---------------------------------TAGID\n\n\n";
			string s = look->toString();
			Id* id = top->get(((Word*) look)->lexeme);
//std::cout << "---------------------------------LEXEME " << ( (Word*) look)->lexeme << "\n\n\n";
			if (id == NULL)
				error(look->toString() + " undeclared");
			move();
			//	std::cout << "Look.tag : " << look->tag << "\n";
			if (look->tag != '[') {
				//		std::cout << "after2\n";
				return id;
			} else
				return offset(id);
		}
	}

	virtual Access* offset(Id* a) {   // I -> [E] | [E] I
		Expr* i;
		Expr* w;
		Expr* t1, *t2;
		Expr* loc;  // inherit id

		Type* type = a->type;
		match('[');
		i = cbool();
		match(']');     // first index, I -> [ E ]
		type = ((Array*) type)->of;
		w = new Constant(type->width);
		t1 = new Arith(new Token('*'), i, w);
		loc = t1;
		while (look->tag == '[') {      // multi-dimensional I -> [ E ] I
			match('[');
			i = cbool();
			match(']');
			type = ((Array*) type)->of;
			w = new Constant(type->width);
			t1 = new Arith(new Token('*'), i, w);
			t2 = new Arith(new Token('+'), loc, t1);
			loc = t2;
		}

		return new Access(a, loc, type);
	}

	virtual ~Parser() {
	}
};

#endif /* PARSER_H_ */
