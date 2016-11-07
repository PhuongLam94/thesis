#ifndef WORKLIST_H
#define WORKLIST_H

#endif // WORKLIST_H
#include <map>
//This file is to define classes will use in constant propagation.

using namespace std;
//parent class for FlowWorkList and SSAWorkList
class BasicBlock;
class Statement;
class Binary;
class Const;
class Unary;
class Exp;
class WorkList{
protected:
    int typeOfWorkList;//1: flow work list, 2: ssa work list
public:
    bool isFlowWorkList(){return typeOfWorkList == 1;}
    bool isSSAWorkList(){return typeOfWorkList == 2;}
};
//class to define edges between bb, include one boolean to determine if this edge is executable or not
class FlowWorkList:WorkList{
public:
    FlowWorkList(){
        typeOfWorkList = 1;
    }
    BasicBlock* fromBB;
    BasicBlock* toBB;
    bool isExecutable = false;
};
class SSAWorkList:WorkList{
public:
    SSAWorkList(){
        typeOfWorkList = 2;
   }
   Statement* def;
   Statement* use;
};
class ConstantVariable{
public:
    int type; //1: top, 2: constant, 3: bottom
    Exp* variable; //two form: Const(i), i is an integer and m[Const(i)], i is an integer
};

class EvalExpressionVisitor{
public:
    ConstantVariable* visit(Const* c, map<Exp*, ConstantVariable*>& m);
    ConstantVariable* visit(Binary* c, map<Exp*, ConstantVariable*>& m);
    ConstantVariable* visit(Unary* c, map<Exp*, ConstantVariable*>& m);
};
