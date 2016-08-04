
#include <string.h>
#include "gameSpace.hpp"
#include "gameObjects.hpp"
#include "lib_flip_display.hpp"

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

    {"Enchanted Forest", gameSpaceLocationForest,
    {gameSpaceLocationTrail1, gameSpaceLocationTrail2, gameSpaceLocationTrail3, gameSpaceLocationInvalid},
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

    {"Nice smooth trail", gameSpaceLocationTrail1,
    {gameSpaceLocationForest, gameSpaceLocationRiver, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Forest Trail 2
    //
    // Connects to:
    //         Forest
    //         River
    //
    // Contains Objects:
    //         None
    //

    {"Overgrown trail with old stones", gameSpaceLocationTrail2,
    {gameSpaceLocationForest, gameSpaceLocationCabin, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Forest Trail 3
    //
    // Connects to:
    //         Forest
    //         Cave
    //         Trail 4
    //
    // Contains Objects:
    //         None
    //

    {"Trail with over hanging trees", gameSpaceLocationTrail3,
    {gameSpaceLocationForest, gameSpaceLocationTrail4, gameSpaceLocationCave, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Forest Trail 4
    //
    // Connects to:
    //         Trail 1
    //         Trail 3    
    //
    // Contains Objects:
    //         None
    //

    {"Trail with over small clearing", gameSpaceLocationTrail4,
    {gameSpaceLocationTrail3, gameSpaceLocationTrail1, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : River
    //
    // Connects to:
    //         Pond
    //         Trail 1
    //
    // Contains Objects:
    //         None
    //

    {"A river", gameSpaceLocationRiver,
    {gameSpaceLocationTrail1, gameSpaceLocationPond, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Pond
    //
    // Connects to:
    //         Cabin
    //         River
    //
    // Contains Objects:
    //         None
    //

    {"A pond with some fish", gameSpaceLocationPond,
    {gameSpaceLocationRiver, gameSpaceLocationCabin, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cabin
    //
    // Connects to:
    //         Trail 2
    //         Pond
    //         Cabin Basement
    //
    // Contains Objects:
    //         None
    //

    {"An abandonded log cabin.", gameSpaceLocationCabin,
    {gameSpaceLocationTrail2, gameSpaceLocationPond, gameSpaceLocationCabinBasement, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cabin Basement
    //
    // Connects to:
    //         Cabin
    //
    // Contains Objects:
    //         None
    //

    {"Secret basement in cabin.", gameSpaceLocationCabinBasement,
    {gameSpaceLocationCabin, gameSpaceLocationInvalid, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cave
    //
    // Connects to:
    //         Trail 3
    //         Cave Room
    //
    // Contains Objects:
    //         None
    //

    {"A dark cave.", gameSpaceLocationCave,
    {gameSpaceLocationTrail3, gameSpaceLocationCaveRoom, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cave Room
    //
    // Connects to:
    //         Cave
    //
    // Contains Objects:
    //         None
    //

    {"A room in the cave with a sky light.", gameSpaceLocationCaveRoom,
    {gameSpaceLocationCave, gameSpaceLocationInvalid, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Invalid - This is used to signal the  end of the gameSpaceDescription array
    //
    // Connects to:
    //         None
    //
    // Contains Objects:
    //         None
    //

    {"EndTerminator", gameSpaceLocationInvalid,
    {gameSpaceLocationInvalid, gameSpaceLocationInvalid, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},
};

gameSpace::gameSpace(const gameSpaceDescription * spaceDesc)
{
    DebugConsole::debug_print (1, false, COLOR_WHITE, "Creating gameSpace (%d) %s\n", spaceDesc->thisSpace, spaceDesc->spaceName.c_str());
    spaceDescription.spaceName = spaceDesc->spaceName;
    spaceDescription.thisSpace = spaceDesc->thisSpace;
    memcpy (spaceDescription.connectedSpaces, spaceDesc->connectedSpaces, sizeof (spaceDescription.connectedSpaces));
    memcpy (spaceDescription.objectsInSpace, spaceDesc->objectsInSpace, sizeof (spaceDescription.objectsInSpace));

    // Create a dynamic array of the objectsInSpace
    int objectIndex=0;
    for (objectIndex = 0; objectIndex < NUM_OBJECTS_IN_SPACE; objectIndex++)
    {
        switch (spaceDescription.objectsInSpace[objectIndex])
        {
            case objectTypeKnife:
            {
                objects.push_back(new gameObjectKnife);
            }
            case objectTypeChest:
            {
                objects.push_back(new gameObjectChest);
            }
            case objectTypeRing:
            {
                objects.push_back(new gameObjectRing);
            }
            case objectTypeCrystalOrb:
            {
                objects.push_back(new gameObjectCrystalOrb);
            }
            case objectTypeFlower:
            {
                objects.push_back(new gameObjectFlower);
            }
            case objectTypeTeaPot:
            {
                objects.push_back(new gameObjectTeaPot);
            }
            case objectTypeElixer:
            {
                objects.push_back(new gameObjectElixer);
            }
            case objectTypeStarFish:
            {
                objects.push_back(new gameObjectStarFish);
            }
            case objectTypeSquirtle:
            {
                objects.push_back(new gameObjectSquirtle);
            }
            case objectTypeStarmie:
            {
                objects.push_back(new gameObjectStarmie);
            }
            case objectTypeGem:
            {
                objects.push_back(new gameObjectGem);
            }
            case objectTypeGemKey:
            {
                objects.push_back(new gameObjectGemKey);
            }
            case objectTypeOrbHole:
            {
                objects.push_back(new gameObjectOrbHole);
            }
            case objectTypeStick:
            {
                objects.push_back(new gameObjectStick);
            }
            case objectTypeLantern:
            {
                objects.push_back(new gameObjectLantern);
            }
            case objectTypeMagicDoor:
            {
                objects.push_back(new gameObjectMagicDoor);
            }
            break;
            default:
            {
                // Ignore invalid object.
            }
            break;
        }
    }
    
}

bool gameSpace::CanMoveTo(gamePlayer * player)
{
    return true;
}

const gameSpaceDescription gameSpace::GetSpaceDescription()
{
    return spaceDescription;
}