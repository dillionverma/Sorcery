#include <iostream>
#include <string>
#include <sstream>
#include "Player.h"

using namespace std;

int main(int argc, char *argv[]) {

    // Initialize default state
    string deck1 = "default.deck";
    string deck2 = "default.deck";
    string initfile = "";
    bool init     = false;
    bool testing  = false;
    bool graphics = false;
    //Player *activePlayer = nullptr;
    //Player *nonActivePlayer = nullptr;

    // change default state from command line arguments
    for (int i = 1; i < argc; ++i) { 
        if (string(argv[i]) == "-deck1") deck1 = argv[i+1];
        if (string(argv[i]) == "-deck2") deck2 = argv[i+1];
        if (string(argv[i]) == "-testing") testing = true;
        if (string(argv[i]) == "-graphics") graphics = true;
        if (string(argv[i]) == "-init") {
            initfile = argv[i+1];
            init = true;
        }
    }

    // print game state (for testing purposes
    cout << "init: " << init << " " << initfile << endl;
    cout << "graphics: " << graphics << endl;
    cout << "testing: " << testing << endl;
    cout << "deck1: " << deck1 << endl;
    cout << "deck2: " << deck2 << endl;

    // The game begins by first asking both players for their names.
    cout << "Player 1, please enter your name" << endl;
    string playerOneName;
    cin >> playerOneName;
    cout << "Player 2, please enter your name" << endl;
    string playerTwoName;
    cin >> playerTwoName;
   
    cout << "Welcome, " << playerOneName << " and " << playerTwoName << "!" << endl;

    // Create players - this also shuffles and sets up decks and hands
    Player playerOne(playerOneName);
    Player playerTwo(playerTwoName);

    // game begins within no command, so first effects must occur right away
    // activePlayer.updateMana(activePlayer.mana++);
    // activePlayer.drawFromDeck();

    string command;

    while(cin >> command) {
        int minion = 0;
        int card = 0;
        int targetPlayer = 0;
        int otherMinion = 0;
        string tmp, targetCard;

        if (command == "help") {
            cout << "Commands:\n"
                "      help -- Display this message.\n"
                "      end -- End the current player’s turn.\n"
                "      quit -- End the game.\n"
                "      attack minion other-minion -- Orders minion to attack other-minion.\n"
                "      attack minion -- Orders minion to attack the opponent.\n"
                "      play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n"
                "      use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player.\n"
                "      inspect minion -- View a minion’s card and all enchantments on that minion.\n"
                "      hand -- Describe all cards in your hand.\n"
                "      board -- Describe all cards on the board.\n";
        } else if (command == "end") {
            // end of turn events occur for current player
            cout << "end" << endl;
            // swap(activePlayer, nonActivePlayer);
            // activePlayer.updateMana(activePlayer.mana++);
            // activePlayer.drawFromDeck();
            // beginning of turn events occur for new player
        } else if (command == "quit") {
            break;
        } else if (command == "attack") {
            getline(cin, tmp);
            istringstream iss {tmp};
            int count = 0;
            while (iss >> tmp) {
                ++count;
                if (count == 1) minion = stoi(tmp);
                if (count == 2) {
                    otherMinion = stoi(tmp);
                    break;
                }
            }
            if (otherMinion) {
                cout << "Active player's minion " << minion << " is attacking other player's minion " << otherMinion << endl;
            } else {
                cout << "Active player's minion " << minion << " is attacking the other player" << endl;
            }
        } else if (command == "play") {
            getline(cin, tmp);
            istringstream iss {tmp};
            int count = 0;
            while (iss >> tmp) {
                ++count;
                if (count == 1) card = stoi(tmp);
                if (count == 2) targetPlayer = stoi(tmp);
                if (count == 3) {
                    targetCard = tmp;
                    break;
                }
            }
            if (count == 3) {
                if (targetCard == "r") {
                    cout << "Playing card: " << card << " on player " << targetPlayer << "'s ritual" << endl;
                } else {
                    cout << "Playing card: " << card << " on player " << targetPlayer << "'s minion: " << stoi(targetCard) << endl;
                }
            } else {
                cout << "Playing card: " << card << endl;
            }
        } else if (command == "use") {
            getline(cin, tmp);
            istringstream iss {tmp};
            int count = 0;
            while (iss >> tmp) {
                ++count;
                if (count == 1) card = stoi(tmp);
                if (count == 2) targetPlayer = stoi(tmp);
                if (count == 3) {
                    targetCard = tmp;
                    break;
                }
            }
            if (count == 3) {
                if (targetCard == "r") {
                    cout << "Using card: " << card << " on player " << targetPlayer << "'s ritual" << endl;
                } else {
                    cout << "Using card: " << card << " on player " << targetPlayer << "'s minion: " << stoi(targetCard) << endl;
                }
            } else {
                cout << "Using card: " << card << endl;
            }
        } else if (command == "inspect") {
            cin >> minion;
            cout << "Inspecting minion: " <<  minion << endl;
        } else if (command == "hand") {
            cout << "hand" << endl;
        } else if (command == "board") {
            cout << "board" << endl;
        } else if (command == "draw") {
            if (testing) {
             //   activePlayer.drawFromDeck();
                cout << "draw" << endl;
            }
        } else if (command == "discard") {
            if (testing) {
                cout << "discard" << endl;
            }
        }
    }
}
