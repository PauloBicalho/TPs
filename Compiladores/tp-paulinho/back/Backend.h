#ifndef BACKEND_H
#define BACKEND_H

#include <iostream>
#include <string>
#include <map>

#include "Scanner.h"
#include "Types.h"

using namespace std;

class Backend{
  
  public:
    Backend();
    void program();

  private:
    Scanner scanner;
    int currentIndex;
    int fileLine;
    int label;
    
    map<string,int> variableMap;  //map variable in local registrators
    vector<int> freeRegs;
    vector< pair<string,int> > regsWithTemps;

    vector< pair<string, vector<string> > > lines;
    
    vector< pair<string, string> > convertedLines;
    map< int, int> mapNewLinesToLabel;

    map<string, int > labelLines;

    void processLine(vector<string> &words, const string &type);
    int processOperand(const string &word);

    vector<string> getLabels(vector<string> &words, int fileLine);

    vector<string> constantPool;
    map<string,int> mapToConstantPool;
   

  protected:


    string getValue(const string &word){
      int i = word.find_last_of('(');
      int j = word.find_first_of(')');
      return word.substr(i+1,j-i-1);
    }

    string getIndex(const string &word){
      int i = word.find_last_of('[');
      int j = word.find_last_of(']');
      return word.substr(i+1,j-i-1);
    }


    int getReg(const string &word, bool f = true){
      if( variableMap.find(word) != variableMap.end() )
        return variableMap[word];
      
      if(f)
        return getFreeReg();
      else
        return -1;
    }

    int getFreeReg(){
      return currentIndex++;
    }

    int pushOnStack(const string &word, const Types::OperandType type){
      int reg = -1; int lbl; string index; int idx;
      switch(type){
        case Types::CONST_INT:
          return emit( "bipush\t" + getValue(word) );
          break;
        case Types::CONST_FLOAT:
          if( mapToConstantPool.find(word) != mapToConstantPool.end() )
            idx = mapToConstantPool[word];
          else{
            string value = getValue(word);
            idx = (int) constantPool.size();
            constantPool.push_back(value);
            mapToConstantPool[word] = idx;
          }
          return emit("ldc\t#" + to_string(idx));
          break;
        case Types::CONST_TRUE:
          return emit("iconst_1");
          break;
        case Types::CONST_FALSE:
          return emit("iconst_0");
          break;          
        case Types::VAR_INT:
          reg = getReg(word);
          return emit("iload\t" + to_string(reg));
          break;
        case Types::VAR_FLOAT:
          reg = getReg(word);
          return emit("fload\t" + to_string(reg));
          break;
        case Types::VAR_BOOL:
          reg = getReg(word);
          return emit("iload\t" + to_string(reg));
          break;
        case Types::ARRAY_INT:
          reg = getReg(word,false);

          if(reg == -1){
            emit("bipush\t1000");
            emit("newarray\tint");
            reg = getReg(word);
            emit("astore\t" + to_string(reg));
            variableMap[word] = reg;
          }

          lbl = emit("aload\t" + to_string(reg));
          index = getIndex(word);
          pushOnStack(index, Types::VAR_INT);
          emit("iaload");
          return lbl;
          break;
        case Types::ARRAY_FLOAT:
          reg = getReg(word,false);

          if(reg == -1){
            emit("bipush\t1000");
            emit("newarray\tfloat");
            reg = getReg(word);
            emit("astore\t" + to_string(reg));
            variableMap[word] = reg;
          }

          lbl = emit("aload\t" + to_string(reg));
          index = getIndex(word);
          pushOnStack(index, Types::VAR_INT);
          emit("faload");
          return lbl;
          break;
        case Types::ARRAY_CHAR:
          reg = getReg(word,false);

          if(reg == -1){
            emit("bipush\t1000");
            emit("newarray\tchar");
            reg = getReg(word);
            emit("astore\t" + to_string(reg));
            variableMap[word] = reg;
          }

          lbl = emit("aload\t" + to_string(reg));
          index = getIndex(word);
          pushOnStack(index, Types::VAR_INT);
          emit("caload");
          return lbl;
          break;
        case Types::ARRAY_BOOL:
          reg = getReg(word,false);

          if(reg == -1){
            emit("bipush\t1000");
            emit("newarray\tboolean");
            reg = getReg(word);
            emit("astore\t" + to_string(reg));
            variableMap[word] = reg;
          }

          lbl = emit("aload\t" + to_string(reg));
          index = getIndex(word);
          pushOnStack(index, Types::VAR_INT);
          emit("baload");
          return lbl;
          break; 
        default:
          break;
      }
      return -1;
    }

