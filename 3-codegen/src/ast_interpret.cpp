#include "ast.hpp"

#include <regex>

//Seq [ Assign : a [ a ] ] ??? not valid?
//when return non-zero, 1 was used


int32_t Interpret(
    InterpretContext &context, // Contains the parameters and variable bindings
    TreePtr program
){
    std::regex reNum("^-?[0-9]+$");
    std::regex reId("^[a-z][a-z0-9]*$");

    if( regex_match(program->type, reNum) ){
      return std::atol(program->type.c_str());

    }else if( regex_match(program->type, reId) ){
      return context.bindings.at(program->type);

    }else if(program->type=="Input"){
      int input;
      std::cin>>input;
      return input;

    }else if(program->type=="Param"){
      unsigned index=atol(program->value.c_str());
      auto value=context.params.at(index);
      return value;

    }else if(program->type=="Output"){
      int32_t val=Interpret(context, program->branches.at(0));
      std::cout<<val<<std::flush;
      return val;

    }else if(program->type=="LessThan"){
      int R=Interpret(context,program->branches.at(0));
      int L=Interpret(context,program->branches.at(1));
      return (R<L)? 1 : 0;

    }else if(program->type=="Add"){
      int A=Interpret(context,program->branches.at(0));
      int B=Interpret(context,program->branches.at(1));
      return A+B;

    }else if(program->type=="Sub"){
      int A=Interpret(context,program->branches.at(0));
      int B=Interpret(context,program->branches.at(1));
      return A-B;

    }else if(program->type=="Assign"){

      int val=Interpret(context,program->branches.at(0));
      // if variable exist => overwirte its value
      // if variable not exist => insert new variable with the assigned value
      context.bindings[program->value]=val;
      return val;

    }else if(program->type=="Seq"){
      int val;
      for(auto itr=program->branches.begin(); itr!=program->branches.end(); ++itr){
        val=Interpret(context, *itr);
      }
      return val;

    }else if(program->type=="If"){
      if( Interpret(context, program->branches.at(0) ) != 0 ){
        return Interpret( context, program->branches.at(1) );
      }else{
        return Interpret( context, program->branches.at(2) );
      }

    }else if(program->type=="While"){
      while ( Interpret(context, program->branches.at(0)) != 0 ) {
        Interpret(context, program->branches.at(1));
      }
      return 0;

    }else{
        throw std::runtime_error("Unknown construct '"+program->type+"'");
    }
}
