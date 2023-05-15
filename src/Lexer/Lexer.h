# pragma once
// #include <istream>
#include <unordered_map>
#include "../Token/TokenType.h"
#include "../Token/Token.h"
#include "../ErrorHandler/InterpreterExceptions.h"
#include "../ErrorHandler/ErrorReporter.h"
#include "../ErrorHandler/Errors.h"

class Lexer
{
private:
    std::istream &charactersStream;
    char currentCharacter;
    Position currentPosition;
    Position previousPosition;
    Token token;
    std::unordered_map <std::string, TokenType> keywordsMap; 
    
    Position previous(Position old) const;
    void initLexer();
    void initPosition();
    void initKeywordsMap();
    TokenType findKeyword(const std::string &identifier);
    
    void moveInStream();
    void getNextCharacter();

    char tryGetEscapeCharacter();

    void skipWhites();    
    bool tryBuildIdentifierOrKeyword();
    bool tryBuildETX();
    bool tryBuildComment();
    bool tryBuildTextConst();
    bool tryBuildNumber();
    bool tryBuildMultiCharacterOperator();
    bool tryBuildSingleCharacterOperator();
    bool tryBuildOperator();
    bool tryBuildOperator(TokenType single, const std::string& singleText, TokenType multi, const std::string& multiText);
    bool tryBuildOperator(TokenType single, const std::string& singleText);
public:
    explicit Lexer(std::istream &stream);
    ~Lexer() = default;
    Token getNextToken();
    std::istream & getCharacterStream();

};