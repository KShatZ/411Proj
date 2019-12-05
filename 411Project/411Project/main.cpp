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
    
    vector <string> instruction = instructionFileRead(); // Loads Instruction File
    
    IF.setCurrentInstruction(PC.getInstruction(instruction));
    
    cout << "The OP Code is: "     << IF.op << endl;
    cout << "The rs register is: " << IF.rs << endl;
    cout << "The rt register is: " << IF.rt << endl;

    if (IF.rt.length() != 0){
        cout << "The rd register is: " << IF.rd << endl;
    }
    else{
        cout << "The offset of I Type is: " << IF.offset << endl;
    }

    
    
    return 0;
}

