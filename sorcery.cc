#include <iostream>
#include <string>
#include <sstream>


int main(int argc, char *argv[]) {

  // Initialize default state
  std::string deck1 = "default.deck";
  std::string deck2 = "default.deck";
  std::string initfile = "";
  bool init     = false;
  bool testing  = false;
  bool graphics = false;

  bool quit = false;
  //Player *activePlayer = nullptr;
  //Player *nonActivePlayer = nullptr;


  // change default state from command line arguments
  for (int i = 1; i < argc; ++i) { 
    if (std::string(argv[i]) == "-deck1") deck1 = argv[i+1];
    if (std::string(argv[i]) == "-deck2") deck2 = argv[i+1];
    if (std::string(argv[i]) == "-testing") testing = true;
    if (std::string(argv[i]) == "-graphics") graphics = true;
    if (std::string(argv[i]) == "-init") {
      initfile = argv[i+1];
      init = true;
    }
  }


  // print game state (for testing purposes
  std::cout << "init: " << init << " " << initfile << std::endl;
  std::cout << "graphics: " << graphics << std::endl;
  std::cout << "testing: " << testing << std::endl;
  std::cout << "deck1: " << deck1 << std::endl;
  std::cout << "deck2: " << deck2 << std::endl;


  while(!quit) {
    std::string minion, card, targetPlayer, targetCard, otherMinion, tmp;
    std::stringstream ss;
    std::string command;
    std::cin >> command;

    if (command == "help") {
      std::cout << "Commands:\n"
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
      // end the current player turn
      // std::swap(activePlayer, nonActivePlayer);
    } else if (command == "quit") {
      quit = true;
    } else if (command == "attack") {
      std::cin >> minion >> otherMinion;
      std::cout << "Minion: " << minion << " is attacking: " << otherMinion << std::endl;
      // attack minion and otherMinion
    } else if (command == "play") {
      std::getline(std::cin, tmp);
      ss.clear(); ss.str(tmp); tmp = "";
      int count = 0;
      while (ss >> tmp) {
        ++count;
        if (count == 1) card = tmp;
        if (count == 2) targetPlayer = tmp;
        if (count == 3) targetCard = tmp;
      }

      if (count == 3) {
        std::cout << "Card: " << card << ", targetPlayer: " << targetPlayer << ", targetCard: " << targetCard << std::endl; 
        // play card optionally targetting target card owned by target player
      } else {
        std::cout << "Card: " << card << std::endl;
        // play card normally
      }

    } else if (command == "use") {
      std::getline(std::cin, tmp);
      ss.clear(); ss.str(tmp); tmp = "";
      int count = 0;
      while (ss >> tmp) {
        ++count;
        if (count == 1) minion = tmp;
        if (count == 2) targetPlayer = tmp;
        if (count == 3) targetCard = tmp;
      }

      if (count == 3) {
        std::cout << "Minion: " << minion << ", targetPlayer: " << targetPlayer << ", targetCard: " << targetCard << std::endl; 
        // use minion targetting another minion
      } else {
        std::cout << "Minion: " << minion << std::endl;
        // use minion ability normally
      }
      

    } else if (command == "inspect") {
      std::cin >> minion;
      std::cout << minion;
      // inspect minion
    } else if (command == "hand") {
      // describe all cards in your hand
    } else if (command == "board") {
      // describe all cards on board
    }

  }


  return 0;
}
