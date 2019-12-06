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
    
    ProgramCounter PC;  // PC = 0
    instructionFetch IF;
    Reg Register;
    
    vector <string> instruction = instructionFileRead(); // Loads Instruction File
    
    for(int i = 0; i < (instruction.size())/4; i ++){
        
        IF.setCurrentInstruction(PC.getInstruction(instruction));
        IF.setInstructionDetails();
        
        cout << "The rs register is: " << IF.rs << endl;
        cout << "The rt register is: " << IF.rt << endl;
        
        if (IF.rd.length() != 0){
            cout << "The rd register is: " << IF.rd << endl;
        }
        else{
            cout << "The offset of I Type is: " << IF.offset << endl;
        }
        
        Register.setSrcDest(IF.rs, IF.rt, IF.offset);
        cout << "The first source register is : " << Register.readRegister1
        << "The second source register is : " << Register.readRegister2
        << "The Destination Register is : " << Register.writeRegister;
        
        
        PC.PCNext();
        IF.clearInstructionDetails();
    }

    return 0;
}

