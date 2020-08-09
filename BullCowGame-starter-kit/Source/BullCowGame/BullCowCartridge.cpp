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
    Isograms = GetValidWords(Words);
    SetupGame();
    
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    // PrintLine(TEXT("You have %i lives left"), Lives);//  Debug line

    if (bGameOver) 
    {
        ClearScreen();
        SetupGame();
    
    }
    else 
    {
        ProcessGuess(PlayerInput);
    }

}

void UBullCowCartridge::SetupGame() 
{

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    PrintLine(TEXT("The hidden word was %s: "), *HiddenWord); // Debug Line
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
        FBullCowCount Score = GetBullCows(Guess);
        PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
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

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++) 
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        } 
    }
    return Count;
}