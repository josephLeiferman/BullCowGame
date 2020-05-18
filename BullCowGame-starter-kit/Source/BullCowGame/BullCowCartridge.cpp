// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 3 letter word!")); // Magic Number please remove
    PrintLine(TEXT("Press enter to continue..."));

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("pug"); // Make this an instance variable instead
    if (HiddenWord == Input) 
    {
        PrintLine(TEXT("You have won!"));
    } 
    else 
    {
        PrintLine(TEXT("You have lost!"));
    }
}