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

    return instruction;
    
}

void ProgramCounter::setBankSize(vector<string> instructionBank){
    
    sizeOfBank = instructionBank.size();
    
}

void ProgramCounter::setPC(string address){

    PC = stoi(address, nullptr, 2);
    
}

void ProgramCounter::setPC(int address){
    
    PC = address;
    
}

void instructionFetch::setCurrentInstruction(string instruction){
    
    currentInstruction = instruction;

}

void instructionFetch::setInstructionDetails(){
    
    //OPCODE DECODE
    string OpCode;
    
    for (int i = 0; i < 6; i++){
        OpCode += currentInstruction[i];
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
            
            if(op == 7){
                
                for (int i = 6; i < 32; i++){
                    jAddress += currentInstruction[i];
                }
            }
            else{
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


Reg::Reg() {
    
    //Setting up register vector
    
    for(int i = 0; i < 32; i++){
        
        registers.push_back("");
        
        for(int j = 0; j < 32; j++){
            
            registers[i] += "0";
        }
    }
    
}

void Reg::setSrcDest(string readReg1, string readReg2, string writeReg){
    
    readRegister1 = stoi(readReg1, nullptr, 2);
    readRegister2 = stoi(readReg2, nullptr, 2);
    writeRegister = stoi(writeReg, nullptr, 2);
    
}

void Reg:: setReg(string value, int R){
    
    registers[R] = value;
}

string Reg::getRegValue(int R){
    
    return registers.at(R);
    
}

void Memory::writeMem(string value, int M){
    
    memory[M] = value;
    
}

string Memory::getMemValue(int M){
    
    return memory.at(M);
}

void Memory::setInitialMemory(){
    
    fstream MemoryStream;
    string fileName;
    
    cout << "Enter file name of initial memory state: " ;
    cin >> fileName;
    
    MemoryStream.open(fileName);
    
    if (MemoryStream.is_open()){
        
        while(!MemoryStream.eof()){ //While end of file is not reached
            
            string stringLine;
            getline(MemoryStream,stringLine);
            memory.push_back(stringLine);
            
        }
        
    }
    
    else{
        
        cout << "Can't find " << fileName << ", initial memory is not set" << endl;
    }
    
}

void ALU::carryOutRInstruction(instructionFetch instruction){
    
    if(instruction.op == 0){ // Add
        
        result = addBinary(input1, input2);
    }

    else if(instruction.op == 1){ // Subtract
        
        int a = stoi(input1, nullptr, 2);
        int b = stoi(input2, nullptr, 2);
        
        int c = a - b;
        
        result = decimalToBinary(c);
        
    }
    
    else if(instruction.op == 3){ // and
        
        for(int i = 0; i < 32; i++){
            
            if(input1[i] == '1' and input2[i] == '1'){
                
                result += '1';
                
            }
            else{
                
                result += '0';
                
            }
        }
        
        
    }
    else if(instruction.op == 4){ // or
        
        for(int i = 0; i < 32; i++){
            
            if(input1[i] == '1' or input2[i] == '1'){
                
                result += '1';
                
            }
            else{
                
                result += '0';
                
            }
        }
        
    }
    else if(instruction.op == 5){ // nor
        
        for(int i = 0; i < 32; i++){
            
            if(input1[i] == '0' and input2[i] == '0'){
                
                result += '1';
                
            }
            else{
                result += '0';
            }
            
        }
        
    }
    
}

string ALU::addBinary(string a, string b){     // Adding two binary strings
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



string ALU::decimalToBinary(int c){
   
    int a[32],i;
    string result;
    
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

void ALU::setInputs(string a, string b){
    
    input1 = a;
    input2 = b;
    
}

void ALU::clearValues(){
    
    input1.clear();
    input2.clear();
    result.clear();
    
}


void IALU::setInputs(string a, string b, string c){
    
    rs     = stoi(a, nullptr, 2);
    rt     = stoi(b, nullptr, 2);
    offset = stoi(c,nullptr,2);
    
}

void IALU::carryOutIInstruction(instructionFetch instruction, Memory memVector, Reg regVector, ProgramCounter PC){
    
    //LW
    if(instruction.op == 8){
        
        writeValue = memVector.memory.at(stoi(regVector.registers.at(rs), nullptr, 2) + offset);
        
    }
    
    //SW
    else if(instruction.op == 9){
        
        writeValue = regVector.registers.at(rt);
        
        
    }
    
    //ADDIU
    else if(instruction.op == 2){
        
        string tempValue = "00000000000000000000000000000000";
        writeValue = decimalToBinary(stoi(regVector.registers.at(rs), nullptr, 2) + offset);
        writeValue = addBinary(writeValue, tempValue);
        
    }
    
    //BEQ
    else if(instruction.op == 6){
        
        if(regVector.registers.at(rs) == regVector.registers.at(rt)){
            
            int a = 4 * offset;
            cout << "Branching" << endl;
            PCAdressAdder = a;
        }
            
            else{
                
                cout << "Cant Branch Sorry" << endl;
            }
            
        }
    
}

string IALU::decimalToBinary(int c){
    
    int a[32],i;
    string result;
    
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

string IALU::addBinary(string a, string b){     // Adding two binary strings
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



