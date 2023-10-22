#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <map>

enum TokenType {
    NUMBER,
    STRING,
    IDENTIFIER,
    KEYWORD,
    OPERATOR,
    PUNCTUATION,
    COMMENT,
    PREPROCESSOR_DIRECTIVE,
    NEW_LINE,
    WHITE_SPACE,
    ERROR
};

struct Token {
    std::string lexeme;
    TokenType type;
};

int main() {
    std::string code = "var x = 42 + '50'; let variable = 'e'; &% -- // This is a comment\nfunction foo(){return 'Hello World';} while (true) {x++};";
    std::string numberPattern = "\\b\\d+(\\.\\d+)?\\b";
    std::string stringPattern = "'[^']*'|\"[^\"]*\"";
    std::string keywordPattern = "\\b(alignas|alignof|and|and_eq|asm|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|consteval|constexpr|const_cast|continue|co_await|co_return|co_yield|decltype|default|delete|do|double|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq|function|let|var)\\b";
    std::string identifierPattern = "\\b[a-zA-Z_]\\w*\\b"; 
    std::string operatorPattern = "\\*\\*|\\+\\+|\\-\\-|[+\\-*/=]|%";
    std::string punctuationPattern = "[,;{}()]";
    std::string commentPattern = "//[^\n]*|/\\*.*?\\*/";
    std::string directivePattern = "#.*";
    std::string newlinePattern = "\n";
    std::string whitespacePattern = "\\s+";

    std::vector<Token> tokens;

    std::map<std::string, TokenType> regexMap = {
        {stringPattern, STRING},
        {numberPattern, NUMBER},
        {keywordPattern, KEYWORD},
        {identifierPattern, IDENTIFIER},
        {operatorPattern, OPERATOR},
        {punctuationPattern, PUNCTUATION},
        {commentPattern, COMMENT},
        {directivePattern, PREPROCESSOR_DIRECTIVE},
        {newlinePattern, NEW_LINE},
        {whitespacePattern, WHITE_SPACE}
    };

    std::smatch match;
    size_t currentPosition = 0;

    while (currentPosition < code.length()) {
        bool found = false;
        for (const auto& pair : regexMap) {
            if (std::regex_search(code.cbegin() + currentPosition, code.cend(), match, std::regex(pair.first))) {
                if (match.position() == 0) {
                    tokens.push_back({match[0], pair.second});
                    currentPosition += match.length();
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            tokens.push_back({code.substr(currentPosition, 1), ERROR});
            currentPosition++;
        }
    }
    for (const Token& token : tokens) {
        std::string tokenType;
        switch (token.type) {
            case NUMBER: tokenType = "NUMBER"; break;
            case STRING: tokenType = "STRING"; break;
            case IDENTIFIER: tokenType = "IDENTIFIER"; break;
            case KEYWORD: tokenType = "KEYWORD"; break;
            case OPERATOR: tokenType = "OPERATOR"; break;
            case PUNCTUATION: tokenType = "PUNCTUATION"; break;
            case COMMENT: tokenType = "COMMENT"; break;
            case PREPROCESSOR_DIRECTIVE: tokenType = "PREPROCESSOR_DIRECTIVE"; break;
            case WHITE_SPACE: tokenType = "WHITE_SPACE"; break;
            case NEW_LINE: tokenType = "NEW_LINE"; break;
            case ERROR: tokenType = "ERROR"; break;
        }
        std::cout << "<" << token.lexeme << ", " << tokenType << ">" << std::endl;
    }

    return 0;
}
