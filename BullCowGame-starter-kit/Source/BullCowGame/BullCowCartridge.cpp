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
        if (HiddenWord == Input) 
        {
            PrintLine(TEXT("You have won!"));
            EndGame();
        } 
        else 
        {
            --Lives;
            PrintLine(TEXT("Lost a life!"));
            PrintLine(TEXT("Lives remaing: %i", Lives));
            if (Lives > 0) 
            {
                if (HiddenWord.Len() != Input.Len()) 
                {
                    PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
                }
            }
            else {
                PrintLine(TEXT("You have no lives left!"));
                EndGame();
            }

        }

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