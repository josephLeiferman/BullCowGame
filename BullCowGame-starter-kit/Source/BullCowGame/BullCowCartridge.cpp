// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

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
    PrintLine(TEXT("Press Enter to play again"));

}

void UBullCowCartridge::ProcessGuess(FString Guess) 
{
    if (HiddenWord == Guess) 
        {
            PrintLine(TEXT("You have won!"));
            EndGame();
        } 
        else 
        {
            PrintLine(TEXT("Lost a life!"));
            PrintLine(TEXT("Lives remaining: %i"), --Lives);
            if (Lives > 0) 
            {
                if (HiddenWord.Len() != Guess.Len()) 
                {
                    PrintLine(TEXT("Remember it is a %i letter word"), HiddenWord.Len());
                }
            }
            else {
                PrintLine(TEXT("You have no lives left!"));
                EndGame();
            }

        }
}