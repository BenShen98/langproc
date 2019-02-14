#include "ast.hpp"

#include <string>
#include <regex>

static int makeNameUnq=0;

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
        std::cout<<"const "<<destReg<<" "<<program->type<<std::endl;

    }else if( regex_match( program->type, reId ) ){
        std::string constReg = makeReg();
        constant(constReg,program->type);


    }else if(program->type=="Input"){


    }else if(program->type=="Param"){
      param(destReg,program->value);

    }else if(program->type=="Output"){

    }else if(program->type=="LessThan"){

    }else if(program->type=="Add"){
      std::string regA=makeReg();
      CompileRec(regA, program->branches.at(0));
      std::string regB=makeReg();
      CompileRec(regB, program->branches.at(1));

    }else if(program->type=="Sub"){

    }else if(program->type=="Assign"){

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

    // Compile the whole thing
    CompileRec(res, program);

    // Put the result out
    halt(res);
}
