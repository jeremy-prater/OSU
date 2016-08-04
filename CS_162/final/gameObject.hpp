#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

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
    objectTypes objectType;

public:
    gameObject();
    ~gameObject();

    virtual objectTypes GetObjectType() = 0;
    virtual std::string GetName() = 0;

    virtual bool canUseItemOnTarget (gameObject * target);
    virtual int useItem(gameObject * target);

    virtual bool canTake();
    virtual bool canTalk();
    virtual std::string talk();
    virtual bool canRead();
    virtual std::string read();
};


#endif // GAME_OBJECT_HPP