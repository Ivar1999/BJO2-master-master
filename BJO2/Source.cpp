#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <conio.h>

using namespace std;


string arraytype[] = { " of clubs", " of diamonds", " of spades", " of hearts" };
string arraynumber[] = { "2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace" };

struct cardtype
{
	int type;
	int number;
};
vector <cardtype> availablecards;
vector <cardtype> usedcards;
struct card
{
	int value;
	string display;
	cardtype type;
};
struct Hand
{
	vector <card> cards;
	int getsum() {
		int hand = 0;
		for (int i = 0; i < cards.size(); i++)
		{
			//cout << i+1 << ". card is: " << cards.at(i).value << endl;
			//cout << i +1 << ". card is: " <<cards.at(i).display << endl;
			hand += cards.at(i).value;

		}
		
		return hand;
	}	
	void getdisplay() {
		for (int i = 0; i < cards.size(); i++)
		{
			cout << i + 1 << ". card is: " << cards.at(i).display << endl;
		}
	}

};

card getrandomcard();
card getrandomcard()
{
	const int randomnumber = rand() % availablecards.size();
	//cout << "randomnumber: " << randomnumber << endl;
	//cout << "availablecards.size(): " << availablecards.size() << endl;
	usedcards.push_back(availablecards[randomnumber]);	
	card Card;
	Card.type = availablecards[randomnumber];
	availablecards.erase(availablecards.begin() + randomnumber);
	//cout << "Card.type.number: " << Card.type.number << endl;
	switch (Card.type.number)
	{
	case 9: Card.value = 10;
		break;
	case 10: Card.value = 10;
		break;
	case 11: Card.value = 10;
		break;
	case 12: Card.value = 11;
		break;
	default: Card.value = Card.type.number+2;
		break;
	}
	Card.display = arraynumber[Card.type.number] + arraytype[Card.type.type];
	

	return Card;
}
void shuffle();
void shuffle() // used cards after 1 round back into available cards
{
	for (int i = 0; i < usedcards.size(); i++)
	{
		availablecards.push_back(usedcards[i]);
	}
	usedcards.erase(usedcards.begin(), usedcards.end());
}
/*int wincon();
int wincon()
{

}*/


int main() {
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			cardtype type;
			type.number = j;
			type.type = i;
			availablecards.push_back(type);
		}
	}
	//card Card = getrandomcard();
	//cout << Card.value << " " << Card.display; // value, number&type
	//cout << Card.display;
	
	int option;
	int money = 100;
	do
	{
		int bet = 0;
		cout << "Your account is: " << money << "$\n" << "Minimum bet is 10$.\nPlace your bet.\n";
		do
		{
			cin >> bet;
			if (bet < 10)
			{
				cout << "Your bet is too low. Try again.\n";
			}
		} while (bet < 10); 
		money -= bet;
		//cout << money;
		system("pause");
		Hand player;
		Hand dealer;
		dealer.cards.push_back(getrandomcard());
		player.cards.push_back(getrandomcard());
		player.cards.push_back(getrandomcard());
		do
		{
			system("cls");
			dealer.getdisplay();
			cout << "Dealers card is: "<< dealer.getsum() << "\n" << endl;
			player.getdisplay();
			cout << "Your hand is: " << player.getsum() << "\n" << endl;

			//cout << "hand value:" << player.getsum() << "\ncard value:" << Card.value << endl;
			//cout << Card.display << endl;
			cout << "\nhit or stand\n";
			cout << " 1       2  \n";
			cin >> option;
			if (option == 1)
			{
				system("cls");
				player.cards.push_back(getrandomcard());
			}
			
			
		} while ( option == 1 && player.getsum() < 21);// hand value < 21 || stand
		//system("cls");
		//cout << "Your hand is: " << player.getsum() << endl;
		//dealer.cards.push_back(getrandomcard());
		//const int playerhand = player.getsum();
		//const int dealerhand = dealer.getsum();
		if (player.getsum() > 21)
		{
			system("cls");
			//cout << "Dealer card is: " << dealer.getsum() << endl;
			player.getdisplay();
			cout << "Your hand is: " << player.getsum() << "\nPlayer loses. You went over 21." << endl;
		}
		else
		{
			dealer.cards.push_back(getrandomcard());
			//cout << dealer.getsum();
			draw:
			if (dealer.getsum() < 17)
			{
				dealer.cards.push_back(getrandomcard());
				goto draw;
			}
			//system("pause");
			/*while (dealer.getsum() > 1 && dealer.getsum() <= 16)
			{
				dealer.cards.push_back(getrandomcard());
			}*/
			system("cls");
			dealer.getdisplay();
			cout << "Dealers hand is: " << dealer.getsum() << "\n" << endl;
			player.getdisplay();
			cout << "Your hand is: " << player.getsum() << endl;

			if (dealer.getsum() > 21)
			{
				cout << "\nDealer went over 21.\n\nPlayer wins." << endl;
				cout << "You won: " << bet << "$" << endl;
				money += (bet * 2);
			}
			else
			{
				//int dealerhand = dealer.getsum();
				//system("cls");
				//cout << playerhand << " " << dealerhand;
				//system("pause");
				if (player.getsum() > dealer.getsum())
				{
					cout << "\n\nPlayer wins." << endl;
					cout << "You won: " << bet << "$" << endl;
					money += (bet * 2);
				}
				else if (player.getsum() == dealer.getsum())
				{
					cout << "\n\nIt's a draw." << endl;
					cout << "You won: 0$" << endl;
					money += bet;
				}
				else if (player.getsum() < dealer.getsum())
				{
					cout << "\n\nDealer wins." << endl;
					cout << "You lost: " << bet << "$" << endl;
				}
				system("pause");
			}


		}
		

		// if hand > dealer bet x2 -> money
		shuffle();
		system("pause");
		system("cls");

		//cout << "test\n";
	} while (money > 10); // money > 0
	cout << "Your account balance is: " << money << "$" << endl;
	cout << "Set in money to play more." << endl;
	system("pause");

	return 0;
}