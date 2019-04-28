#include "Item.h"

Item::Item(int AssignedType): Type(AssignedType) {}
Item::~Item() {}
const int Item::getType() const {
    return Type;
}
