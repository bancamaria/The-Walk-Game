#ifndef ITEM_H
#define ITEM_H

class Item {
    // Item Type (Corresponding Robot Type)
    const int Type;
public:
    // Constructor with Type parameter
    Item(int AssignedType = 0);
    // Destructor
    ~Item();
    // Get-method for Item Type
    const int getType() const;
};

#endif // ITEM_H
