#include "Map.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <map>
#include <set>
#include <queue>

// Convention: first argument of pair will always be Y coordinate (or line), and the second will be the X coordinate (or column)

Map::Map(std::pair<int, int> AssignedSize, std::pair<int, int> AssignedViewDistance, std::pair<int, int> AssignedStart, int RobotType): Size(AssignedSize), DefaultViewDistance(AssignedViewDistance), Start(AssignedStart) {
    // Randomly generating finish position
    std::srand(time(0));
    do {
        Finish = {rand() % Size.first, rand() % Size.second};
    } while(Finish == Start);

    // Allocating tile and configuration matrices from here to row 23
    Tiles = new Tile*[Size.first];
    Configuration = new char*[Size.first];
    for(int Row = 0; Row < Size.first; ++Row) {
        Tiles[Row] = new Tile[Size.second];
        Configuration[Row] = new char[Size.second];
    }

    // Computing the number of traps to be randomly laid within the map
    int TrapNumber = ceil((Size.first * Size.second) / 10.0);
    for(int i = 0; i < TrapNumber; ++i) {
        Trap* CurrentTrap = new Trap();
        int TrapLine, TrapColumn;
        do {
            TrapLine = rand() % Size.first;
            TrapColumn = rand() % Size.second;
        }
        while(Tiles[TrapLine][TrapColumn].getTrap() != 0 || std::make_pair<int, int>(TrapLine, TrapColumn) == Start || std::make_pair<int, int>(TrapLine, TrapColumn) == Finish); ///Checking whether a Trap would overlap the Start/Finish Positions
        Tiles[TrapLine][TrapColumn].setTrap(CurrentTrap);
    }

    // Computing the number of items to be randomly laid within the map
    int ItemNumber = ceil((Size.first * Size.second) / 20.0);
    for(int i = 0; i < ItemNumber; ++i) {
        // Randomly deciding the item type
        int ItemType = rand() % 3 + 1;
        Item* CurrentItem = new Item(ItemType);
        int ItemLine, ItemColumn;
        do {
            ItemLine = rand() % Size.first;
            ItemColumn = rand() % Size.second;
        }
        while(Tiles[ItemLine][ItemColumn].getItem() != 0 || Tiles[ItemLine][ItemColumn].getTrap() != 0 || std::make_pair<int, int>(ItemLine, ItemColumn) == Start || std::make_pair<int, int>(ItemLine, ItemColumn) == Finish); ///Checking whether a Trap would overlap a Trap or the Start/Finish Positions
        Tiles[ItemLine][ItemColumn].setItem(CurrentItem);
    }

    // Allocating the player depending on the RobotType parameter
    switch(RobotType){
        case 1:{
            Player = new Type1Robot(Start, DefaultViewDistance);
            break;
        }
        case 2:{
            Player = new Type2Robot(Start, DefaultViewDistance);
            break;
        }
        case 3:{
            Player = new Type2Robot(Start, DefaultViewDistance);
            break;
        }
        default:{
            Completed = true;
            return;
        }
    }

    Completed = false;
    GetPossiblePath();   // Computing the Possible Path
    Round = 0;           // Resetting the rounds
}


// Drawing the Map
void Map::Draw() const {
    for(int Line = 0; Line < Size.first; ++Line) {
        for(int Column = 0; Column < Size.second; ++Column) {
            // R -> Robot | T -> Trap | 0...3 -> Item Type | S -> Start Position | F -> Finish Position | Blank -> Open Space
            if(Line == Player->getPosition().first && Column == Player->getPosition().second)
                Configuration[Line][Column] = 'R';
            else {
                if(Tiles[Line][Column].getTrap() != 0)
                    Configuration[Line][Column] = 'T';
                else {
                    if(Tiles[Line][Column].getItem() != 0)
                        Configuration[Line][Column] = 48 + Tiles[Line][Column].getItem()->getType();
                    else {
                        if(Line == Start.first && Column == Start.second)
                            Configuration[Line][Column] = 'S';
                        else {
                            if(Line == Finish.first && Column == Finish.second)
                                Configuration[Line][Column] = 'F';
                            else
                                Configuration[Line][Column] = ' ';
                        }
                    }
                }
            }
        }
    }

    for(int Step = 1; Step < Round; ++Step)
        // Overwriting the positions which were previously traveled by the Player
        if(Tiles[PossiblePath[Step].first][PossiblePath[Step].second].getItem() == 0)
            Configuration[PossiblePath[Step].first][PossiblePath[Step].second] = '*';
}


// Displays the current configuration matrix with a border of lines
void Map::Display(std::ostream& OutBuffer) const {
    OutBuffer << '\n';
    for(int Column = 0; Column < 2 * (Size.second + 1); ++Column)
        OutBuffer << '-';
    OutBuffer << '\n';
    for(int Line = 0; Line < Size.first; ++Line) {
        OutBuffer << '|';
        for(int Column = 0; Column < Size.second; ++Column)
            OutBuffer << Configuration[Line][Column] << ' ';
        OutBuffer << '|' << '\n';
    }
    for(int Column = 0; Column < 2 * (Size.second + 1); ++Column)
        OutBuffer << '-';
    OutBuffer << '\n';
    if(Completed == true)
        DisplayPossiblePath();
}


