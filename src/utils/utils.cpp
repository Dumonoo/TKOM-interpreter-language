#include <string>
#include <algorithm>

using namespace std;

string toLowerCase(string input)
{
    string output = "";
    for (auto i = 0; i < input.length(); i++)
    {
        output += (char)tolower(input[i]);
    }
    return output;
}

bool isNewLineCharacter(char character)
{
    return (
        (int)character == 10 ||
        (int)character == 13 ||
        (int)character == 21 ||
        (int)character == 30 ||
        (int)character == 155
    );
}

bool isEtxCharacter(char character){
    return (
        character == std::char_traits<char>::eof()
    );
}