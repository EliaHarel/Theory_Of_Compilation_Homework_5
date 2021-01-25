#ifndef _236360_3_
#define _236360_3_

#include <vector>
#include <string>

using namespace std;

namespace output {
    void endScope();

    void printID(const std::string& id, int offset, const std::string& type);

    /* Do not save the string returned from this function in a data structure
        as it is not dynamically allocated and will be destroyed(!) at the end of the calling scope.
    */
    std::string makeFunctionType(const std::string& retType, vector<string>& argTypes);

    void errorLex(int lineno);

    void errorSyn(int lineno);

    void errorUndef(int lineno, const std::string& id);

    void errorDef(int lineno, const std::string& id);

    void errorUndefFunc(int lineno, const std::string& id);

    void errorMismatch(int lineno);

    void errorPrototypeMismatch(int lineno, const std::string& id, vector<string>& argTypes);

    void errorUnexpectedBreak(int lineno);

    void errorUnexpectedContinue(int lineno);

    void errorMainMissing();

    void errorByteTooLarge(int lineno, const std::string& value);

    void errorSetTooLarge(int lineno, const std::string& start, const std::string& end);
}

#endif //_236360_3_
