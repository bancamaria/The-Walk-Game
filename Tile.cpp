#include "Tile.h"

Tile::Tile(Item* AssignedItem, Trap* AssignedTrap): item(AssignedItem), trap(AssignedTrap) {}
Tile::~Tile() {
    delete item;
    delete trap;
}

void Tile::clearItem() {
    if(item != 0) {
        delete item;
        item = 0;
    }
}

const Item* Tile::getItem() const {
    return item;
}

void Tile::setItem(Item* AssignedItem) {
    item = AssignedItem;
}

const Trap* Tile::getTrap() const {
    return trap;
}
void Tile::setTrap(Trap* AssignedTrap) {
    trap = AssignedTrap;
}
