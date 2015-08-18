//
//  main.cpp
//  lexer
//
//  Created by ddfamily on 8/18/15.
//  Copyright (c) 2015 dragonslayer. All rights reserved.
//

#include <iostream>
#include "lexer.h"

int main(int argc, const char * argv[]) {
    
    lexer::Lexer l;
    while(1)
    {
        lexer::Token* t = l.scan();
        if (!t) break;
        
        //print t here
        std::cout<<" met token, type:"<<t->GetType();
        if (lexer::TagType_Num == t->GetType())
            std::cout<<" Num:"<<((lexer::Num*)t)->GetValue();
        else if(lexer::TagType_ID == t->GetType())
            std::cout<<" ID:"<<((lexer::Word*)t)->GetLexeme();
        std::cout<<std::endl;
    }
    
    return 0;
}
