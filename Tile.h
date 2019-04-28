#ifndef TILE_H
#define TILE_H
#include "Item.h"
#include "Trap.h"

class Tile {
    Item* item; // Contained item (if existent)
    Trap* trap; // Contained trap (if existent)
public:
    Tile(Item* AssignedItem = 0, Trap* AssignedTrap = 0);   // Constructor with AssignedItem or AssignedTrap parameter
    ~Tile();                                                // Destructor in which the Item and the Trap are destroyed, if existent
    void clearItem();                                       // Method to clear contained item if used by the Player
    const Item* getItem() const;                            // Get-method for contained item
    void setItem(Item* AssignedItem);                       // Set-method for contained item
    const Trap* getTrap() const;                            // Get-method for contained trap
    void setTrap(Trap* AssignedTrap);                       // Set-method for contained trap
};

#endif // TILE_H
