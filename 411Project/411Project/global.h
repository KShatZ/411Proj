#ifndef global_h
#define global_h

#include <iostream>
#include <string>

using namespace std;

enum InstructionName{
    Raddu,  //0
    Rsubu,  //1
    Iaddiu, //2
    RAnd,   //3
    Ror,    //4
    Rnor,   //5
    Ibeq,   //6
    Jj,     //7
    Ilw,    //8
    Isw,    //9
    Jhalt   //10
};



//Register Constants

inline const string R0  = "00000";
inline const string R1  = "00001";
inline const string R2  = "00010";
inline const string R3  = "00011";
inline const string R4  = "00100";
inline const string R5  = "00101";
inline const string R6  = "00110";
inline const string R7  = "00111";
inline const string R8  = "01000";
inline const string R9  = "01001";
inline const string R10 = "01010";
inline const string R11 = "01011";
inline const string R12 = "01100";
inline const string R13 = "01101";
inline const string R14 = "01110";
inline const string R15 = "01111";
inline const string R16 = "10000";
inline const string R17 = "10001";
inline const string R18 = "10010";
inline const string R19 = "10011";
inline const string R20 = "10100";
inline const string R21 = "10101";
inline const string R22 = "10110";
inline const string R23 = "10111";
inline const string R24 = "11000";
inline const string R25 = "11001";
inline const string R26 = "11010";
inline const string R27 = "11011";
inline const string R28 = "11100";
inline const string R29 = "11101";
inline const string R30 = "11110";
inline const string R31 = "11111";


//
inline const string RTYPE = "000000"; // R-Type
inline const string ADDIU = "001001"; // R-Type
inline const string LW    = "100011"; // I-Type
inline const string SW    = "101011"; // I-Type
inline const string BEQ   = "000100"; // I-Type
inline const string JTYPE = "000010"; // J-Type
inline const string HALT  = "111111"; // J-Type

//Funcs
inline const string FADDU = "100001";
inline const string FSUBU = "100011";
inline const string FAND  = "100100";
inline const string FOR   = "100101";
inline const string FNOR  = "100111";
#endif /* global_h */
