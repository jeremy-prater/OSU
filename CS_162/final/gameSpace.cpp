
#include "gameSpace.hpp"

struct gameSpaceDescription gameSpace::gameSpaceDescriptions [] = {

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Enchanted Forest
    //
    // Connects to:
    //         Trail 1
    //         Trail 2
    //         Trail 3
    //
    // Contains Objects:
    //         None
    //

    {"Enchanted Forest", gameSpaceForest,
    {gameSpaceTrail1, gameSpaceTrail2, gameSpaceTrail3, gameSpaceInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Forest Trail 1
    //
    // Connects to:
    //         Forest
    //         River
    //
    // Contains Objects:
    //         None
    //

    {"Nice smooth trail", gameSpaceTrail1,
    {gameSpaceForest, gameSpaceRiver, gameSpaceInvalid, gameSpaceInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},
}
