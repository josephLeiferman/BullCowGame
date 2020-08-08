// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include <map>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Load word lists from file 
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    SetupGame(GetValidWords(Words));
    
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    // PrintLine(TEXT("You have %i lives left"), Lives);//  Debug line

    if (bGameOver) 
    {
        ClearScreen();
        SetupGame(GetValidWords(Words));
    
    }
    else 
    {
        ProcessGuess(PlayerInput);
    }

}

void UBullCowCartridge::SetupGame(const TArray<FString>& ValidWordList) 
{

    HiddenWord = ValidWordList[FMath::RandRange(0, ValidWordList.Num())];
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

void UBullCowCartridge::ProcessGuess(const FString& Guess) 
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

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    int hash[123] = {};
    for(int32 i = 0; i < Word.Len(); i++) 
    {
        hash[Word[i]] += 1;
        if(hash[Word[i]] == 2) 
        {
            return false;
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
     TArray<FString> ValidWords;


    for(FString Word : WordList) 
    {
        if(Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
           ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}