#ifndef GRAPHICBOARD_H
#define GRAPHICBOARD_H
#include "window.h"
#include "Player.h"
#include "Observer.h"
#include "Board.h"

const int cw  = 120;
const int ch  = 110;
const int bth = 20;
const Xwindow::Colour strCol = Xwindow::Black; // constant for string colour

class GraphicBoard: public Observer {
  const int winSize;
  Xwindow xw;
  Board *board;
  public:
    GraphicBoard(int winSize=800);
    void notify(Player &p) override;
    void setBoard(Board *b);
};
#endif
