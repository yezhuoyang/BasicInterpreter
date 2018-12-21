/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */
#include <string>
#include "program.h"
#include "statement.h"
using namespace std;
Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
    for(map<int,Statement*>::iterator iter=Statement_map.begin();iter!=Statement_map.end();++iter)
    {
        delete (iter->second);
    }
}

void Program::clear() {
    for(map<int,Statement*>::iterator iter=Statement_map.begin();iter!=Statement_map.end();++iter)
    {
        delete (iter->second);
    }
    Statement_map.clear();
    Source_map.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
    Source_map.insert(pair<int,string>(lineNumber,line));
   // Replace this stub with your own code
}

void Program::removeSourceLine(int lineNumber) {
    map<int,string>::iterator iter;
    iter=Source_map.find(lineNumber);
    Source_map.erase(iter);
    map<int,Statement*>::iterator iter1;
    iter1=Statement_map.find(lineNumber);
    delete  iter1->second;
    Statement_map.erase(iter1);
}

string Program::getSourceLine(int lineNumber) {
    map<int,string>::iterator iter;
    iter=Source_map.find(lineNumber);
    return (iter->second);
}


bool Program::Line_inserted(int lineNumber){
    map<int,string>::iterator iter;
    iter=Source_map.find(lineNumber);
    if(iter!=Source_map.end())
         return true;
    else
        return false;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    Statement_map.insert(pair<int,Statement*>(lineNumber,stmt));
}


Statement *Program::getParsedStatement(int lineNumber) {
    map<int,Statement*>::iterator iter;
    iter=Statement_map.find(lineNumber);
    return iter->second;
}

int Program::getFirstLineNumber() {
   return (Source_map.begin())->first;     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
    map<int,string>::iterator iter;
    iter=Source_map.find(lineNumber);
    iter++;
    return iter->first;     // Replace this stub with your own code
}



void run_Program(Program& P, EvalState & state){
    map<int,Statement*>::iterator iter=P.Statement_map.begin();
    while(iter!=P.Statement_map.end()){

        //cout<<"L  "<<iter->first<<endl;

        switch (iter->second->getType()) {
            case IF:
                state.compare=true;
                if(iter->second->exp->eval(state)) {
                    state.compare=false;
                    iter = P.Statement_map.find(iter->second->linenumber);
                    if(iter==P.Statement_map.end())
                        error("LINE NUMBER ERROR");
                }
                else{
                    ++iter;
                    state.compare=false;
                }
                break;
            case GOTO:
                   iter=P.Statement_map.find(iter->second->linenumber);
                   if(iter==P.Statement_map.end()){
                       error("LINE NUMBER ERROR");
                   }
                break;
            case END:
                iter=P.Statement_map.end();
                break;
            default:
                iter->second->execute(state);
                ++iter;
        }
    }
}


void list_Program(Program& P){
    for(map<int,string>::iterator iter=P.Source_map.begin();iter!=P.Source_map.end();++iter)
    {
        std::cout<<iter->second<<std::endl;
    }
}
