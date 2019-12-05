
#ifndef classes_hpp
#define classes_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "global.h"

using namespace std;




class ProgramCounter{
    
    int PC = 0;
    string currentInstruction;
    
    
public:
    
    void PCNext();
    string getInstruction(vector<string> instructionBank);
    
};

class instructionFetch{

public:
    InstructionName op;
    string rs;
    string rt;
    string rd;
    string offset;
    string currentInstruction;
    
public:
    
    void setCurrentInstruction(string instruction);
    void setInstructionDetails();
    
};



#endif /* classes_hpp */