// Displays the possible path as (X, Y)->(X', Y')
void Map::DisplayPossiblePath(std::ostream& OutBuffer) const {
    OutBuffer << '\n';
    OutBuffer << "Path: ";
    for(int Position = 0; Position < PossiblePath.size(); ++Position) {
        OutBuffer << "(" << PossiblePath[Position].first << ", " << PossiblePath[Position].second << ')';
        if(Position + 1 != PossiblePath.size())
            OutBuffer << "->";
    }
    OutBuffer << '\n';
}


// Destructor
Map::~Map() {
    for(int Line = 0; Line < Size.first; ++ Line) {
        delete[] Tiles[Line];
        delete[] Configuration[Line];
    }
    delete[] Tiles;
    delete[] Configuration;
    delete Player;
}


// Lee's Algorithm for finding the shortest path to finish, if existent
void Map::GetPossiblePath() {
    // Directional Arrays
    short int dX[] = {-1, -1, -1, 1, 1, 1, 0, 0};
    short int dY[] = {0, -1, 1, -1, 1, 0, -1, 1};

    // Queue of Positions
    std::queue<std::pair<int, int> > ToVisit;
    // Visited Positions
    std::map<std::pair<int, int>, bool> Visited;
    // Distance between the position and the start position => used to pick the minimum
    std::map<std::pair<int, int>, int> Distance;
    // Ancestor set for each position, if existent
    std::map<std::pair<int, int>, std::set<std::pair<int, int> > > Ancestors;

    // Queuing Start
    ToVisit.push(Start);
    Visited[Start] = true;
    Distance[Start] = 0;
    std::pair<int, int> CurrentPosition = Start;
    std::pair<int, int> LastPosition = CurrentPosition;
    int CurrentDistance = Distance[CurrentPosition];
    bool ItemUsed = false;
    while(!ToVisit.empty()) {                                                   // While there are still positions to visit
        CurrentPosition = ToVisit.front();                                      // Picks the front position
        if(CurrentPosition == Finish) {                                         // If we landed on the finish position, generate the optimal path
            PossiblePath.insert(PossiblePath.begin(), CurrentPosition);         // Inserts finish
            while(CurrentPosition != Start) {                                   // While there is still position to insert
                std::pair<int, int> OptimalAncestor;                            // Getting the ancestor set of current position
                for(std::set<std::pair<int, int> >::iterator Position = Ancestors[CurrentPosition].begin(); Position != Ancestors[CurrentPosition].end(); ++Position) {
                    if(Position == Ancestors[CurrentPosition].begin())
                        OptimalAncestor = *Position;
                    else {
                        if(Distance[OptimalAncestor] > Distance[*Position])     // Selecting the optimal ancestor => minimum distance from Start
                            OptimalAncestor = *Position;
                    }
                }
                PossiblePath.insert(PossiblePath.begin(), OptimalAncestor);     // Inserting optimal ancestor
                CurrentPosition = OptimalAncestor;                              // Updating current position
            }
            break;
        }

        // Popping the front position
        ToVisit.pop();
        ItemUsed = false;
        // Deciding whether the Player can use an Item at this Position
        if(Tiles[CurrentPosition.first][CurrentPosition.second].getItem())
            if(Tiles[CurrentPosition.first][CurrentPosition.second].getItem()->getType() == Player->getType())
                ItemUsed = true;
        // Saving position before attempting to advance
        LastPosition = CurrentPosition;
        // Advancing in 8 directions according to the arrays
        for(int Direction = 0; Direction < 8; ++Direction) {
            CurrentPosition = LastPosition;
            CurrentPosition.first += dX[Direction];
            CurrentPosition.second += dY[Direction];

             // If new position is within the map borders
            if(CurrentPosition.first >= 0 && CurrentPosition.first < Size.first && CurrentPosition.second >= 0 && CurrentPosition.second < Size.second) {
                // If new position hasn't been visited previously
                if(Visited[CurrentPosition] == false) {
                    // If the new position doesn't contain a Trap
                    if(Tiles[CurrentPosition.first][CurrentPosition.second].getTrap() == 0) {
                        // Marking the new position as visitable
                        ToVisit.push(CurrentPosition);
                        // Marking the new position as Visited prior to reject further attempts before reaching this position
                        Visited[CurrentPosition] = true;
                        // Deciding the distance depending on Item usage
                        if(!ItemUsed)
                            Distance[CurrentPosition] = CurrentDistance + 1;
                        else
                            Distance[CurrentPosition] = CurrentDistance;
                            // Adding the last position as an Ancestor for the new position
                            Ancestors[CurrentPosition].insert(LastPosition);
                    }
                }
            }
        }
    }
}

bool Map::isCompleted() const { return Completed; }

void Map::PlayRound() { // Advances the Player within the Possible Path
    ++Round;
    Player->Advance(PossiblePath[Round]);
    std::pair<int, int> PlayerPosition = Player->getPosition();
    if(Tiles[PlayerPosition.first][PlayerPosition.second].getItem()) // If the Player uses an Item, clears the corresponding tile
        if(Tiles[PlayerPosition.first][PlayerPosition.second].getItem()->getType() == Player->getType())
            Tiles[PlayerPosition.first][PlayerPosition.second].clearItem();
    if(Player->getPosition() == Finish) // If the Player landed on the Finish Position, signals that the game was completed
        Completed = true;
    Draw();
    Display();
}
