//
//  main.cpp
//  infix_postfix
//
//  Created by ddfamily on 8/16/15.
//  Copyright (c) 2015 dragonslayer. All rights reserved.
//

#include <iostream>

typedef enum{
    ParseError_No = 0,
    ParseError_Syntax = 1,
}ParseError;

static int char_feed();
static ParseError g_err = ParseError_No;
static bool parse_fail() { return ParseError_No != g_err;};

class Parser
{
public:
    Parser()
    {
        lookahead = char_feed();
    }
    void expr()
    {
        term();
        while(true){
            if ( '+' == lookahead)
            {
                match('+');
                term();
                if (parse_fail())
                    break;
                else
                    std::cout<<'+';
            }else if('-' == lookahead){
                match('-');
                term();
                if (parse_fail())
                    break;
                else
                    std::cout<<'-';
            }
            else return;
        }
    }
    void term()
    {
        if (isdigit((char)lookahead)){
            std::cout<<(char)lookahead;
            match(lookahead);
        }else{
            std::cout<<" syntax error";
            g_err = ParseError_Syntax;
        }
    }
    void match(int t)
    {
        if (lookahead == t) lookahead = char_feed();
        else{
            g_err = ParseError_Syntax;
        }
    }
    
private:
    int lookahead;
};

int main(int argc, const char * argv[])
{
    Parser parser;
    parser.expr();
    
    if (parse_fail())
        std::cout<<" Parse Fail"<<std::endl;
    else
        std::cout<<" END"<<std::endl;
    
    return 0;
}

static char* tobe_parsed = "3+5-6E";
static int pos = 0;

int char_feed()
{
    return tobe_parsed[pos++];
};

