#include <vector>
#include <memory>
#include "GraphicBoard.h"
#include "Board.h"

using namespace std;

GraphicBoard::GraphicBoard(int winSize):winSize{winSize}, xw{winSize, winSize}{
  xw.fillRectangle(0, 0, winSize, winSize, Xwindow::Brown);                         // background
  xw.fillRectangle(15, 15, winSize-15*2, bth + ch*5 + 15, Xwindow::Yellow);         // game board
  xw.drawBigString(winSize/2-95, bth + ch*2 + 20*2 + 45,"Sorcery", Xwindow::Black); // game title
}


Xwindow::Colour col(string type) {
  if (type == "Minion") return Xwindow::Green;
  if (type == "Enchantment") return Xwindow::Cyan;
  if (type == "Spell") return Xwindow::Blue;
  if (type == "Ritual") return Xwindow::Magenta;
}

void emptyCard(int x, int y, Xwindow &xw, Xwindow::Colour c) { xw.fillRectangle(x, y, cw, ch, c); }

void drawPlayer(int x, int y, Xwindow &xw, Player *p) { 
    xw.fillRectangle(x, y, cw, ch, Xwindow::White); 
    int m = (p->getNum() == 1) ? m = 105 : m = 15;
    xw.drawString(x + 50,  y + 55, p->getName(), strCol);
    xw.drawString(x + 5,   y + m, to_string(p->getHealth()), strCol);
    xw.drawString(x + 110, y + m, to_string(p->getMana()), strCol);
}

void drawDescription(int x, int y, Xwindow &xw, string s, int width, Xwindow::Colour c) {
    int charsPerLine = 19;
    int start = 0;
    int height = y;
    while (start < s.length()) {
        xw.drawString(x, height, s.substr(start, charsPerLine), c);
        start += charsPerLine;
        height += 15;
    }
}

void drawCard(int x, int y, Xwindow &xw, shared_ptr<Card> c, bool dead = false) {
    if (dead) {
      xw.fillRectangle(x, y, cw, ch, Xwindow::Red);
    } else {
      xw.fillRectangle(x, y, cw, ch, col(c->getType()));
    }
    xw.drawString(x + 5, y + 15, c->getName(), strCol);
    xw.drawString(x + 110, y + 15, to_string(c->getCost()), strCol);

  if (c->getType() == "Minion") {
    shared_ptr<Minion> m = dynamic_pointer_cast<Minion>(c);
    xw.drawString(x + 80, y + 30, c->getType(), strCol);
    if (m->getAC() != 0) {
      xw.drawString(x + 5, y + 45, to_string(m->getAC()), strCol);
      drawDescription(x + 5, y + 60, xw,c->getInfo(), cw, strCol); // print minion description
    } else {
      drawDescription(x + 5, y + 50, xw,c->getInfo(), cw, strCol); // print minion description

    }
    xw.drawString(x + 5, y + 105, to_string(dynamic_pointer_cast<Minion>(c)->getAttack()), strCol);
    xw.drawString(x + 110, y + 105, to_string(dynamic_pointer_cast<Minion>(c)->getDefence()), strCol);
  }
  if (c->getType() == "Enchantment") {
    shared_ptr<Enchantment> e = dynamic_pointer_cast<Enchantment>(c);
    xw.drawString(x + 50, y + 30, c->getType(), strCol);
    drawDescription(x + 5, y + 50, xw,c->getInfo(), cw, strCol); // print minion description

    if (e->getAttack() != 0 && e->getDefence() != 0) {
      if (e->getName() == "Giant Strength") {
        xw.drawString(x + 5, y + 105, "+" + to_string(e->getAttack()), strCol);
        xw.drawString(x + 110, y + 105, "+" + to_string(e->getDefence()), strCol);
      } else if (e->getName() == "Enrage") {
        xw.drawString(x + 5, y + 105, "*" + to_string(e->getAttack()), strCol);
        xw.drawString(x + 110, y + 105, "*" + to_string(e->getDefence()), strCol);
      }
    }
  }
  if (c->getType() == "Spell") {
    xw.drawString(x + 85, y + 30, c->getType(), strCol);
    drawDescription(x + 5, y + 50, xw,c->getInfo(), cw, strCol); // print minion description
  }
  if (c->getType() == "Ritual") {
    shared_ptr<Ritual> r = dynamic_pointer_cast<Ritual>(c);
    xw.drawString(x + 80, y + 30, c->getType(), strCol);
    xw.drawString(x + 5, y + 45, to_string(r->getAC()), strCol);
    drawDescription(x + 5, y + 60, xw,c->getInfo(), cw, strCol); // print minion description
  }
}

void GraphicBoard::notify(Player &p) {
    vector<shared_ptr<Card>> hand = p.getHand();
    vector<shared_ptr<Minion>> p1c = board->getCards(1);
    vector<shared_ptr<Minion>> p2c = board->getCards(2);
    vector<shared_ptr<Minion>> p1g = board->playerOne->getGrave();
    vector<shared_ptr<Minion>> p2g = board->playerTwo->getGrave();

    int s = winSize/5;

    // row 1
    for (int i = 0; i < 5; ++i) {
      if (i == 0 && board->getRitual(1)) drawCard(s*i + 20,  bth, xw, board->getRitual(1));
      if (i == 2)                        drawPlayer(s*i + 20,bth, xw, board->playerOne);
      if (i == 4 && p1g.size() != 0)     drawCard(s*i + 20,  bth, xw, p1g.back(), true);
    }

    // row 2
    for (int i = 0; i < p1c.size(); ++i) drawCard(s*i + 20,  bth + ch + 20, xw, p1c.at(i));
    for (int i = p1c.size(); i < 5; ++i) emptyCard(s*i + 20, bth + ch + 20, xw, Xwindow::Yellow);

    // row 3
    for (int i = 0; i < p2c.size(); ++i) drawCard(s*i + 20,  bth + ch*3, xw, p2c.at(i));
    for (int i = p2c.size(); i < 5; ++i) emptyCard(s*i + 20, bth + ch*3, xw, Xwindow::Yellow);

    // row 4
    for (int i = 0; i < 5; ++i) {
      if (i == 0 && board->getRitual(2)) drawCard(s*i + 20,  bth + ch*4 + 20, xw, board->getRitual(2));
      if (i == 2)                        drawPlayer(s*i + 20,bth + ch*4 + 20, xw, board->playerTwo); 
      if (i == 4 && p2g.size() != 0)     drawCard(s*i + 20,  bth + ch*4 + 20, xw, p2g.back());
    }

    // active player hand
    if (p.getActive() && (p.getState() == State::StartTurn || p.getState() == State::MinionEnter)) {
      for (int i = 0; i < p.getHand().size(); ++i) {
        drawCard(s*i + 20, bth + ch*5 + 60, xw, hand.at(i));
      }
      for (int i = p.getHand().size(); i < 5; ++i) {
        emptyCard(s*i + 20, bth + ch*5 + 60, xw, Xwindow::Brown);
      }
    }
    
}

void GraphicBoard::setBoard(Board *b){ board = b; }
