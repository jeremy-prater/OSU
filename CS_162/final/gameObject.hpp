/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameObject.hpp
*********************************************************************/

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <string>
#include "classDecl.hpp"
#include "gameObject.hpp"

enum objectTypes
{
    objectTypeInvalid = -1,
    objectTypeKnife,

    objectTypeChest,
    objectTypeLock,
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
    gameSpaceController * Controller;

public:
    static gameObject * CreateObjectFromType (objectTypes type, gameSpaceController * controller);
    
    gameObject(gameSpaceController * controller);
    ~gameObject();

    virtual objectTypes GetObjectType() = 0;
    virtual std::string GetName() = 0;
    virtual std::string GetText() = 0;

    virtual bool canUseItemOnTarget (gameObject * target);
    virtual void useItem(gameObject * target);

    virtual bool canTake();
    virtual bool canTalk();
    virtual std::string talk();
    virtual bool canRead();
    virtual std::string read();
};


#endif // GAME_OBJECT_HPP