/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
/* Implementation of the Statement class */


Statement::Statement() { 
   exp=NULL;
}

Statement::~Statement() {
   delete exp;
    //std::cout<<"father die"<<std::endl;
}

void Statement::execute(EvalState  &state){
}

Comment::Comment(){}

StatementType Comment::getType(){
    return COMMENT;
}

Assignment::Assignment(Expression *expr){exp=expr;}

StatementType Assignment::getType(){
    return ASSIGNMENT;
}

void Assignment::execute(EvalState  &state){
    exp->eval(state);
}

Print::Print(Expression *expr){exp=expr;}


StatementType Print::getType(){
    return PRINT;
}

void Print::execute(EvalState  &state){
    std::cout<<exp->eval(state)<<std::endl;
}


Input::Input(string var):var(var){}//std::cout<<"New  "<<var<<std::endl;


StatementType Input::getType(){
    return INPUT;
}

void Input::execute(EvalState  &state){
    int value;
    TokenScanner scanner;
    string token;
    TokenType type;
    while(true) {
       try {
           std::cout << " ? ";
           scanner.ignoreWhitespace();
           scanner.setInput(getLine());
           scanner.scanNumbers();
           token = scanner.nextToken();
           type = scanner.getTokenType(token);
           //std::cout<<"type"<<type<<NUMBER<<token<<std::endl;
           if (type != NUMBER || scanner.hasMoreTokens()) {
               if (token == "-") {
                   value = -1 * stringToInteger(scanner.nextToken());
                   state.setValue(var, value);
                   return;
               } else
                   throw Invalid_Number();
           }
           if(type==NUMBER&&token.find(".")<token.length()){
               throw Invalid_Number();
           }
       }
       catch(Invalid_Number &ex){
                std::cout<<ex.what()<<std::endl;
                continue;
       }
       break;
    }
    value=stringToInteger(token);
    //std::cout<<value<<std::endl;
    state.setValue(var, value);
}



Input::~Input(){
    //std::cout<<"Input die"<<std::endl;
};


StatementType End::getType(){
    return END;
}


End::End(){}

void End::execute(EvalState  &state){
    state.quit=true;
}

Goto::Goto(const int& linenum){linenumber=linenum;}

StatementType Goto::getType(){
    return GOTO;
}

If::If(const int& linenumbe,Expression *expr){linenumber=linenumbe;exp=expr;}


StatementType If::getType(){
    return IF;
}

Run::Run(){}

StatementType Run::getType(){
    return RUN;
}

List::List(){}

StatementType List::getType(){
    return LIST;
}

Clear::Clear(){}

StatementType Clear::getType(){
    return CLEAR;
}

Quit::Quit(){}

StatementType Quit::getType(){
    return QUIT;
}

Help::Help(){}

StatementType Help::getType(){
    return HELP;
}

Divide_Byzero::Divide_Byzero():message("DIVIDE BY ZERO"){
}


Invalid_Number::Invalid_Number():message("INVALID NUMBER"){

}



Syntax_Error::Syntax_Error():message("SYNTAX ERROR"){

}


Var_Ndefined::Var_Ndefined():message("VARIABLE NOT DEFINED"){

}


Linenumber_Error::Linenumber_Error():message("LINE NUMBER ERROR"){

}