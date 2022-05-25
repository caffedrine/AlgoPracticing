#include <iostream>

using namespace std;

void ReverseCharsOrder(char *input, int len)
{
    if( len <= 1 )
        return;

    int start = 0;
    int end = len-1;

    while( start < end )
    {
        char tmp = input[start];
        input[start] = input[end];
        input[end] = tmp;

        start++;
        end--;
    }
}

void ReverseWordsOrder(char *input, int len)
{
    int last_space = -1;

    ReverseCharsOrder(input, len-1);

    for( int i = 0; i < len; i++ )
    {
        if( input[i] == ' ' || input[i] == '\0')
        {
            ReverseCharsOrder(&input[last_space + 1], i - (last_space + 1));
            last_space = i;
        }
    }
}

bool IsPalindrome(char *str, int len)
{
    int start = 0;
    int end = len - 1;

    while( start < end )
    {
        if( str[start] != str[end] )
            return false;
        start++;
        end--;
    }
    return true;
}

int FindAllPalindromes(char *input, int len)
{
    int palindromesFound = 0;
    for( int subLen = 2; subLen < len; subLen++ )
    {
        for( int pos = 0; pos < len - subLen; pos++)
        {
            if(IsPalindrome(&input[pos], subLen))
            {
                cout << string(&input[pos],subLen) << " ";
                palindromesFound++;
            }
        }
    }
    return palindromesFound;
}

int main()
{
    char input[] = "The quick brown fox jumps over the lazy dog";

    cout << "Reversing '" << input << "'";
    ReverseWordsOrder(input, sizeof(input));
    cout << " ==> '" << input << "'\n";

    char palindromes[] = "aabbbaa";
    cout << "Palindromes found in string '" << palindromes << "' => ";
    FindAllPalindromes(palindromes, sizeof(palindromes));
    cout << endl;

    return 0;
}
