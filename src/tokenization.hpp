#include <iostream>
#include <optional>
#include <vector>
using namespace std;

#pragma once

enum class TokenType {
    exit,
    int_lit,
    semi,
};
struct Token {
    TokenType type;
    optional<string> value {};
};

class Tokenizer {
    
    public:
        inline Tokenizer (const string src)
            : m_src(move(src))
        {

        }

        inline vector<Token> tokenize() {
            vector<Token> tokens;
            string buf;

            while(peek().has_value()){

                // alphanumeric
                if(isalpha(peek().value())){
                    buf.push_back(consume());

                    while(peek().has_value() && isalnum(peek().value())){
                        buf.push_back(consume());
                    }

                    if(buf == "exit"){
                        tokens.push_back({.type = TokenType::exit});
                        buf.clear();
                        continue;
                    } else {
                        cerr << "You messed up!" << endl;
                        exit(EXIT_FAILURE);
                    }
                }

                // number
                else if(isdigit(peek().value())) {
                    buf.push_back(consume());

                    while(peek().has_value() && isdigit(peek().value())){
                        buf.push_back(consume());
                    }

                    tokens.push_back({.type = TokenType::int_lit, .value = buf});
                    buf.clear();
                    continue;
                }

                // semicolon
                else if(peek().value() == ';') {
                    consume();
                    tokens.push_back({.type = TokenType::semi});
                    continue;
                }

                // whitespace
                else if(iswspace(peek().value())){
                    consume();
                    continue;
                }

                // else error exception
                else {
                    cerr << "You messed upd!" << endl;
                    exit(EXIT_FAILURE);
                }

            }

            m_index = 0; // incase tokenization reuse
            return tokens;
        }

    private:
        [[nodiscard]] inline optional<char> peek(int ahead = 1) const {
            if(m_index + ahead > m_src.length()){
                return {};
            } else {
                return m_src.at(m_index);
            }
        }

        inline char consume() {
            return m_src.at(m_index++);
        }

        const string m_src;
        size_t m_index = 0;
};