#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Board.h"
#include "GraphicBoard.h"

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
    Player *activePlayer    = nullptr;
    Player *nonActivePlayer = nullptr;
    string playerOneName;
    string playerTwoName;
    srand(time(0));   // Seed Random Number Generator

    // change default state from command line arguments
    for (int i = 1; i < argc; ++i) { 
        if (string(argv[i]) == "-deck1")    deck1 = argv[i+1];
        if (string(argv[i]) == "-deck2")    deck2 = argv[i+1];
        if (string(argv[i]) == "-testing")  testing = true;
        if (string(argv[i]) == "-graphics") graphics = true;
        if (string(argv[i]) == "-init") {
            initfile = argv[i+1];
            ifs.open(initfile);
            init = true;
        }
    }

    // print game state (for testing purposes
    cout << "init: "     << init     << " " << initfile << endl;
    cout << "graphics: " << graphics << endl;
    cout << "testing: "  << testing  << endl;
    cout << "deck1: "    << deck1    << endl;
    cout << "deck2: "    << deck2    << endl;

    // The game begins by first asking both players for their names.
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

    Player playerOne(playerOneName, 1, deck1);
    Player playerTwo(playerTwoName, 2, deck2);
    if (!testing) {
      playerOne.shuffleDeck();
      playerTwo.shuffleDeck();
    }

    activePlayer    = &playerOne;
    nonActivePlayer = &playerTwo;
    activePlayer->setActive(true);
    activePlayer->setState(State::StartTurn);
    Board board(testing);
    board.setPlayer(&playerOne, 1);
    board.setPlayer(&playerTwo, 2);

    activePlayer->changeMana(1);
    playerOne.addObserver(&board);
    playerTwo.addObserver(&board);

    shared_ptr<GraphicBoard> gb= nullptr;
    if (graphics) {
      auto g = make_shared<GraphicBoard>(800);
      gb = g;
      gb->setBoard(&board);
      playerOne.addObserver(&*gb);
      playerTwo.addObserver(&*gb);
    }

    playerOne.drawFromDeck(5); // draw 5 cards
    playerTwo.drawFromDeck(5); // draw 5 cards

    string command;

    while(true) {
        int minion = 0;
        int card = 0;
        int targetPlayer = 0;
        int otherMinion = 0;
        int currentPlayerNum = activePlayer->getNum();
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
                "      end -- End the current player's turn.\n"
                "      quit -- End the game.\n"
                "      attack minion other-minion -- Orders minion to attack other-minion.\n"
                "      attack minion -- Orders minion to attack the opponent.\n"
                "      play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n"
                "      use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player.\n"
                "      inspect minion -- View a minion's card and all enchantments on that minion.\n"
                "      hand -- Describe all cards in your hand.\n"
                "      board -- Describe all cards on the board.\n";
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
                board.attackMinion(currentPlayerNum, minion, otherMinion);
            } else {
                cout << "Active player's minion " << minion << " is attacking the other player" << endl;
                board.attackPlayer(currentPlayerNum, minion);
                cout << "Other player health: " << nonActivePlayer->getHealth() << endl;
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
                    if (currentPlayerNum == 1) {
                        board.playCardP1(card, targetPlayer, 0);
                    } else {
                        board.playCardP2(card, targetPlayer, 0);
                    }
                } else {
                    cout << "Playing card: " << card << " on player " << targetPlayer << "'s minion: " << stoi(targetCard) << endl;
                    if (currentPlayerNum == 1) { // if active player is P1
                        board.playCardP1(card, targetPlayer, stoi(targetCard));
                    } else {
                        board.playCardP2(card, targetPlayer, stoi(targetCard));
                    }
                }
            } else {
                cout << "Playing card: " << card << endl;
                if (currentPlayerNum == 1) { // if active player is P1
                    board.playCardP1(card);
                } else {
                    board.playCardP2(card);
                }
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
                cout << "Using card: " << card << " on player " << targetPlayer << "'s minion: " << stoi(targetCard) << endl;
                board.useActivatedAbility(currentPlayerNum, card, targetPlayer, stoi(targetCard));
            } else {
                cout << "Using card: " << card << endl;
                board.useActivatedAbility(currentPlayerNum, card);
            }
        } else if (command == "end")                { board.endTurn(activePlayer, nonActivePlayer); swap(activePlayer, nonActivePlayer);
        } else if (command == "quit")               { break;
        } else if (command == "inspect")            { 
            if (init) {
                ifs >> minion; 
            } else {
                cin >> minion;
            }
            board.inspect(currentPlayerNum, minion);
        } else if (command == "hand")               { activePlayer->showHand();
        } else if (command == "board")              { board.display();
        } else if (command == "draw" && testing)    { activePlayer->drawFromDeck(1);
        } else if (command == "discard" && testing) { 
            if (init) {
                ifs >> minion;
            } else {
                cin >> minion;
            }
            activePlayer->removeFromHand(minion);
        }
        if (activePlayer->getHealth() <= 0 and nonActivePlayer->getHealth() <= 0) {
            cout << activePlayer->getName() << " and " << nonActivePlayer->getName() << " tied!" << endl;
            break;
        } else if (activePlayer->getHealth() <= 0) {
            cout << nonActivePlayer->getName() << " won!" << endl;;
            break;
        } else if (nonActivePlayer->getHealth() <= 0) {
            cout << activePlayer->getName() << " won!" << endl;;
            break;
        }
    }
}