    void storeOnArray(const string &word, const Types::OperandType type){
      int reg; string index;
      switch(type){
        case Types::ARRAY_INT:
          reg = getReg(word,false);
          
          emit("istore_0");
          
          if(reg == -1){
            emit("bipush\t1000");
            emit("newarray\tint");
            reg = getReg(word);
            emit("astore\t" + to_string(reg));
            variableMap[word] = reg;
          }
          
          emit("aload\t" + to_string(reg));
          index = getIndex(word);
          pushOnStack(index, Types::VAR_INT);
          emit("iload_0");
          emit("iastore");
          break;
        case Types::ARRAY_FLOAT:
          reg = getReg(word,false);
          
          emit("fstore_0");
          
          if(reg == -1){
            emit("bipush\t1000");
            emit("newarray\tfloat");
            reg = getReg(word);
            emit("astore\t" + to_string(reg));
            variableMap[word] = reg;
          }
          
          emit("aload\t" + to_string(reg));
          index = getIndex(word);
          pushOnStack(index, Types::VAR_INT);
          emit("fload_0");
          emit("fastore");
          break;
        case Types::ARRAY_CHAR:
          reg = getReg(word,false);
          
          emit("istore_0");
          
          if(reg == -1){
            emit("bipush\t1000");
            emit("newarray\tchar");
            reg = getReg(word);
            emit("astore\t" + to_string(reg));
            variableMap[word] = reg;
          }
          
          emit("aload\t" + to_string(reg));
          index = getIndex(word);
          pushOnStack(index, Types::VAR_INT);
          emit("iload_0");
          emit("castore");
          break;
        case Types::ARRAY_BOOL:
          reg = getReg(word,false);
          
          emit("istore_0");
          
          if(reg == -1){
            emit("bipush\t1000");
            emit("newarray\tboolean");
            reg = getReg(word);
            emit("astore\t" + to_string(reg));
            variableMap[word] = reg;
          }
          
          emit("aload\t" + to_string(reg));
          index = getIndex(word);
          pushOnStack(index, Types::VAR_INT);
          emit("iload_0");
          emit("bastore");
          break;
        default:
          return;

        }
    }

    void storeOnReg(const int regId, const Types::OperandType type){
      switch(type){
        case Types::VAR_INT: case Types::VAR_BOOL:
          emit("istore\t" + to_string(regId));
          break;
        case Types::VAR_FLOAT:
          emit("fstore\t" + to_string(regId));
          break;
        default:
          return;
      }
    }

    Types::OperandType getType(const string &word){ 

      if(word == "var_bool(true)")  return Types::CONST_TRUE;
      if(word == "var_bool(false)") return Types::CONST_FALSE;
      if(word[0] == 't')  return Types::TEMP;
      
      if(word.find("var_float(const_f(") != word.npos ) return Types::CONST_FLOAT;
      if(word.find("var_int(const_i(")   != word.npos ) return Types::CONST_INT; //match
      if(word.find("var_bool(const_i(")   != word.npos ) return Types::CONST_INT; //match

      if( word.find("var_float(") != word.npos ){
        if(word.find("const_f(",9) != word.npos) return Types::CONST_FLOAT;
        else return Types::VAR_FLOAT;
      }
      if( word.find("var_int(") != word.npos ){
        if(word.find("const_i(",7) != word.npos) return Types::CONST_INT;
        else return Types::VAR_INT;
      }
      
      if( word.find("var_bool(") != word.npos ) return Types::VAR_BOOL;

      if( word.find("var_[float](") != word.npos ) return Types::ARRAY_FLOAT;
      if( word.find("var_[int](") != word.npos ) return Types::ARRAY_INT;
      if( word.find("var_[char](") != word.npos ) return Types::ARRAY_CHAR;
      if( word.find("var_[bool](") != word.npos ) return Types::ARRAY_BOOL;

      return Types::ERROR;
    }

    int emit(string s){
      
      if( mapNewLinesToLabel.find(fileLine) == mapNewLinesToLabel.end() ){
        mapNewLinesToLabel[fileLine] = label;
      }
      
      string l;
      l.append("\t" + to_string(label) + ": " + s);
      label++;

      convertedLines.push_back( pair<string, string> ( l,""));
      return label-1;
    }
    
    int emit(string s, string lbl){
      
      if( mapNewLinesToLabel.find(fileLine) == mapNewLinesToLabel.end() )
        mapNewLinesToLabel[fileLine] = label;

      string l;
      l.append("\t" + to_string(label) + ": " + s);
      label++;

      convertedLines.push_back( pair<string,string> (l,lbl));
      return label-1;
    }

    void showConstantPool(){
      cout << "Constant Pool:\n";

      for(unsigned i=0; i<constantPool.size(); i++){
        cout << "\t#" << i << " = Float\t" << constantPool[i] << "\n"; 
      }

    }

    void showConvertedLines(){
      cout << "{\n";
      for(unsigned i =0; i<convertedLines.size(); i++){
        if(convertedLines[i].second == "")
          cout << convertedLines[i].first << "\n";
        else{
          cout << convertedLines[i].first << "\t"; 
          string oldLbl =  convertedLines[i].second;
          int fL = labelLines[oldLbl];
          
          cout << mapNewLinesToLabel[fL] << "\n";
        }
      }
      cout << "}\n";

    }
  
};

#endif // BACKEND_H
