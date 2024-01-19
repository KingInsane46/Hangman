#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

const std::string g0 = "\n\n\n";
const std::string g1 = "  O\n     \n   \n     ";
const std::string g2 = "  O\n  |  \n  |\n     ";
const std::string g3 = "  O\n--|  \n  |\n     ";
const std::string g4 = "  O\n--|--\n  |\n     ";
const std::string g5 = "  O\n--|--\n  |\n /   ";
const std::string g6 = "  O\n--|--\n  |\n / \\";

const int possibleWordsCount = 10;
const std::string possibleWords[] {"electricity","donkey","hardware","transistor","engineering","hangman","picture","teacher","alarm","puzzle"   };

std::string word;

bool discoveredLetters[255];
bool gameDone;
int incorrectLetterGusses;
int correctLetterGusses;

void PrintWord()
{
    for(int i = 0; i < word.size(); i++)
    {
        char letter = word[i];
        if(letter == ' ')
        {
            std::cout << ' ';
        }
        else if(discoveredLetters[letter])
        {
            std::cout << letter;
        }
        else
        {
            std::cout << '?';
        }
    }
    std::cout << std::endl;
}

void PrintMan()
{
    switch(incorrectLetterGusses)
    {
        case 0: std::cout << g0 << std::endl; break;
        case 1: std::cout << g1 << std::endl; break;
        case 2: std::cout << g2 << std::endl; break;
        case 3: std::cout << g3 << std::endl; break;
        case 4: std::cout << g4 << std::endl; break;
        case 5: std::cout << g5 << std::endl; break;
        case 6: std::cout << g6 << std::endl; break;
    };
}

void PlayerChooseLetter()
{
    std::cout << "Chose a Letter" << std::endl;
    char letter;
    std::cin >> letter;
    letter = tolower(letter);
    while(discoveredLetters[letter])
    {
        std::cout << letter << "<-already chosen" << std::endl;
        std::cin >> letter;
    }
    discoveredLetters[letter] = true;

    int spaceCount = 0;
    bool wordContainsLetter = false;
    for(int i = 0; i < word.size(); i++)
    {
        if(word[i] == ' ')
        {
            spaceCount++;
            continue;
        }
        else if(word[i] == letter)
        {
            correctLetterGusses++;
            wordContainsLetter = true;
        }
    }
    if(!wordContainsLetter)
    {
        incorrectLetterGusses++;
        if(incorrectLetterGusses > 6)
        {
            std::cout << "Out of chances, You Lose. The word was: " << word << std::endl;
            gameDone = true;
        }
    }
    if(word.size() - spaceCount == correctLetterGusses)
    {
        std::cout << "All Letters Found, You Win." << std::endl;
        gameDone = true;
    }
}

void GameLoop()
{
    word = possibleWords[rand() % possibleWordsCount];
    incorrectLetterGusses = 0;
    correctLetterGusses = 0;
    for(int i = 0; i < 255; i++)
    {
        discoveredLetters[i] = false;
    }
    gameDone = false;

    while(!gameDone)
    {
        std::system("CLS");
        PrintWord();
        PrintMan();
        PlayerChooseLetter();
    }
}

bool PlayAgain()
{
    char val;
    std::cout << "Play Again? Y/N" << std::endl;
    std::cin >> val;
    return val == 'y' || val == 'Y';
}

int main()
{
    srand(time(NULL));
    do
    {
        GameLoop();
    } while(PlayAgain());
    return 0;
}
