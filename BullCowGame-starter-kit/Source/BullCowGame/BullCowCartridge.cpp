// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <map>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
    
    //PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord)); // Debug Line  
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // PrintLine(TEXT("You have %i lives left"), Lives);//  Debug line

    if (bGameOver) 
    {
        ClearScreen();
        SetupGame();
    
    }
    else 
    {
        ProcessGuess(Input);
    }

}

void UBullCowCartridge::SetupGame() 
{
    HiddenWord = TEXT("pugs");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess. \nPress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress Enter to play again"));

}

void UBullCowCartridge::ProcessGuess(FString Guess) 
{
    if (HiddenWord == Guess) 
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }
    else 
    {
        PrintLine(TEXT("You lost of a life!"));
        --Lives;

        if (HiddenWord.Len() != Guess.Len()) 
        {
            PrintLine(TEXT("Remember it is a %i letter word"), HiddenWord.Len());
        }

        // Check if guess was not an isogram
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("No repeating letters, guess again"));
        }

        
        if (Lives <= 0) 
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives left!"));
            PrintLine(TEXT("The hidden word was %s: "), *HiddenWord);
            EndGame();
            return;
        }

        // Show the palyer the bulls and cows
    }
}

bool UBullCowCartridge::IsIsogram(FString word) const
{
    int hash[123] = {};
    for(int i = 0; i < word.Len(); i++) 
    {
        hash[word[i]] += 1;
        if(hash[word[i]] == 2) 
        {
            return false;
        }
    }
    return true;
}