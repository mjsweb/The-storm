#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <windows.h>
using namespace std;

class Creature {
public:

	// Set creatures variables
	Creature(string newName, int newHealth, int newDamage, int newGold) {
		name = newName;
		health = newHealth;
		damage = newDamage;
		gold = newGold;
	}

	// Set new health
	void setHealth(int amount) {
		health -= amount;
	}

	// Get creature health
	int getHealth() {
		return health;
	}

	// Get creature gold
	int getGold() {
		return gold;
	}

	// Get creature damage
	int getDamage() {
		return damage;
	}

	// Get creature name
	string getName() {
		return name;
	}
private:
	string name;
	int health;
	int damage;
	int gold;
};

//player name
string playerName	;

// Fight function
void fight(int &health, int &gold, int damage) {

	// Battle boolean
	bool battle = true;

	// Create vector of creature Class
	vector<Creature> creatures;

	// Creature creatures
	creatures.push_back( Creature("Lava Slime", 100, 10, 20) );
	creatures.push_back( Creature("Fury Rat", 100, 15, 20) );
	creatures.push_back( Creature("Wear Pig", 120, 25, 30) );
	creatures.push_back( Creature("Little Goblin", 130, 35, 40) );
	creatures.push_back( Creature("Hobit Wizard", 150, 45, 45) );
	creatures.push_back( Creature("Sinister Witch", 180, 70, 120) );

	// Random index
	int randIndex = rand() % creatures.size();

	// Choose a random creature
	Creature randCreature = creatures[ randIndex ];

	// Clear console
	system("cls");

	// Print room
	cout << "[Battle]"													<< endl;
	cout << "> Player Summary <\n" 										<< endl;
	cout << "- "<<playerName											<< endl;
	cout << "- Health: " 		<< health 								<< endl;
	cout << "- Gold: " 			<< gold 								<< endl;
	cout << endl;

	// Print fight decisions
	cout << "- A wild " << randCreature.getName() 	<< " appeared!" 	<< endl;
	cout << endl;
	cout << "What would you like to do?" 				 				<< endl;
	cout << "- f, " << right << "fight" 								<< endl;
	cout << "- r, " << right << "run, \t-10 Gold" 		 				<< endl;
	cout << endl;

	// Get user input
	while (battle) {

		// user input
		string response;

		// Get input
		cin >> response;

		// Fight
		if (response == "f") {

			system("cls");
			
			// Roll Player dice
			int playerDice = rand() % 10 + 1;

			// Roll Creature dice
			int creatureDice = rand() % 10 + 1;

			// Difference
			int difference = 0;

			// Print dice rolls
			cout << "\nYou have rolled a " 					   << playerDice   << "!" << endl;
			cout << randCreature.getName() << " has rolled a " << creatureDice << "!" << endl;

			// If creature dice higher than player dice,
			// subtract creature dice first, else vice versa.

			// Creature attack
			if (creatureDice > playerDice) {

				// Get difference from both dices
				difference = creatureDice - playerDice;

				// Standard damage
				if (difference < 5) {

					// Subtract player health
					health -= randCreature.getDamage();

					// Print creature attack summary
					cout << endl;
					cout << randCreature.getName() 	<< " has inflicted " << randCreature.getDamage()  << " damage!" << endl;

					// Print health
					cout << "- Player Health: " << health << endl;
					cout << "- " << randCreature.getName() << " Health: " << randCreature.getHealth() << endl;
					cout << endl;
				}

				// Critical damage
				else{

					// Subtract player health
					health -= randCreature.getDamage()*2;

					// Print creature attack summary
					cout << endl;
					cout << randCreature.getName() 	<< " has CRIT and inflicted " << randCreature.getDamage()*2  << " damage!" << endl;

					// Print health
					cout << "- Player Health: " << health << endl;
					cout << "- " << randCreature.getName() << " Health: " << randCreature.getHealth() << endl;
					cout << endl;

				}

				// Check if player health is <= 0
				if (health <= 0) {
					health = 0;
					battle = false;
					cout << "You have died." << endl;
				}
				else{
					cout << "Choose your next move." <<endl;
					cout << "- f, " << right << "fight" 								<< endl;
					cout << "- r, " << right << "run, \t-10 Gold" 		 				<< endl;
				}
			}

			// Player attack
			else{
				// Get difference from both dices
				difference = playerDice - creatureDice;

				// Standard damage
				if (difference < 5) {

					// Subtract player health
					randCreature.setHealth(damage);

					// Print creature attack summary
					cout << endl;
					cout << "You have and inflicted " << damage << " damage!" << endl;

					// Print health
					cout << "- Player Health: " << health << endl;
					cout << "- " << randCreature.getName() << " Health: " << randCreature.getHealth() << endl;
					cout << endl;
				}
				// Critical damage
				else{

					// Subtract player health
					randCreature.setHealth(damage*2);

					// Print creature attack summary
					cout << endl;
					cout << "You have CRIT and inflicted " << damage*2  << " damage!" << endl;

					// Print health
					cout << "- Player Health: " << health << endl;
					cout << "- " << randCreature.getName() << " Health: " << randCreature.getHealth() << endl;
					cout << endl;
				}

				// Check if creature health is <= 0
				if (randCreature.getHealth() <= 0) {
					battle = false;

					// Add player gold
					gold += randCreature.getGold();
					cout << ">" << randCreature.getName() << " has died<" << endl;
				}
				else {
					cout << "Choose your next move." <<endl;
					cout << "- f, " << right << "fight" 								<< endl;
					cout << "- r, " << right << "run, \t-10 Gold" 		 				<< endl;
				}
			}
		}
		// Run
		else if (response == "r") {
			battle = false;

			// If player does not have enough gold to throw, he pays
			// with blood (health will be subtracted to
			// the difference of the cost of running
			// and your current gold
			if (gold < 10) {
				health -= (10 - gold);
			}else{
				gold -= 10;
			}
		}
	}

	// Player confirmation
	cout << endl;
	cout << "Press Enter to continue..." << endl;
	cin.get();
	cin.get();
}

