#include "ast.hpp"

#include <string>
#include <regex>

static int makeNameUnq=0;
const static std::string zeroReg="zero";


//all register are one time use, excpet the variable register

//variable in this code exist as a register
//when read variable, a copy of variable register is returned to the destReg (i.e. snipshot)
//when modify the variable, the variable register need to be the destReg, the update will be reflected on the future read


inline void copyReg(const std::string& regDst, const std::string& reg){
  //copy register value by add 0
  add(regDst,reg,zeroReg);
}

static std::string makeReg()
{
    return "reg_"+std::to_string(makeNameUnq++);
}


static std::string makeLabel()
{
    return "label_"+std::to_string(makeNameUnq++);
}

void CompileRec(
    std::string destReg,    // The name of the register to put the result in
    TreePtr program
){
    std::regex reNum("^-?[0-9]+$");
    std::regex reId("^[a-z][a-z0-9]*$");

    if( regex_match( program->type, reNum ) ){
        constant(destReg,program->type);
        // std::cout<<"const "<<destReg<<" "<<program->type<<std::endl;

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
      CompileRec(program->value,program->branches.at(0));
      copyReg(destReg,program->value);


    }else if(program->type=="Seq"){
        for(unsigned i=0; i<program->branches.size(); i++){
            CompileRec(destReg, program->branches[i]);
        }

    }else if(program->type=="If"){

    }else if(program->type=="While"){

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
