#pragma once

#include "ship.h"
#include "cellstatus.h"

struct Cell
{
  public:
    Ship *OccupyingShip;
    CellStatus Status;

  public:
    Cell() : OccupyingShip(NULL), Status(CellStatus_Unshelled) {}
};