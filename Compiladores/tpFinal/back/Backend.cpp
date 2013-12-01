#include "Backend.h"
#include <stdlib.h>
#include <cctype>

Backend::Backend(){
  currentIndex = 1;
  label = 0;
  fileLine = 0;

  for(int i=0; i<4; i++)
    freeRegs.push_back(i);
}

void Backend::processLine(vector<string> &words, const string &type){

  vector<string> labels = getLabels(words, fileLine);

  if( type ==  "=" and words.size() == 3 ){
    string dest = words[0];
    Types::OperandType destType = getType(dest);

    string orig = words[2];
    Types::OperandType origType = getType(orig);

    pushOnStack(orig, origType);

    
    int regId = getReg(dest);

    if(destType == Types::ARRAY_INT || destType == Types::ARRAY_FLOAT || 
        destType == Types::ARRAY_CHAR || destType == Types::ARRAY_BOOL ){
      storeOnArray(dest, destType);
    }

    else{
      storeOnReg(regId, destType);
      variableMap[dest] = regId;
    }

  }

  else if( type == "iffalse" ){
    string op1 = words[1];
    Types::OperandType op1Type = getType(op1);
    pushOnStack(op1,op1Type);

    string op2 = words[3];
    Types::OperandType op2Type = getType(op2);
    pushOnStack(op2,op2Type);
    
    if( words[2] == ">" ) emit("if_icmple",words[5] );
    if( words[2] == ">=" ) emit("if_icmplt",words[5] );
    
    if( words[2] == "<" ) emit("if_icmpge",words[5] );
    if( words[2] == "<=" ) emit("if_icmpgt",words[5] );
    
    if( words[2] == "==" ) emit("if_icmpne",words[5] );
    if( words[2] == "!=" ) emit("if_icmpe",words[5] );

//      cout << "\t\t\t\t\t\t" << words[5] << "to" << (labelLines[words[5]]) << "\n";
  }
  
  else if( type == "if" ){
    string op1 = words[1];
    Types::OperandType op1Type = getType(op1);
    pushOnStack(op1,op1Type);

    string op2 = words[3];
    Types::OperandType op2Type = getType(op2);
    pushOnStack(op2,op2Type);
    
    if( words[2] == "<=" ) emit("if_icmple",words[5] );
    if( words[2] == "<" ) emit("if_icmplt",words[5] );
    
    if( words[2] == ">" ) emit("if_icmpgt",words[5] );
    if( words[2] == ">=" ) emit("if_icmpge",words[5] );
    
    if( words[2] == "!=" ) emit("if_icmpne",words[5] );
    if( words[2] == "==" ) emit("if_icmpe",words[5] );

//      cout << "\t\t\t\t\t\t" << words[5] << "to" << (labelLines[words[5]]) << "\n";
  }

  else if( type == "goto" ){
    emit("goto", words[1]);
  }

  else if( ( type == "(i+)" or type == "(i-)" or type == "(i*)" or type == "(i/)" ) 
      and words.size() == 5){
    string dest = words[0];
    Types::OperandType destType = getType(dest);

    string op1 = words[2];
    Types::OperandType op1Type = getType(op1);
    pushOnStack(op1,op1Type);

    string op2 = words[4];
    Types::OperandType op2Type = getType(op2);
    pushOnStack(op2,op2Type);

    if( type == "(i+)" )  emit("iadd");
    if( type == "(i-)" )  emit("isub");
    if( type == "(i*)" )  emit("imul");
    if( type == "(i/)" )  emit("idiv");

    int regId = getReg(dest);
    
    if(destType == Types::ARRAY_INT || destType == Types::ARRAY_FLOAT || 
        destType == Types::ARRAY_CHAR || destType == Types::ARRAY_BOOL ){
      storeOnArray(dest, destType);
    }

    else{
      storeOnReg(regId, Types::VAR_INT);
      variableMap[dest] = regId;
    }


  }


  else if( ( type == "(f+)" or type == "(f-)" or type == "(f*)" or type == "(f/)" ) 
      and words.size() == 5){
    string dest = words[0];
    Types::OperandType destType = getType(dest);

    string op1 = words[2];
    Types::OperandType op1Type = getType(op1);
    pushOnStack(op1,op1Type);

    string op2 = words[4];
    Types::OperandType op2Type = getType(op2);
    pushOnStack(op2,op2Type);

    if( type == "(f+)" )  emit("fadd");
    if( type == "(f-)" )  emit("fsub");
    if( type == "(f*)" )  emit("fmul");
    if( type == "(f/)" )  emit("fdiv");

    int regId = getReg(dest);
    
    if(destType == Types::ARRAY_INT || destType == Types::ARRAY_FLOAT || 
        destType == Types::ARRAY_CHAR || destType == Types::ARRAY_BOOL ){
      storeOnArray(dest, destType);
    }

    else{
      storeOnReg(regId, Types::VAR_FLOAT);
      variableMap[dest] = regId;
    }


  }

  else{
    emit("");
  }

  fileLine++;
  return;
}

vector<string> Backend::getLabels(vector<string> &words, int fileLine){
  vector<string> labels;

  for(unsigned i=0; i<words.size(); i++){   
    if( words[i][0] == 'L' ){ 
      string label = "L";
      for(unsigned j=1; j<words[i].size(); j++){
        if(words[i][j] == ':'){
          labelLines[label] = fileLine;
          labels.push_back(label);
          label = "";
        }
        else
          label.push_back( words[i][j] );
      }
      words.erase(words.begin() + i);
      i--;
    }
    else
      break;
  }

  return labels;
}

void Backend::program(){
    pair<string, vector<string> > line = scanner.scanLine();

    while( !line.second.empty() ){
      lines.push_back( line );
      line = scanner.scanLine();
    }
    
    for(unsigned i=0; i<lines.size(); i++){
      processLine(lines[i].second,lines[i].first);
    }

    showConstantPool();
    showConvertedLines();

}
