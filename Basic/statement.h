/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */
#ifndef _statement_h
#define _statement_h
#include "evalstate.h"
#include "exp.h"
/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */
enum StatementType {COMMENT,ASSIGNMENT,PRINT,INPUT,END,GOTO,IF,RUN,LIST,CLEAR,QUIT,HELP};
class Statement {
public:
    int value;
/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */
   Statement();
/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */
   virtual ~Statement();
   virtual StatementType getType()=0;
/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */
   virtual void execute(EvalState & state);

    Expression *exp;
    int linenumber;
};
/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */
class Comment:public Statement{
    public:
        Comment();
        virtual StatementType getType();
};

class Assignment:public Statement{
    public:
       explicit Assignment(Expression *exp);
        virtual void execute(EvalState & state);
        virtual StatementType getType();
    //private:
        //Expression* exp;
};

class Print:public Statement{
    public:
        explicit Print(Expression *exp);
        virtual void execute(EvalState & state);
        virtual StatementType getType();
    //private:
        //Expression* exp;
};

class Input:public Statement{
    public:
        explicit Input(string var);
        virtual void execute(EvalState & state);
        virtual StatementType getType();
    private:
        string var;
};

class End:public Statement{
    public:
        End();
        virtual void execute(EvalState & state);
        virtual StatementType getType();
};

class Goto:public Statement{
    public:
        explicit Goto(const int& linenum);
        virtual StatementType getType();
};

class If:public Statement{
    public:
        explicit If(const int& linenumber,Expression *exp);
        virtual StatementType getType();
};

class Run:public Statement{
    public:
        Run();
        virtual StatementType getType();
};

class List:public Statement{
    public:
        List();
        virtual StatementType getType();
};

class Clear:public Statement{
    public:
        Clear();
        virtual StatementType getType();
};

class Quit:public Statement{
    public:
        Quit();
        virtual StatementType getType();
};

class Help:public Statement{
    public:
        Help();
        virtual StatementType getType();
};
#endif
