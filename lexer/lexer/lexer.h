//
//  lexer.h
//  lexer
//
//  Created by ddfamily on 8/18/15.
//  Copyright (c) 2015 dragonslayer. All rights reserved.
//

#ifndef lexer_lexer_h
#define lexer_lexer_h

#include <string>
#include <map>

namespace lexer
{

    typedef enum{
        TagType_Num = 256,
        TagType_ID = 257,
        TagType_True = 258,
        TagType_False = 259,
    }TagType;
    
    class Token{
    public:
        Token(int t):_tag(t){}
        int GetType() { return _tag;}
        virtual ~Token(){}
    private:
        int _tag;
    };
    
    class Num: public Token{
    public:
        Num(int v):Token(TagType_Num),_value(v){}
        int GetValue() { return _value; }
    private:
        int _value;
    };
    
    class Word: public Token{
    public:
        Word(int t, const std::string& s):Token(t),_lexeme(s){}
        const std::string& GetLexeme()const { return _lexeme;}
    private:
        std::string _lexeme;
    };
    
    typedef std::map<std::string, Word> wordMap;
    typedef wordMap::iterator itWord;
    
    static char* tobe_parsed = "hello world +9877 dam q&a\this is the second screen.";
    static int pos = 0;
    
    int char_feed()
    {
        return tobe_parsed[pos++];
    };
    
    bool is_letter(char ch)
    {
        if (ch >= 'a' && ch <= 'z') return  true;
        if (ch >= 'A' && ch <= 'ch') return  true;
        return false;
    }
    
    class Lexer{
    public:
        Lexer():_line(1),_peek(' ')
        {
            reserve(Word(TagType_True, std::string("true")));
            reserve(Word(TagType_False, std::string("false")));
        }
        
        void reserve(const Word& w){
            _words.insert(std::make_pair(w.GetLexeme(), w));
        }
        
        Token* scan()
        {
            for(; _peek; _peek = char_feed())
            {
                if (_peek == ' ' || _peek == '\t') continue;
                else if(_peek == '\n') _line++;
                else break;
            }
            
            if (0 == _peek) return NULL;
            
            if (isdigit(_peek))
            {
                int v = 0;
                do {
                    v = 10*v + _peek - (int)'0';
                    _peek = char_feed();
                }while(isdigit(_peek));
                return new Num(v);
            }
            
            if (is_letter(_peek))
            {
                std::string b;
                do{
                    b += _peek;
                    _peek = char_feed();
                }while(is_letter(_peek) || isdigit(_peek));
                
                itWord it = _words.find(b);
                if (_words.end() == it)
                {
                    _words.insert(std::make_pair(b, Word(TagType_ID, b)));
                }else{
                    return  new Word(TagType_ID, b);
                }
                
                return  new Word(TagType_ID, b);
            }
            
            if (_peek == 0) return NULL;
            
            Token* t = new Token(_peek);
            _peek = ' ';
            return t;
        }
        
    private:
        int _line;
        char _peek;
        wordMap _words;
    };
    
}


#endif
