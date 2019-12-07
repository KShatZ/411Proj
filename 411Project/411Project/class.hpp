
#ifndef classes_hpp
#define classes_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "global.h"

using namespace std;




class ProgramCounter{

public:
    int PC = 0;
    string currentInstruction;
    
    
public:
    
    void PCNext();
    string getInstruction(vector<string> instructionBank);
    
};

class controlUnit{
    
    bool RegDst;
    bool Jump;
    bool Branch;
    bool MemRead;
    bool MemtoReg;
    bool ALUOp;
    bool MemWrite;
    bool ALUSrc;
    bool RegWrite;
    
};

class instructionFetch{

public:
    InstructionName op;
    string rs;
    string rt;
    string rd;
    string offset;
    string currentInstruction;
    string jAddress;
    
public:
    
    void setCurrentInstruction(string instruction);
    void setInstructionDetails();
    void clearInstructionDetails();
    
};

class Reg{
    
public:
    
    vector<string> registers;
    
    int readRegister1;  // First Source Register  (rs)
    int readRegister2;  // Second Source Register (rt)
    int writeRegister;  // Destination Register   (rd)
    string writeData;   // Data to be written  (32 bits)

public:
    
    string readData1; //Contents of source register 1 (rs)
    string readData2; //Contents of source register 2 (rt)
    
public:
    Reg();
    void setSrcDest(string readReg1, string readReg2, string writeReg);
    void setReg(string value, int R);
    string getRegValue(int R);
    //void clearReg(int R);
    // Function to write into text file
};

class ALU{
    
public:
    
    string input1;
    string input2;
    string result;
    
public:
    
    void carryOutInstruction(instructionFetch instruction);
    void setInputs(string a, string b);
    void clearValues();
    string addBinary (string a, string b);
    string twoCompSub(string a);
    string decimalToBinary(int c);
    
};



class Memory{
    
public:
    vector <string> memory;
    
public:

    void writeMem(string value, int M);
    string getMemValue(int M);
    void setInitialMemory();
    //Function to write into text file
};



#endif /* classes_hpp */
