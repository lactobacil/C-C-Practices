#include<iostream>
#include<cstdlib>
#include<ctime>
using std::string;
using namespace std;

int win = 0;

int matchword(int*);

void gameDisplay(int Attempts) {

	string wrong[6];

	wrong[0] = "   |   ";
	//Store array for every input;
	switch (Attempts) {
	case 4:
		wrong[1] = "   |  ";
		break;
	case 3:
		wrong[1] = "   |  ";
		wrong[2] = "   O ";
		break;
	case 2:
		wrong[1] = "   |  ";
		wrong[2] = "   O ";
		wrong[3] = "  -|- ";
		break;
	case 1:
		wrong[1] = "   |  ";
		wrong[2] = "   O ";
		wrong[3] = "  -|- ";
		wrong[4] = "  | |  ";
		break;
	case 0:
		wrong[1] = "   |  ";
		wrong[2] = "   O ";
		wrong[3] = "  -|- ";
		wrong[4] = "  | |  ";
		wrong[5] = "  ____ ";
		break;
	}
	

	cout << "__________  " << endl;
	cout << "|  " << wrong[0] << endl;
	cout << "|  " << wrong[1] << endl;
	cout << "|  " << wrong[2] << endl;
	cout << "|  " << wrong[3] << endl;
	cout << "|  " << wrong[4] << endl;
	cout << "|  " << wrong[5] << endl;
	
}

//Get Number from Dictionary here 
string randWord() {
	int randNumber;
	string chooseword[] = { "admin", "letter", "timber", "dubliners", "tableau", };

	srand(time(NULL));
	randNumber = rand() % 5;
	return chooseword[randNumber];
}


//Hard Part of the game for me, Try to sketch it next time on a paper


int matchWord(char guessLetter, char* guessWord, int guessLen, string correctword, int *win) {

	//Matches the string with the word
	//Return mark 0 if the number failed
	int mark = 0;

	for (int i = 0; i < guessLen; i++) {
		if (guessLetter == correctword[i]) {
				if (guessWord[i] == correctword[i]) {
					//Return false because it failed to match the value
					mark = 2;

				}
				else {
					guessWord[i] = guessLetter;
					mark = 1;
					*win = *win + 1;
					if (*win == guessLen) {
						mark = 3; 
					}
			}
		}
	}
	return mark;
}


void filldash(char* arr, int length) {
	for (int i = 0; i < length; i++) {
		arr[i] = '-';
	}
}

void displayWord(char* arr, int length) {
	for (int i = 0; i < length; i++) {
		cout << arr[i];
	}

	cout << endl;
}

void intro() {
	cout << " H A N G M A N " << endl;
	cout << " H A N G M A N " << endl;
	cout << " H A N G M A N " << endl;
	cout << " H A N G M A N " << endl;
	cout << " H A N G M A N " << endl;
	cout << endl;
}

//Main Function To Try
int main() {

	char guessletter;
	string correctWord;
	int correctWordLen;
	int attempts = 5;
	int guessArrlen;
	int win = 0;


	correctWord = randWord();
	correctWordLen = correctWord.length();
	guessArrlen = correctWord.length();

	//Initialise Dynamic Array to store the guessword, needed this for allocating since we cant create the guessword array dynamically
	char *guessWord;
	guessWord = (char*)malloc( guessArrlen * sizeof(char));

	intro();

	filldash(guessWord, guessArrlen);


	while (attempts > 0) {


		cout << "Enter your guess letter:" << endl;
		cin >> guessletter;

		int wordAttempt = matchWord(guessletter, guessWord, correctWordLen, correctWord, &win);


		if (wordAttempt == 0) {
			cout << "Wrong Letter!" << endl;
			attempts--;				//Decrease Attempt
			cout << "Attempts Left:" << attempts << endl;
			displayWord(guessWord, correctWordLen);
			gameDisplay(attempts);
		}

		else if (wordAttempt == 3) {
			cout << "___________" << endl;
			cout << "You've Won!" << endl;
			cout << "___________" << endl;
			break;
		}

		else if (wordAttempt == 2) {
			cout << "Guess Another Letter" << endl;
		}

		else if (wordAttempt == 1) {
			cout << "Correct Letter Guess!, Continue" << endl;
			cout << "Attempts Left:" << attempts << endl;

			//Winning Condition

			displayWord(guessWord, correctWordLen);
		}
	}

	if (attempts == 0) {
		cout << "Game Over" << endl;
		cout << endl;
		cout << "The word is:" << correctWord << endl;
		cout << endl;
	}

	// Clear Memory
	free(guessWord);
}