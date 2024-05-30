
#include <iostream>
#include<cstdlib>
#include<string>
//#include "stdafx.h"
using namespace std;

enum enGameChoice {Stone=1,Paper=2,Scissors=3};
enum enWinner{Player1=1,Computer=2,Draw=3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResult
{
	short GameRounds = 0;
	short PlayerWinTimes = 0;
	short ComputWinTime = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = " ";
};


int ReadNumberI(int From, int To)
{
	int ReadNumber = rand() % (To - From + 1) + From;
	return ReadNumber;
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 0;
	do
	{
		cout << "\nYour Choice : [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;

	} while (Choice<1||Choice>3);

	return (enGameChoice)Choice;
}



short ReadHowManyRounds()
{
	short GameRounds = 1;
	do
	{
		cout << "How Many Rounds 1 to 10 ? \n ";
		cin >> GameRounds;
	} while (GameRounds<1||GameRounds>10);
	return GameRounds;
}


enGameChoice GetComputerChoice()
{
	return (enGameChoice)ReadNumberI(1, 3);
}


enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice==RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.Player1Choice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player1;
}


string WinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = { "Player1","Computer","No Winner" };
	return ArrWinnerName[Winner - 1];
}


string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { "stone","Paper","Scissors" };
	return arrGameChoices[Choice - 1];
}


void SetWinnerScreenColor(enWinner Winner)
{

	switch (Winner)
	{
	case Player1:
		system("color 2f");
		break;
	case Computer:
		system("color 4f");
		cout<<"\a";
		break;
	case Draw:
		system("color 6f");
		break;
	default:
		break;
	}
}


void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n______________________Round[" << RoundInfo.RoundNumber << "]____________________\n\n";
	cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Choice   : [ " << RoundInfo.WinnerName << "]\n";
	cout << "____________________________________\n" << endl;

}


enWinner WhoWonTheGame(short Player1WinTime, short ComputerWinTimes)

{
	if (Player1WinTime > ComputerWinTimes)
		return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTime)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}


stGameResult FillGameResult(short GameRound, short ComputerWinTimes, short Player1WinTime, short DrawTime)
{
	stGameResult GameResults;
	GameResults.GameRounds = GameRound;
	GameResults.ComputWinTime = ComputerWinTimes;
	GameResults.PlayerWinTimes = Player1WinTime;
	GameResults.DrawTimes = DrawTime;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTime, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);
	return GameResults;

}
stGameResult PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTime = 0, ComputerWinTimes = 0, DrawTime = 0;
	for (short GameRound= 1; GameRound <=HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins : \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTime++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTime++;

		PrintRoundResult(RoundInfo);
	}
	return FillGameResult(HowManyRounds, Player1WinTime, ComputerWinTimes, DrawTime);
}


string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}


void ShowGameOverScreen()
{


	cout <<Tabs(2)<<"_____________________________________________________\n\n";
	cout <<Tabs(2)<< "+++ G a m e   O v e r +++\n\n";
	cout <<Tabs(2)<< "_______________________________________________________________\n\n";
	}

void ShowFinalGameResults(stGameResult GameResults)
{
	    cout << Tabs(2) << "_____________________[Game Results]_______________\n\n";
		cout << Tabs(2) << "Game Ruounds       : " << GameResults.GameRounds << endl;
		cout << Tabs(2) << "Player1 won times  : " << GameResults.PlayerWinTimes << endl;
		cout << Tabs(2) << "Computer won times : " << GameResults.ComputWinTime << endl;
		cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
		cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
		cout << Tabs(2) << "__________________________________________________________\n";
		ShowGameOverScreen();



}

void ResetScreen() 
{
	system("cls");
	system("color 0f");
}


void StartGame()
{
    char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResult GamResult = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GamResult);
		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain=='y'||PlayAgain=='Y');
}


int main()
{
	srand((unsigned)time(NULL));
	StartGame();

}
