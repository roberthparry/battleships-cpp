#pragma once

class Ship
{
  private:
    int _length;
    int _hits;

  protected:
    Ship(int length);

  public:
    int GetLength();
    void TakeHit();
    bool IsDestroyed();
};

class Destroyer : public Ship
{
  public:
    Destroyer();
};

class BattleShip : public Ship
{
  public:
    BattleShip();
};