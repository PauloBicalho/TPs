#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>


using namespace std;

class Scanner{

  public:
    Scanner(){
      types.insert("if");
      types.insert("iffalse");
      types.insert("goto");
      
      types.insert(">");
      types.insert(">=");
      types.insert("<");
      types.insert("<=");

      types.insert("==");
      types.insert("!=");
      
      types.insert("(i+)");
      types.insert("(i-)");
      types.insert("(i*)");
      types.insert("(i/)");
      
      types.insert("(f+)");
      types.insert("(f-)");
      types.insert("(f*)");
      types.insert("(f/)");
    }

    pair<string, vector<string> > scanLine(){
      vector<string>  words;
      string type ("=");

      for(;;){
        string w = scanWord();

        if( types.find(w) != types.end() and type == "=" )
          type = w;

        
        if( w != "")
          words.push_back(w);

        if( newLine || endFile )
          return make_pair(type,words);
      }


      return make_pair(type,words);
    }

  private:
    char peek;
    bool newLine;
    bool endFile;
    set<string> types;
    
    string scanWord(){
      newLine = false;
      endFile = false;
      string word ("");


      for(;;){
        cin.get(peek);

        if( cin.fail() ){
          endFile = true;
          return word;
        }

        if(peek == '\n'){
          newLine = true;
          return word;
        }

        if(peek == '\t' || peek == ' ')
          return word;
        
        word.push_back(peek);
      }
    }
      
};

#endif // SCANNER_H
