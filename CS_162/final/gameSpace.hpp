#ifndef GAME_SPACE_HPP
#define GAME_SPACE_HPP

#include <string>
#include <vector>
#include "gameObject.hpp"

#define NUM_CONNECTED_SPACES 4
#define NUM_OBJECTS_IN_SPACE 5

class gameSpace;

enum gameSpaceLocation
{
    gameSpaceLocationInvalid = -1,
    gameSpaceLocationForest,
    gameSpaceLocationTrail1,
    gameSpaceLocationRiver,

    gameSpaceLocationTrail2,
    gameSpaceLocationCabin,
    gameSpaceLocationCabinBasement,
    
    gameSpaceLocationTrail3,
    gameSpaceLocationCaveEntrance,
    gameSpaceLocationCaveRoom,

    gameSpaceLocation_NumLocations
};

struct gameSpaceDescription
{
    string spaceName;
    gameSpaceLocation thisSpace;
    gameSpaceLocation connectedSpaces[NUM_CONNECTED_SPACES];
    objectTypes objectsInSpace[NUM_OBJECTS_IN_SPACE];
};

class gameSpace
{
protected:
    gameSpaceDescription spaceDescription;
    std::vector<gameObject> objects;

public:
    static struct gameSpaceDescription gameSpaceDescriptions[];
    gameSpace(const gameSpaceDescription * spaceDesc);
    ~gameItem();

};


#endif // GAME_SPACE_HPP