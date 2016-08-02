#ifndef GAME_SPACE_HPP
#define GAME_SPACE_HPP

#include <string>
#include <vector>
#include "gameObject.hpp"

class gameSpace;

enum gameSpaceLocation
{
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
    gameSpaceLocation connectedSpaces[4];
    std::vector<gameObject> objects;
};

class gameSpace
{
protected:
    gameSpaceDescription spaceDescription;


public:
    gameSpace(const gameSpaceDescription * spaceDesc);
    ~gameItem();

};


#endif // GAME_SPACE_HPP