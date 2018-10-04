#include "ship.h"

Ship::Ship(int length) : _length(length), _hits(0)
{
}

int Ship::GetLength()
{
    return _length;
}

void Ship::TakeHit()
{
    if (_hits < _length)
        _hits++;
}

bool Ship::IsDestroyed()
{
    return _hits == _length;
}

Destroyer::Destroyer() : Ship(4)
{
}

BattleShip::BattleShip() : Ship(5)
{
}
