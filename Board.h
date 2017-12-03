#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include "Player.h"
#include "Ritual.h"
#include "Minion.h"
#include "Observer.h"

class Subject;
class Board: public Observer{
  Player *playerOne = nullptr;
  Player *playerTwo = nullptr;
  std::shared_ptr<Ritual> ritualP1 = nullptr;
  std::shared_ptr<Ritual> ritualP2 = nullptr;
  std::vector<std::shared_ptr<Minion>> cardsP1;
  std::vector<std::shared_ptr<Minion>> cardsP2;
  public:
    Board();
    void setPlayer(Player *p, int playerNum);
    void endTurn(Player *activePlayer, Player *nonActivePlayer);
    void playCardP1(int slot, int player = -1, int otherSlot = -1); // play card at P1 slot
    void playCardP2(int slot, int player = -1, int otherSlot = -1); // can be refactored later 
    void toGrave(int slot, int playerNum);
    void toHand(int slot, int playerNum);
    void attackMinion(int currentPlayer, int minion, int otherMinion);
    void attackPlayer(int currentPlayer, int minion);
    void inspect(int currentPlayer, int minion);
    void notify(Player &p) override;
    std::shared_ptr<Ritual> getRitual(int playerNum) const;
    std::vector<std::shared_ptr<Minion>> &getCards(int playerNum);
    void setRitual(std::shared_ptr<Ritual> ritual, int playerNum);
    void display();
};

#endif
