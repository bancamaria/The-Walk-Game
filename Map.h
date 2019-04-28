#ifndef MAP_H
#define MAP_H
#include <iostream>
#include "RobotTypes.h"
#include "Tile.h"
#include <vector>

class Map{
    std::pair<int, int> Size;                           // Map Size
    std::pair<int, int> DefaultViewDistance;            // Map View Distance
    std::pair<int, int> Start;                          // Map Start Position
    std::pair<int, int> Finish;                         // Map Finish Position => Randomly Decided within Instantiation
    std::vector<std::pair<int,int> > PossiblePath;      // Possible Path for the Robot to Follow => Calculated within Object-Instantiation
    Tile** Tiles;                                       // Tile-Matrix to store information about each tile on the Map
    char** Configuration;                               // Configuration Matrix: used for displaying current paths/ tiles inside Display..() methods
    Robot* Player;                                      // Current Player (Robot)
    bool Completed;                                     // Completed Tick/Flag
    int Round;                                          // Current Round
public:
    // Constructor with Assigned Size, View Distance, Start Position and Robot Type
    Map(std::pair<int, int> AssignedSize = {1,1}, std::pair<int, int> AssignedViewDistance = {1, 1}, std::pair<int, int> AssignedStart = {0, 0}, int RobotType = 1);
    ~Map();                                                                 // Destructor: Destroys the dynamic allocated containers (Tiles, Configuration) and the current Player
    void Draw()const;                                                       // Method that computed the current Configuration Matrix
    void Display(std::ostream& OutBuffer = std::cout)const;                 // Method that displays the current Configuration Matrix
    void DisplayPossiblePath(std::ostream& OutBuffer = std::cout)const;     // Method that displays the Possible Path computed during Object-Instantiation
    void PlayRound();                                                       // Method that plays the current round and then advances the game
    void GetPossiblePath();                                                 // Method that computes the Possible Path
    bool isCompleted()const;                                                // Method that signals when the game was completed
};

#endif // MAP_H
