
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
    //         Cabin
    //
    // Contains Objects:
    //         Stick
    //

    {"Overgrown trail with old stones", gameSpaceLocationTrail2,
    {gameSpaceLocationForest, gameSpaceLocationCabin, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeStick, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

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
    //         Flowers
    //

    {"Trail with over small clearing", gameSpaceLocationTrail4,
    {gameSpaceLocationTrail3, gameSpaceLocationTrail1, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeFlower, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : River
    //
    // Connects to:
    //         Pond
    //         Trail 1
    //
    // Contains Objects:
    //         Starfish
    //

    {"A river", gameSpaceLocationRiver,
    {gameSpaceLocationTrail1, gameSpaceLocationPond, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeStarFish, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Pond
    //
    // Connects to:
    //         Cabin
    //         River
    //
    // Contains Objects:
    //         Squirtle
    //

    {"A pond with some fish", gameSpaceLocationPond,
    {gameSpaceLocationRiver, gameSpaceLocationCabin, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeSquirtle, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

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
    //         Teapot, Lock
    //

    {"An abandonded log cabin.", gameSpaceLocationCabin,
    {gameSpaceLocationTrail2, gameSpaceLocationPond, gameSpaceLocationCabinBasement, gameSpaceLocationInvalid},
    {objectTypeTeaPot, objectTypeLock, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cabin Basement
    //
    // Connects to:
    //         Cabin
    //
    // Contains Objects:
    //         Lantern, Chest
    //

    {"Secret basement in cabin.", gameSpaceLocationCabinBasement,
    {gameSpaceLocationCabin, gameSpaceLocationInvalid, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeLantern, objectTypeChest, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cave
    //
    // Connects to:
    //         Trail 3
    //         Cave Room
    //
    // Contains Objects:
    //         Magic Door, Orb holder
    //

    {"A dark cave.", gameSpaceLocationCave,
    {gameSpaceLocationTrail3, gameSpaceLocationCaveRoom, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeOrbHole, objectTypeMagicDoor, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

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

gameSpace::gameSpace(const gameSpaceDescription * spaceDesc, gameSpaceController * controller)
{
    DebugConsole::debug_print (1, false, COLOR_WHITE, "Creating gameSpace (%d) %s\n", spaceDesc->thisSpace, spaceDesc->spaceName.c_str());
    Controller = controller;
    spaceDescription.spaceName = spaceDesc->spaceName;
    spaceDescription.thisSpace = spaceDesc->thisSpace;
    memcpy (spaceDescription.connectedSpaces, spaceDesc->connectedSpaces, sizeof (spaceDescription.connectedSpaces));
    memcpy (spaceDescription.objectsInSpace, spaceDesc->objectsInSpace, sizeof (spaceDescription.objectsInSpace));

    // Create a dynamic array of the objectsInSpace
    int objectIndex=0;
    for (objectIndex = 0; objectIndex < NUM_OBJECTS_IN_SPACE; objectIndex++)
    {
        gameObject * newObject = __null;
        switch (spaceDescription.objectsInSpace[objectIndex])
        {
            case objectTypeKnife:
            {
                newObject = new gameObjectKnife(Controller);
            }
            break;
            case objectTypeChest:
            {
                newObject = new gameObjectChest(Controller);
            }
            break;
            case objectTypeLock:
            {
                newObject = new gameObjectLock(Controller);
            }
            break;
            case objectTypeCrystalOrb:
            {
                newObject = new gameObjectCrystalOrb(Controller);
            }
            break;
            case objectTypeFlower:
            {
                newObject = new gameObjectFlower(Controller);
            }
            break;
            case objectTypeTeaPot:
            {
                newObject = new gameObjectTeaPot(Controller);
            }
            break;
            case objectTypeElixer:
            {
                newObject = new gameObjectElixer(Controller);
            }
            break;
            case objectTypeStarFish:
            {
                newObject = new gameObjectStarFish(Controller);
            }
            break;
            case objectTypeSquirtle:
            {
                newObject = new gameObjectSquirtle(Controller);
            }
            break;
            case objectTypeStarmie:
            {
                newObject = new gameObjectStarmie(Controller);
            }
            break;
            case objectTypeGem:
            {
                newObject = new gameObjectGem(Controller);
            }
            break;
            case objectTypeGemKey:
            {
                newObject = new gameObjectGemKey(Controller);
            }
            break;
            case objectTypeOrbHole:
            {
                newObject = new gameObjectOrbHole(Controller);
            }
            break;
            case objectTypeStick:
            {
                newObject = new gameObjectStick(Controller);
            }
            break;
            case objectTypeLantern:
            {
                newObject = new gameObjectLantern(Controller);
            }
            break;
            case objectTypeMagicDoor:
            {
                newObject = new gameObjectMagicDoor(Controller);
            }
            break;
            default:
            {
                // Ignore invalid object.
            }
            break;
        }
        if (newObject != __null)
        {
            DebugConsole::debug_print (1, false, COLOR_WHITE, "Creaing Object %s\n", newObject->GetName().c_str());
            objects.push_back (newObject);
        }
    }   
}

gameSpace::~gameSpace()
{
    int currentObjectIndex = 0;
    DebugConsole::debug_print (1, true, COLOR_MAGENTA, "Destroying gameSpace %s and %d objects.\n", spaceDescription.spaceName.c_str(), objects.size());
    while (currentObjectIndex < objects.size())
    {
        DebugConsole::debug_print (1, false, COLOR_MAGENTA, "Destroying Object %s\n", objects[currentObjectIndex]->GetName().c_str());
        delete objects[currentObjectIndex++];
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

std::vector<gameObject *> gameSpace::GetObjects()
{
    return objects;
}

bool gameSpace::ContainsObject (objectTypes type)
{
    int currentObjectIndex = 0;
    while (currentObjectIndex < objects.size())
    {
        if (objects[currentObjectIndex]->GetObjectType() == type)
        {
            return true;
        }
    }
    return false;    
}

void gameSpace::RemoveObject (gameObject * object)
{
    int currentObjectIndex = 0;
    while (currentObjectIndex < objects.size())
    {
        if (objects[currentObjectIndex] == object)
        {
            objects.erase (objects.begin() + currentObjectIndex);
            return;
        }
    }
    
}