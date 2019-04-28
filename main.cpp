#include <iostream>
#include "Map.h"

int main() {
    int RobotType;
    do {
        std::cout << "Enter the type of the robot: ";
        std::cin >> RobotType;
        if(RobotType > 3)
            std::cout << "Unexistent type!\n";
    }
    while(RobotType > 3);
    Map TestMap(std::make_pair<int, int>(15, 15), std::make_pair<int, int>(4, 4), std::make_pair<int, int>(0, 0), RobotType);
    TestMap.Draw();
    TestMap.Display();
    char Choice;
    do {
        do {
            std::cout << "Do you want to continue? Y/N ";
            std::cin >> Choice;
            if(Choice != 'Y' && Choice != 'N')
                std::cout << "Invalid choice!\n";
        }
        while(Choice != 'Y' && Choice != 'N');
        if(Choice == 'N')
            break;
        TestMap.PlayRound();
    }
    while(TestMap.isCompleted() == false);
    return 0;
}
