#ifndef GAME_ITEM_HPP
#define GAME_ITEM_HPP

#include <string>
#include "gameObject.hpp"

enum objectTypes
{
    objectTypeInvalid = -1,
    objectTypeKnife,

    objectTypeChest,
    objectTypeRing,
    objectTypeCrystalOrb,

    objectTypeFlower,
    objectTypeTeaPot,
    objectTypeElixer,

    objectTypeStarFish,
    objectTypeSquirtle,
    objectTypeStarmie,
    objectTypeGem,
    objectTypeGemKey,

    objectTypeOrbHole,

    objectTypeStick,
    objectTypeLantern,

    objectTypeMagicDoor,
    objectType_NumObjects
};

class gameObject
{
protected:
    unsigned int objectID;
    objectTypes objectType;

public:
    gameObject(unsigned int id, objectTypes type);
    ~gameObject();

    virtual unsigned int GetObjectID();
    virtual unsigned int GetObjectType();

    virtual bool canUseItemOnTarget (gameObject * target) = 0;
    virtual int useItem(gameObject * target) = 0;

    virtual bool canTalk() = 0;
    virtual string talk() = 0;
    virtual bool CanRead() = 0;
    virtual string Read() = 0;
};


#endif // GAME_ITEM_HPP