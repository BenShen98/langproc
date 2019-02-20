#include "ast.hpp"

#include <string>
#include <regex>

static int makeNameUnq=0;
const static std::string zeroReg="zero";


//all register are one time use (NOT TRUE), excpet the variable register

//variable in this code exist as a register
//when read variable, a copy of variable register is returned to the destReg (i.e. snipshot)
//when modify the variable, the variable register need to be the destReg, the update will be reflected on the future read

//this naive compiler will only assembly in line by line fission, does not put branch in the end of assembly file

/* for if struct:
  `code for cmp`
  `if false, jump to label_zero_cmp`

  `:label_non_zero_cmp`   // if true, automatically execute label_non_zero_cmp, (this label is not produced in code)
  `code for non zero condition (true)`
  `jump to :label_end_if`

  `:label_zero_cmp`
  `code for zero condition (false)`

  `:label_end_if`
  `other code OUTSIDE if`

*/


/* for while struct:

  `:label_start_while`
  `code for cmp`
  `if false, jump to :label_end_while`

  `code INSIDE while loop`
  `jump to label_start_while`

  `:label_end_while`
  `other code OUTSIDE while`

*/

inline void copyReg(const std::string& regDst, const std::string& reg){
  //copy register value by add 0
  add(regDst,reg,zeroReg);
}

static std::string makeReg()
{
    return "Reg_"+std::to_string(makeNameUnq++);
}


static std::string makeLabel()
{
    return "Label_"+std::to_string(makeNameUnq++);
}

void CompileRec(
    std::string destReg,    // The name of the register to put the result in
    TreePtr program
){
    std::regex reNum("^-?[0-9]+$");
    std::regex reId("^[a-z][a-z0-9]*$");

    if( regex_match( program->type, reNum ) ){
        constant(destReg,program->type);

    }else if( regex_match( program->type, reId ) ){
        //a snipshot of variable is created, passed as the return value
        copyReg(destReg,program->type);

    }else if(program->type=="Input"){
      input(destReg);

    }else if(program->type=="Param"){
      param(destReg,program->value);

    }else if(program->type=="Output"){
      CompileRec(destReg,program->branches.at(0));
      output(destReg);

    }else if(program->type=="LessThan"){
      std::string regA=makeReg();
      CompileRec(regA, program->branches.at(0));
      std::string regB=makeReg();
      CompileRec(regB, program->branches.at(1));
      lt(destReg,regA,regB);


    }else if(program->type=="Add"){
      std::string regA=makeReg();
      CompileRec(regA, program->branches.at(0));
      std::string regB=makeReg();
      CompileRec(regB, program->branches.at(1));
      add(destReg,regA,regB);

    }else if(program->type=="Sub"){
      std::string regA=makeReg();
      CompileRec(regA, program->branches.at(0));
      std::string regB=makeReg();
      CompileRec(regB, program->branches.at(1));
      sub(destReg,regA,regB);

    }else if(program->type=="Assign"){
      //introduce a new variable register named program->value
      CompileRec(destReg,program->branches.at(0));
      copyReg(program->value,destReg);


    }else if(program->type=="Seq"){
        for(unsigned i=0; i<program->branches.size(); i++){
            CompileRec(destReg, program->branches[i]);
        }

    }else if(program->type=="If"){
      std::string label_zero_cmp=makeLabel();
      std::string label_end_if=makeLabel();

      //code for cmp & branch for false
      std::string cmpVal=makeReg();
      CompileRec(cmpVal,program->branches.at(0));
      beq(cmpVal,zeroReg,label_zero_cmp);

      //:label_non_zero_cmp (this lable does not show in assembly)
      CompileRec(destReg,program->branches.at(1));
      beq(zeroReg,zeroReg,label_end_if); //uncon jump

      //:label_zero_cmp
      label(label_zero_cmp);
      CompileRec(destReg,program->branches.at(2));

      //:label_end_if
      label(label_end_if);

    }else if(program->type=="While"){
      std::string label_start_while=makeLabel();
      std::string label_end_while=makeLabel();

      //code for cmp and exit while
      std::string cmpVal=makeReg();
      label(label_start_while);
      CompileRec(cmpVal,program->branches.at(0));
      beq(cmpVal,zeroReg,label_end_while);

      //:label_start_while
      CompileRec(cmpVal,program->branches.at(1));
      beq(zeroReg,zeroReg,label_start_while);

      //:label_end_while
      label(label_end_while);
      copyReg(destReg,zeroReg);

    }else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }
}

void Compile(
    TreePtr program
){
    // Create a register to hold the final result
    std::string res=makeReg();

    // create 0 constant register
    // std::string zeroReg="zero";
    constant(zeroReg,0);

    // Compile the whole thing
    CompileRec(res, program);

    // Put the result out
    halt(res);
}
