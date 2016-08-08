/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameObject.cpp
*********************************************************************/

#include "gameObject.hpp"
#include "gameObjects.hpp"
#include "lib_flip_display.hpp"

gameObject::gameObject(gameSpaceController * controller)
{
    Controller = controller;
}

gameObject::~gameObject()
{

}

bool gameObject::canUseItemOnTarget(gameObject * target)
{
    return false;
}

void gameObject::useItem(gameObject * target)
{
    return;
}

bool gameObject::canTake()
{
    return false;
}

bool gameObject::canTalk()
{
    return false;
}

std::string gameObject::talk()
{
    return "ERROR: Object can not talk!";
}

bool gameObject::canRead()
{
    return false;
}

std::string gameObject::read()
{
    return "ERROR: Object can not be read!";
}

gameObject * gameObject::CreateObjectFromType (objectTypes type, gameSpaceController * Controller)
{
    gameObject * newObject = __null;
    switch (type)
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
    return newObject;
}