int main() {

	// Make random actually random
	srand(time(0));

	// Game loop
	bool game = true;

	// Game outcome
	/* Exit codes
	 * 0: Game Quit
	 * 1: Game Win
	 * 2: Game Lose
	 */
	int exitCode = -1;

	// Player variables
	int gold 		= 0;
	int health 		= 250;
	int damage		= 60;

	// Print introduction
	for (int i=0; i<75; i++)
		cout << "#";
	cout << endl;
	cout << "- Hello! Welcome to ARR-EN-GEE!"  					  				<< endl;
	cout << "- The goal of this game is to reach 250 Gold!" 	  				<< endl;
	cout << "- You start with 10 Gold and 250 health." 			  				<< endl;
	cout << endl;

	// Print game rules
	cout << "- When fighting a creature you and the creature will roll"  		<< endl;
	cout << "  a dice from 1 - 10. The person who rolls a higher number" 		<< endl;
	cout << "  will attack that turn AND if the difference between the dice" 	<< endl;
	cout << "  rolls is 5 or greater,that person shall do critical damage." 	<< endl;
	cout << endl;

	// Player confirmation
	cout << "Press Enter to continue..." << endl;
	cin.get();	
	
	//player name
	cout << "What is your name traveler? " << endl;
	getline(cin,playerName);
	
	

	// Keep getting input until Player would like to quit
	while (game) {

		// Quit Game, player win
		if (gold >= 250) {
			exitCode = 1;
		}

		// Quit Game, player death
		else if (health <= 0) {
			cout << "There's no room for the WEAK in dungeons.\n\n";
			cout << "Press Enter to retry." << endl;
			cin.get();
			cin.get();
			exitCode = 2;
		}

		// Continue game
		else {

			// Clear console
			system("cls");

			// Print room
			cout << "[Home]" 									<< endl;

			/* Summary after action */
			cout << "> Player Summary <\n" 						<< endl;
			cout << "- "<<playerName							<< endl;
			cout << "- Health: " 		<< health 				<< endl;
			cout << "- Gold: " 			<< gold 				<< endl;
			cout << endl;

			// Print player decisions
			cout << "What would you like to do?" 				<< endl;
			cout << "- f, " << "fight" 							<< endl;
			cout << "- s, " << "sleep \t+15 health, -5 gold" 	<< endl;
			cout << "- q, " << "quit game" 						<< endl;
			cout << endl;

			string answer;

			// Get input from user
			cin >> answer;

			// Quite Game, player request
			if (answer == "q") {
				exitCode = 0;
			}

			// Play Game
			else{

				// Fight
				if (answer == "f") {

					// Player fight outcome
					fight( health, gold, damage );
				}

				// Sleep
				else if (answer == "s") {
					// Check if player has enough gold
					if (gold >= 5) {
						health += 15;
						gold -= 5;
					}
				}
			}
		}

		// Exit messages
		if (exitCode == 0) {
			// Print exit message
			cout << endl;
			cout << "Thanks for playin' AREENGEE!" << endl;

			// Quit game
			game = false;
		}else if (exitCode == 1) {
			// Print win message
			cout << endl;
			cout << playerName<<" have reached 250 GOLD!! NICE JOB!" << endl;
			cout << "Thanks for playin' AREENGEE!\nYou shall forever be known as "<<playerName<<" the dungeon master!" << endl;

			// Quit game
			game = false;
		}else if (exitCode == 2) {
			// Print death message
			gold 		= 10;
			health 		= 250;
			damage		= 60;
		}
	}

	// Player confirmation
	cout << "Press Enter to continue..." << endl;
	cin.get();
	cin.get();

	return 0;
}
