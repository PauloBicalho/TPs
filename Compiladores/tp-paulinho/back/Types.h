#ifndef TYPES_H
#define TYPES_H

class Types{

  public:
    enum OperandType{
      ARRAY_INT,
      ARRAY_FLOAT,
      ARRAY_CHAR,
      ARRAY_BOOL,
      VAR_INT,
      VAR_FLOAT,
      VAR_BOOL,
      TEMP,
      CONST_INT,
      CONST_FLOAT,
      CONST_TRUE,
      CONST_FALSE,
      ERROR
    };

    enum OperandPosition{
      REG_0,
      REG_1,
      REG_2,
      REG_3,
      STACK
    };
};



#endif //TYPES_H
