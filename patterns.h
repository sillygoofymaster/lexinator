#include <string>
#include <vector>
#include <regex>

using std::string, std::vector, std::pair, std::regex; 

/* 
Реалізувати лексичний аналізатор мови програмування. 
Розрізняти принаймні такі класи лексем:
–        числа (десяткові, з плаваючою крапкою, шістнадцяткові),
–        рядкові та символьні константи,
–        директиви препроцесора,
–        коментарі,
–        зарезервовані слова,
–        оператори,
–        розділові знаки,
–        ідентифікатори,
–        інші, характерні для відповідної мови програмування.
Позначати ситуації з помилками (наприклад, нерозпізнавані символи).

Мова: C++.
*/

vector<pair<string, regex>> compiledRegexes() {
    return {
        // числа
        {"DOUBLE",   regex(R"([0-9]+\.[0-9]+([eE][+-]?[0-9]+)?)", regex::ECMAScript)},
        {"INT",      regex(R"([0-9]+)", regex::ECMAScript)},
        {"HEX",      regex(R"(0x[0-9A-Fa-f]*)", regex::ECMAScript)},

        // директиви препроцесора
        {"PREPROCESSOR", std::regex(R"(^\s*#\s*(define|include|ifdef|ifndef|undef|pragma|if|elif|else|endif|error|line)\b.*)")},

        // коментарі
        {"COMMENT_SMALL", regex(R"(//.*)", regex::ECMAScript)},
        {"COMMENT_BIG",  regex(R"(/\*(?:[\s\S]*?)\*/)", regex::ECMAScript)},


        // оператори
        {"OPERATOR", regex(R"(>>|<<|<=|>=|==|!=|\+=|-=|\*=|/=|%=|\+\+|--|\*\*|\|\||&&|!|=|<|>|\^|&|\||~|[+\-*/%])", regex::ECMAScript)},

        // розділові знаки
        {"PUNCTUATION",    regex(R"([\(\)\[\]\{\}]|:|,|;|\.)", regex::ECMAScript)},

        {"SPACE",       regex(R"([ \t]+)", regex::ECMAScript)},
        {"NEWLINE",       regex(R"(\r?\n)", regex::ECMAScript)},

        // зарезервовані слова
        {"KEYWORD", regex(R"(\b(?:alignas|alignof|auto|bool|break|case|char|const|constexpr|continue|default|do|double|else|enum|extern|false|float|for|goto|if|inline|int|long|nullptr|register|restrict|return|short|signed|sizeof|static|static_assert|struct|switch|thread_local|true|typedef|typeof|typeof_unqual|union|unsigned|void|volatile|while)\b)", std::regex::ECMAScript)},

        // ідентифікатори
        {"IDENTIFIER", regex(R"([a-zA-Z][a-zA-Z0-9_]*)", regex::ECMAScript)},

        // інші
        {"STRING", regex(R"("([^"\\]|\\.)*")", regex::ECMAScript)},
        {"CHAR", regex(R"'('([^'\\]|\\.)')'", regex::ECMAScript)}
    };
}