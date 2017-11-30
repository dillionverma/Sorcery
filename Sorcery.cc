#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Board.h"

using namespace std;

int main(int argc, char *argv[]) {

    // Initialize default state
    string deck1 = "default.deck";
    string deck2 = "default.deck";
    string initfile = "";
    ifstream ifs;
    bool init     = false;
    bool testing  = false;
    bool graphics = false;
    Player *activePlayer = nullptr;
    Player *nonActivePlayer = nullptr;

    // change default state from command line arguments
    for (int i = 1; i < argc; ++i) { 
        if (string(argv[i]) == "-deck1") deck1 = argv[i+1];
        if (string(argv[i]) == "-deck2") deck2 = argv[i+1];
        if (string(argv[i]) == "-testing") testing = true;
        if (string(argv[i]) == "-graphics") graphics = true;
        if (string(argv[i]) == "-init") {
            initfile = argv[i+1];
            ifs.open(initfile);
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
    string playerOneName;
    string playerTwoName;
    if (init) {
        ifs >> playerOneName;
        ifs >> playerTwoName;
    } else {
        cout << "Player 1, please enter your name:" << endl;
        cin >> playerOneName;
        cout << "Player 2, please enter your name:" << endl;
        cin >> playerTwoName;
    }
    
    cout << "Welcome, " << playerOneName << " and " << playerTwoName << "!" << endl;

    // Create players - this also shuffles and sets up decks and hands
    Board board = Board();
    Player playerOne(playerOneName, 1);
    Player playerTwo(playerTwoName, 2);
    activePlayer = &playerOne;
    nonActivePlayer = &playerTwo;
    board.setP1(&playerOne);
    board.setP2(&playerTwo);

    // game begins within no command, so first effects must occur right away
    // activePlayer.updateMana(activePlayer.mana++);
    // activePlayer.drawFromDeck();

    string command;

    while(true) {
        int minion = 0;
        int card = 0;
        int targetPlayer = 0;
        int otherMinion = 0;
        string tmp, targetCard;

        if (init) {
            ifs >> command;
        } if(!init || ifs.eof()) {
            cin >> command;
            init = false;
        }

        if (cin.fail()) {
            break;
        }

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
            swap(activePlayer, nonActivePlayer);
            // activePlayer.updateMana(activePlayer.mana++);
            // activePlayer.drawFromDeck();
            // beginning of turn events occur for new player
        } else if (command == "quit") {
            break;
        } else if (command == "attack") {
            if (init) {
                getline(ifs, tmp);
            } else {
                getline(cin, tmp);
            }
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
            if (init) {
                getline(ifs, tmp);
            } else {
                getline(cin, tmp);
            }
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
                    // for sake of simplicity, let 0 represent r
                    // card.notify(b, targetPlayer, 0);
                } else {
                    cout << "Playing card: " << card << " on player " << targetPlayer << "'s minion: " << stoi(targetCard) << endl;
                    //card.notify(g, targetPlater, stoi(targetCard);
               }
            } else {
                cout << "Playing card: " << card << endl;
                // card.notify(b, currentPlayer);
            }
        } else if (command == "use") {
            if (init) {
                getline(ifs, tmp);
            } else {
                getline(cin, tmp);
            }
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
                    // for sake of simplicity, let 0 represent r.
                    //card.notify(b, targetPlayer, 0);
                } else {
                    cout << "Using card: " << card << " on player " << targetPlayer << "'s minion: " << stoi(targetCard) << endl;
                    //card.notify(b, targetPlayer, stoi(targetCard);
                }
            } else {
                cout << "Using card: " << card << endl;
                //card.notify(b, activePlayer);
           }
           // remove card from hand
           // activePlayer.removeCard(card);
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
