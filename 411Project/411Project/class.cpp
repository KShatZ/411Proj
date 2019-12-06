#include "class.hpp"


void ProgramCounter::PCNext(){
    
    PC += 4;
    cout << "Incrementing PC to address: "<< PC << endl;
    
    
};

string ProgramCounter::getInstruction(vector<string> instructionBank){
    
    string instruction;
    
    for(int i = PC; i < PC + 4; i++){
        
        instruction += instructionBank[i];
    }
    
    cout << "Grabbing instruction for execution" << endl;
    return instruction;
    
}

void instructionFetch::setCurrentInstruction(string instruction){
    
    currentInstruction = instruction;
    cout << "String received for instruction fetch"<< endl;
    cout << "Current instruction is: " << currentInstruction <<endl;

}

void instructionFetch::setInstructionDetails(){
    
    //OPCODE DECODE
    string OpCode;
    for (int i = 0; i < 6; i++){
        OpCode += currentInstruction[i];
        cout << OpCode << endl;
    }
    if (OpCode == RTYPE){
        
        string funct;
        for(int i = 26; i < 32; i++){
            funct += currentInstruction[i];
        }
        
        if (funct == FADDU){
            op = Raddu;
        }
        else if (funct == FSUBU){
            op = Rsubu;
        }
        else if (funct == FAND){
            op = RAnd;
        }
        else if (funct == FOR){
            op = Ror;
        }
        else if (funct == FNOR){
            op = Rnor;
        }
    }
    else if (OpCode == ADDIU){
        op = Iaddiu;
    }
    else if (OpCode == LW){
        op = Ilw;
    }
    else if (OpCode == SW){
        op = Isw;
    }
    else if (OpCode == BEQ){
        op = Ibeq;
    }
    else if (OpCode == JTYPE){
        op = Jj;
    }
    else if (OpCode == HALT){
        op = Jhalt;
    }
    
    //Registers Decode
    if(op != Jj or op != Jhalt){ // R and I Type Instructions
        
        if(op == 0 or op == 1 or op == 3 or op == 4 or op == 5){ // RType Instruction
            
            for(int i = 6; i < 11; i++){     // rs Register
                rs += currentInstruction[i];
            }
            for(int i = 11; i < 16; i++){   // rt Register
                rt += currentInstruction[i];
            }
            for(int i = 16; i < 21; i++){   // rd Register
                rd += currentInstruction[i];
            }
        }
        
        else{ // I-Type Instruction
            
            for(int i = 6; i < 11; i++){    // rs Register
                rs += currentInstruction[i];
            }
            for(int i = 11; i < 16; i++){   // rt Register
                rt += currentInstruction[i];
            }
            for(int i = 16; i < 32; i++){    //offset
                offset += currentInstruction[i];
            }
            
        }
        
    }
    else{
        
        for(int i = 6; i < 32; i++){   // J Address
            jAddress += currentInstruction[i];
        }
    }
    
    
    
}

void instructionFetch::clearInstructionDetails(){
    
    if (rs.length() != 0){    //Clears rd register
        rs.clear();
    }
    if (rt.length() != 0){    //Clears rd register
        rt.clear();
    }
    
    if (rd.length() != 0){    //Clears rd register
        rd.clear();
    }
    if(offset.length() != 0){ //Clears offset value
        offset.clear();
    }
    if(jAddress.length() != 0){
        jAddress.clear();
    }
}
