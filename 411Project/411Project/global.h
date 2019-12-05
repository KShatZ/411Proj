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
