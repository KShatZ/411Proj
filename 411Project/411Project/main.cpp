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

string decimalToBinary(int c){
    
    
    int a[32],i;
    string result;
    
    if(c == 0){
        result = "00000000000000000000000000000000";
        return result;
    }
    
    for(i=0; c>0; i++)
    {
        a[i]=c%2;
        c= c/2;
    }
    
    for(i=i-1 ;i>=0 ;i--)
    {
        result += to_string(a[i]);
        
    }
    
    return result;
    
}

string addBinary(string a, string b){     // Adding two binary strings
    string result = ""; // Initialize result
    int s = 0;          // Initialize digit sum
    
    // Traverse both strings starting from last
    // characters
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1)
    {
        // Comput sum of last digits and carry
        s += ((i >= 0)? a[i] - '0': 0);
        s += ((j >= 0)? b[j] - '0': 0);
        
        // If current digit sum is 1 or 3, add 1 to result
        result = char(s % 2 + '0') + result;
        
        // Compute carry
        s /= 2;
        
        // Move to next digits
        i--; j--;
    }
    return result;
}



int main(int argc, const char * argv[]) {
    
    //Building Working Parts of Datapath
    Memory Mem;
    Reg Register;
    ProgramCounter PC;
    instructionFetch IF;
    ALU ALU;
    IALU IALU;
    vector<string> instructionVector;
    
    //Reading Instruction File and Initial Memory File
    instructionVector = instructionFileRead();
    Mem.setInitialMemory();
    
    PC.setBankSize(instructionVector);
    
    
    for(int i = 0; i < instructionVector.size()/4; i++){
        
        IF.setCurrentInstruction(PC.getInstruction(instructionVector));
        IF.setInstructionDetails();
        
        //IF Instruction is R-Type Do This
        if(IF.op == 0 or IF.op == 1 or IF.op == 3 or IF.op == 4 or IF.op == 5){ //R-Type Instruction
            
            Register.setSrcDest(IF.rs, IF.rt, IF.rd);
            ALU.setInputs(Register.getRegValue(Register.readRegister1), Register.getRegValue(Register.readRegister2));
            ALU.carryOutRInstruction(IF);
            Register.setReg(ALU.result, Register.writeRegister);
        
        }
        
        //If Instruction is I-Type Do This
        else if(IF.op == 2 or IF.op == 6 or IF.op == 8 or IF.op == 9){
            
            IALU.setInputs(IF.rs, IF.rt, IF.offset);
            IALU.carryOutIInstruction(IF, Mem, Register, PC);
            
            if(IF.op == 8 or IF.op == 2){ // LW ADDIU
                
                Register.setReg(IALU.writeValue, IALU.rt);
               
            }
            else if(IF.op == 9){  // SW
                
                Mem.writeMem(IALU.writeValue, (stoi(Register.registers.at(IALU.rs), nullptr, 2)) + IALU.offset);

            }
            else if(IF.op == 6){
                
                PC.setPC(IALU.PCAdressAdder + PC.PC);
                
            }
        }
        
        //If Instruction is J-Type Do This
        else if(IF.op == 7){   // Jump
            
            string finalAdress = "";
            string PCAdress = decimalToBinary(PC.PC);
            string b = addBinary(PCAdress, "00000000000000000000000000000000");  // B is PC in 32 bit form string
            string tempAdress = IF.jAddress;
            tempAdress += "00";  // Left Shift Two Position
            
            //Building adress
            for(int i = 0; i < 4; i++){
                
                finalAdress += b[i];
                
            }finalAdress = finalAdress + tempAdress;
            
            finalAdress = decimalToBinary(stoi(finalAdress, nullptr, 2) - 4);
            
            PC.setPC(finalAdress);
        }
        
        else if(IF.op == 10){
            
            ofstream file1;
            ofstream file2;
            file1.open("Memory.txt");
            file2.open("Registers.txt");
            
            for(int i = 0; i < 32; i++){
                
                file1 << Mem.memory.at(i) << endl;
                file2 << Register.registers.at(i) << endl;
                
            }
            
            file1.close();
            file2.close();
            
            cout << "Instructions were completed... Memory.txt,Register.txt created" << endl;
            
            
            return 0;
        }
        
        
        
        // Move to Next Instruction
        PC.PCNext();
        IF.clearInstructionDetails();
        ALU.clearValues();
    }
    
    
    
    
  
    
    
    
    
    
    
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

