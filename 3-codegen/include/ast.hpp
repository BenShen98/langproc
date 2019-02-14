#ifndef generic_ast_hpp
#define generic_ast_hpp

#include <string>
#include <iostream>
#include <memory>
#include <initializer_list>
#include <vector>
#include <map>

struct Tree;

typedef std::shared_ptr<Tree> TreePtr;


struct Tree
{
    Tree(std::string _type, std::string _value, const std::vector<TreePtr> &_branches)
        : type(_type)
        , value(_value)
        , branches(_branches)
    {}

    Tree(std::string _type, std::string _value)
        : type(_type)
        , value(_value)
    {}

    template<class ...TArgs>
    Tree(std::string _type, TArgs ...args)
        : type(_type)
        , branches{args...}
    {}

    std::string type;
    std::string value;
    std::vector<TreePtr> branches;
};

// by spec, the output of program will be on STDCOUT

// Establishes a label (jump target)
inline void label(const std::string& str){
  std::cout<<":"<<str<<" "<<std::flush;//space or change line?
}

// Loads the decimal immediate value into the destination register
inline void constant(const std::string& reg, const std::string& imm){
  std::cout<<"const "<<reg<<' '<<imm<<'\n'<<std::flush;
}
inline void constant(const std::string& reg, int imm){
  std::string imm_str=std::to_string(imm);
  constant(reg,imm_str);
}

// Read a value from input, and put it into the destination register.
inline void input(const std::string& reg){
  std::cout<<"input "<<reg<<'\n'<<std::flush;
}

// Place the input parameter with index immVal into destination register.
inline void param(const std::string& reg, const std::string& imm){
  std::cout<<"param "<<reg<<' '<<imm<<'\n'<<std::flush;
}
inline void param(const std::string& reg, int imm){
  std::string imm_str=std::to_string(imm);
  param(reg,imm_str);
}


// Write the value in source register into the output stream.
inline void output(const std::string& reg){
  std::cout<<"output "<<reg<<'\n'<<std::flush;
}

// Add the two source registers and write to destination.
inline void add(const std::string& regDst, const std::string& regA, const std::string& regB){
  std::cout<<"add "<<regDst<<' '<<regA<<' '<<regB<<'\n'<<std::flush;
}

// Subtract the two source registers and write to destination.
inline void sub(const std::string& regDst, const std::string& regA, const std::string& regB){
  std::cout<<"sub "<<regDst<<' '<<regA<<' '<<regB<<'\n'<<std::flush;
}

// If regA < regB, then regDst=1, otherwise regDst=0.
inline void lt(const std::string& regDst, const std::string& regA, const std::string& regB){
  std::cout<<"lt "<<regDst<<' '<<regA<<' '<<regB<<'\n'<<std::flush;
}

// If regA == regB, then jump to label.
inline void beq(const std::string& regA, const std::string& regB, const std::string& label){
  std::cout<<"beq "<<regA<<' '<<regB<<" :"<<label<<'\n'<<std::flush;
}

// If regA != regB, then jump to label.
inline void bne(const std::string& regA, const std::string& regB, const std::string& label){
  std::cout<<"bne "<<regA<<' '<<regB<<" :"<<label<<'\n'<<std::flush;
}

// Halt the program and return value in srcReg.
inline void halt(const std::string& Reg){
  std::cout<<"halt "<<Reg<<'\n'<<std::flush;
}





// inline TreePtr Number(int32_t x)
// //{ return std::make_shared<Tree>("Number", std::to_string(x)); }
// { return std::make_shared<Tree>(std::to_string(x)); }
//
// inline TreePtr Variable(std::string id)
// //{ return std::make_shared<Tree>("Variable", id); }
// { return std::make_shared<Tree>(id); }
//
// inline TreePtr Input(std::string id)
// { return std::make_shared<Tree>("Input", id); }
//
// inline TreePtr Output(TreePtr expr)
// { return std::make_shared<Tree>("Output", expr); }
//
//
// inline TreePtr Add(TreePtr left, TreePtr right)
// { return std::make_shared<Tree>("Add", left, right); }
//
// inline TreePtr Sub(TreePtr left, TreePtr right)
// { return std::make_shared<Tree>("Sub", left, right); }
//
// inline TreePtr LessThan(TreePtr left, TreePtr right)
// { return std::make_shared<Tree>("LessThan", left, right); }
//
//
// inline TreePtr Seq(std::initializer_list<TreePtr> statements)
// { return std::make_shared<Tree>("Seq", statements); }
//
// inline TreePtr While(TreePtr cond, TreePtr stat)
// { return std::make_shared<Tree>("While", cond, stat ); }
//
// //inline TreePtr IfElse(TreePtr cond, TreePtr stat1, TreePtr stat2)
// //{ return std::make_shared<Tree>("IfElse", cond, stat1, stat2); }
//
// inline TreePtr If(TreePtr cond, TreePtr stat1)
// { return std::make_shared<Tree>("If", cond, stat1); }

TreePtr Parse(
    std::istream &src
);

void PrettyPrint(
    std::ostream &dst,
    TreePtr node,
    std::string indent=""
);

struct InterpretContext
{
    std::vector<int32_t> params;
    std::map<std::string,int32_t> bindings;
};

int32_t Interpret(
    InterpretContext &context,
    TreePtr program
);

void Compile(
    TreePtr program
);


#endif
