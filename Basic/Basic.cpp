/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */
#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;
/* Function prototypes */
void processLine(string line, Program & program, EvalState & state);
/* Main program */


int main() {
   EvalState state;
   state.quit=false;
   Program program;
   //cout << "Stub implementation of BASIC" << endl;
   while (!state.quit) {
      try {
         processLine(getLine(), program, state);
        // cout<<"success"<<endl;
      }
      catch(Divide_Byzero &ex){
          cout<<ex.what()<<endl;
      }
      catch(Invalid_Number &ex){
          cout<<ex.what()<<endl;
      }
      catch (Syntax_Error &ex){
          cout<<ex.what()<<endl;
      }
       catch (Var_Ndefined &ex){
           cout<<ex.what()<<endl;
       }
       catch (Linenumber_Error &ex){
           cout<<ex.what()<<endl;
       }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
    //std::cout<<"PRO "<<line<<std::endl;
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.setInput(line);
   scanner.scanNumbers();
   int linenum=line_num(scanner);
   if(linenum>0){
       if(program.Line_inserted(linenum))
           program.removeSourceLine(linenum);
       if(!scanner.hasMoreTokens())
       {
           return;
       }
       program.addSourceLine(linenum,line);
       program.setParsedStatement(linenum,parseStm(scanner,state));
       return;
   }
   Statement *ptr=parseStm(scanner,state);
   //std::cout<<"successfully"<<std::endl;
    switch (ptr->getType()) {
        case RUN:
            //state.clear();
            run_Program(program,state);
            break;
        case LIST:
            list_Program(program);
            break;
        case CLEAR:
            program.clear();
            state.clear();
            break;
        case QUIT:
            state.quit=true;
            break;
        case HELP:
            //std::cout<<"Hello Idiot!"<<std::endl;
            break;
        default:
            ptr->execute(state);
    }
    //std::cout<<"ptr"<<std::endl;
   delete ptr;

}


