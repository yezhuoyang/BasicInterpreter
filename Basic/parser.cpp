/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.
 */
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;
/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */
Expression *parseExp(TokenScanner & scanner) {
   Expression *exp = readE(scanner);
   //if (scanner.hasMoreTokens()) {
   //   error("parseExp: Found extra token: " + scanner.nextToken());
   //}
   return exp;
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner & scanner, int prec) {
   Expression *exp = readT(scanner);
   string token;
   while (true) {
      token = scanner.nextToken();
      int newPrec = precedence(token);
      if (newPrec <= prec) break;
      Expression *rhs = readE(scanner, newPrec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner.saveToken(token);
   return exp;
}
/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */
Expression *readT(TokenScanner & scanner) {
   string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type == WORD)
   {
       if(token=="LET")
           throw Syntax_Error();
       return new IdentifierExp(token);
   }
   if (type == NUMBER) return new ConstantExp(stringToInteger(token));
   if (token != "(") throw Syntax_Error();
   Expression *exp = readE(scanner);
   if (scanner.nextToken() != ")") {
       throw Syntax_Error();
   }
   return exp;
}


/*
 * Implementation notes: precedence
 * --------------------------------
 * This function cheAZaszzcks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */
int precedence(string token) {
   if (token == "="||token=="<"||token==">") return 1;
   if (token == "+" || token == "-") return 2;
   if (token == "*" || token == "/") return 3;
   return 0;
}

int line_num(TokenScanner & scanner){
    string token=scanner.nextToken();
    TokenType type=scanner.getTokenType(token);
    if(type==NUMBER)
        return stringToInteger(token);
    else{
        scanner.saveToken(token);
        return -1;
    }
}

Statement *parseStm(TokenScanner & scanner,EvalState & state){
    string id=scanner.nextToken();
    Statement* ptr=NULL;
    if(id=="REM")
    {
        ptr=new Comment();
    }
    if(id=="LET")
    {
        ptr=new Assignment(parseExp(scanner));
    }
    if(id=="PRINT") {
        ptr = new Print(parseExp(scanner));
    }
    if(id=="IF")
    {
        Expression* ptr2=parseExp(scanner);
        scanner.nextToken();
        int linenumber=stringToInteger(scanner.nextToken());
        ptr=new If(linenumber,ptr2);
    }
    if(id=="GOTO")
    {
        int linenumber=stringToInteger(scanner.nextToken());
        ptr=new Goto(linenumber);
    }
    if(id=="END")
    {
        ptr=new End();
    }
    if(id=="INPUT"){
        ptr=new Input(scanner.nextToken());
    }
    if(id=="LIST")
    {
        ptr=new List();
    }
    if(id=="RUN"){
        ptr=new Run();
    }
    if(id=="CLEAR"){
        ptr=new Clear();
    }
    if(id=="QUIT"){
        ptr=new Quit();
    }
    if(id=="HELP"){
        ptr=new Help();
    }
    if(!ptr) throw Syntax_Error();
    return ptr;

}
