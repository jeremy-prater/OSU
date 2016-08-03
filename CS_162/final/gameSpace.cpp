
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

gameSpace::gameSpace(const gameSpaceDescription * spaceDesc)
{
    spaceDescription.spaceName = spaceDesc->spaceName;
    spaceDescription.thisSpace = spaceDesc->thisSpace;
    memcpy (spaceDescription.connectedSpaces, spaceDesc->connectedSpaces, sizeof (spaceDescription.connectedSpaces));
    memcpy (spaceDescription.objectsInSpace, spaceDesc->objectsInSpace, sizeof (spaceDescription.objectsInSpace));

    // Create a dynamic array of the objectsInSpace
    int objectIndex=0;
    for (objecIndex = 0; objectIndex < NUM_OBJECTS_IN_SPACE; objectsInSpace++)
    {
        switch (spaceDescription.objectsInSpace[objectIndex].thisSpace):
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
                objects.push_back(new gameObjectStarFist);
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

        }
    }
    
}

