// CMSC 411
// SINGLE CYCLE MIPS PROCESSOR - KIRILL SHATS

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "class.hpp"

using namespace std;

//Text FIle Reading Functions
vector <string> instructionFileRead(){
    
    fstream instructionStream;
    string fileName;
    vector <string> instructionBank;
    
    cout << "Enter the name of the instruction file you want to open: ";
    cin >> fileName;
    instructionStream.open(fileName);
    
    if (instructionStream.is_open()){
        
        while(!instructionStream.eof()){ //While end of file is not reached
            
            string stringLine;
            getline(instructionStream,stringLine);
            instructionBank.push_back(stringLine);
            
        }
        
    }
    
    else{
        
        cout << "Can't find " << fileName << ", instruction bank will be empty" << endl;
    }
    
    return instructionBank;
}


int main(int argc, const char * argv[]) {
    
    //Building Working Parts of Datapath
    Memory Mem;
    Reg Register;
    ProgramCounter PC;
    instructionFetch IF;
    ALU ALU;
    vector<string> instructionVector;
    
    //Reading Instruction File and Initial Memory File
    instructionVector = instructionFileRead();
    Mem.setInitialMemory();
    
    
    for(int i = 0; i < instructionVector.size()/4; i++){
        
        IF.setCurrentInstruction(PC.getInstruction(instructionVector));
        IF.setInstructionDetails();
        
        //IF Instruction is R-Type Do This
        if(IF.op == 0 or IF.op == 1 or IF.op == 3 or IF.op == 4 or IF.op == 5){ //R-Type Instruction
            
            Register.setSrcDest(IF.rs, IF.rt, IF.rd);
            ALU.setInputs(Register.getRegValue(Register.readRegister1), Register.getRegValue(Register.readRegister2));
            ALU.carryOutInstruction(IF);
            Register.setReg(ALU.result, Register.writeRegister);
        }
        
        else{
            cout << "I and J are not yet supported" << endl;
        }
        
        
    
        //If Instruction is I-Type Do This
        //If Instruction is J-Type Do This
        
        // Move to Next Instruction
        PC.PCNext();
        IF.clearInstructionDetails();
    }
    
    cout << Register.registers.at(9) << endl;
    cout << Register.registers.at(10) << endl;
    
    cout << Register.registers.at(20) << endl;
    
    
    
  
    
    
    
    
    
    
//    for(int i = 0; i < (instructionVector.size())/4; i ++){
//
//        IF.setCurrentInstruction(PC.getInstruction(instructionVector));
//        IF.setInstructionDetails();
//
//        cout << "The rs register is: " << IF.rs << endl;
//        cout << "The rt register is: " << IF.rt << endl;
//
//        if (IF.rd.length() != 0){
//            cout << "The rd register is: " << IF.rd << endl;
//        }
//        else{
//            cout << "The offset of I Type is: " << IF.offset << endl;
//        }
//
//        Register.setSrcDest(IF.rs, IF.rt, IF.offset);
//        cout << "The first source register is : " << Register.readRegister1
//        << "The second source register is : " << Register.readRegister2
//        << "The Destination Register is : " << Register.writeRegister;
//
//
//        PC.PCNext();
//        IF.clearInstructionDetails();
//    }

    return 0;
}

