#ifndef ROBOTTYPES_H
#define ROBOTTYPES_H
#include <iostream>

// Base Robot Class for future Robot Types to be Derived from -> Abstract
class Robot {
    protected:
        const int Type;                     // The Type of the Robot
        std::pair<int, int> Position;       // The Position of the Robot
        std::pair<int, int> ViewDistance;   // The View Distance of the Robot
    public:
        // Constructor with Assigned Type, Position and View Distance Parameters
        Robot(int AssignedType = 0, std::pair<int, int> AssignedPosition = {0, 0}, std::pair<int, int> AssignedViewDistance = {0, 0});
        virtual ~Robot();                                               // Destructor
        const int getType()const;                                       // Get-method for Robot Type
        const std::pair<int, int>& getPosition() const;                 // Get-method for Robot Position
        const std::pair<int, int>& getViewDistance() const;             // Get-method for Robot View Distance
        virtual void Advance(std::pair<int, int> AdvancePosition) = 0;  // Pure Virtual Advance method -> "selects" the new position to advance towards
};


// Derived Class for Robots of Type 1
class Type1Robot: public Robot{
public:
        // Position and View Distance Parameters => Assigned Type is 1 by Default
        Type1Robot(std::pair<int, int> AssignedPosition = {0, 0}, std::pair<int, int> AssignedViewDistance = {0, 0});
        ~Type1Robot();                                          // Destructor
        void Advance(std::pair<int, int> AdvancePosition);      // Advance method -> "selects" the new position to advance towards
};


// Derived Class for Robots of Type 2
class Type2Robot: public Robot{
public:
        // Position and View Distance Parameters => Assigned Type is 2 by Default
        Type2Robot(std::pair<int, int> AssignedPosition = {0, 0}, std::pair<int, int> AssignedViewDistance = {0, 0});
        ~Type2Robot();                                          // Destructor
        void Advance(std::pair<int, int> AdvancePosition);      // Advance method -> "selects" the new position to advance towards
};


// Derived Class for Robots of Type 3
class Type3Robot: public Robot{
public:
        // Position and View Distance Parameters => Assigned Type is 3 by Default
        Type3Robot(std::pair<int, int> AssignedPosition = {0, 0}, std::pair<int, int> AssignedViewDistance = {0, 0});
        ~Type3Robot();                                          // Destructor
        void Advance(std::pair<int, int> AdvancePosition);      // Advance method -> "selects" the new position to advance towards
};


#endif // ROBOTTYPES_H
