#include "worklist.h"
#include "statement.h"
#include "basicblock.h"
#include "exp.h"

ConstantVariable* EvalExpressionVisitor::visit(Const *c, map<Exp *, ConstantVariable *> &m){
    ConstantVariable* retValue = new ConstantVariable();
    if (!c->isIntConst()){
        retValue->type = 3;
    } else {
        retValue->type = 2;
        retValue->variable = c;
    }
    return retValue;
}
