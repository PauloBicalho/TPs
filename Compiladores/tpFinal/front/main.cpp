#include <iostream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"

#include <fstream>

using namespace std;

int main(int argc, char **argv) {
	if (argc != 2) {
		cerr << "Erro nos parâmetros\n";
		cerr << "\t" << argv[0] << " <file name>\n";
	}

	std::ifstream in(argv[1]);
	std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
	try {
		Lexer* lex = new Lexer();
		Parser* parse = new Parser(lex);
		parse->program();

		delete lex;
		delete parse;
	} catch (string& s) {
		cerr << "ERROR " << s << endl;
	}
//	cout << "END\n";

	return 0;
}
