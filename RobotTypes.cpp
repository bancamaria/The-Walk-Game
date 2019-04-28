#include "RobotTypes.h"

///////Robot Abstract Class

Robot::Robot(int AssignedType, std::pair<int, int> AssignedPosition, std::pair<int, int> AssignedViewDistance): Type(AssignedType), Position(AssignedPosition), ViewDistance(AssignedViewDistance) {}
Robot::~Robot() {}
const int Robot::getType() const { return Type; }
const std::pair<int, int>& Robot::getPosition() const { return Position; }
const std::pair<int, int>& Robot::getViewDistance() const { return ViewDistance; }

//////Type1Robot Class

Type1Robot::Type1Robot(std::pair<int, int> AssignedPosition, std::pair<int, int> AssignedViewDistance): Robot(1, AssignedPosition, AssignedViewDistance) {}
Type1Robot::~Type1Robot() {}
void Type1Robot::Advance(std::pair<int, int> AdvancePosition) {
    Position = AdvancePosition;
}

//////Type2Robot Class

Type2Robot::Type2Robot(std::pair<int, int> AssignedPosition, std::pair<int, int> AssignedViewDistance): Robot(2, AssignedPosition, AssignedViewDistance) {}
Type2Robot::~Type2Robot() {}
void Type2Robot::Advance(std::pair<int, int> AdvancePosition) {
    Position = AdvancePosition;
}

//////Type31Robot Class

Type3Robot::Type3Robot(std::pair<int, int> AssignedPosition, std::pair<int, int> AssignedViewDistance): Robot(3, AssignedPosition, AssignedViewDistance) {}
Type3Robot::~Type3Robot() {}
void Type3Robot::Advance(std::pair<int, int> AdvancePosition) {
    Position = AdvancePosition;
}
