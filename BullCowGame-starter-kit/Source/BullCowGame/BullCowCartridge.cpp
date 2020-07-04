// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Setting up game
    SetupGame();
    
    //PrintLine(TEXT("The HiddenWord is %s."), *HiddenWord)); // Debug Line

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len()); // Magic Number please remove
    PrintLine(TEXT("Press enter to continue..."));

    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    PrintLine(TEXT("You have %i lives left"), Lives);
    
    if (HiddenWord == Input) 
    {
        PrintLine(TEXT("You have won!"));
    } 
    else 
    {
        if (HiddenWord.Len() != Input.Len()) 
        {
            PrintLine(TEXT("The Hidden word is %i characters long, try again"), HiddenWord.Len());
        }
        PrintLine(TEXT("You have lost!"));
        Lives--;
    }
}

void UBullCowCartridge::SetupGame() 
{
    HiddenWord = TEXT("pugs");
    Lives = HiddenWord.Len();
}