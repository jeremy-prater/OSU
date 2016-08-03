#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

#include "gameObject.hpp"

class gameObjectKnife : public gameObject
{
public:
    gameObjectKnife() : gameObject() { }
    ~gameObjectKnife() { }

    objectTypes GetObjectType();
};

class gameObjectChest : public gameObject
{
public:
    gameObjectChest() : gameObject() { }
    ~gameObjectChest() { }

    objectTypes GetObjectType();
};

class gameObjectRing : public gameObject
{
public:
    gameObjectRing() : gameObject() { }
    ~gameObjectRing() { }

    objectTypes GetObjectType();
};

class gameObjectCrystalOrb : public gameObject
{
public:
    gameObjectCrystalOrb() : gameObject() { }
    ~gameObjectCrystalOrb() { }

    objectTypes GetObjectType();
};

class gameObjectFlower : public gameObject
{
public:
    gameObjectFlower() : gameObject() { }
    ~gameObjectFlower() { }

    objectTypes GetObjectType();
};

class gameObjectTeaPot : public gameObject
{
public:
    gameObjectTeaPot() : gameObject() { }
    ~gameObjectTeaPot() { }

    objectTypes GetObjectType();
};

class gameObjectElixer : public gameObject
{
public:
    gameObjectElixer() : gameObject() { }
    ~gameObjectElixer() { }

    objectTypes GetObjectType();
};

class gameObjectStarFish : public gameObject
{
public:
    gameObjectStarFish() : gameObject() { }
    ~gameObjectStarFish() { }

    objectTypes GetObjectType();
};

class gameObjectSquirtle : public gameObject
{
public:
    gameObjectSquirtle() : gameObject() { }
    ~gameObjectSquirtle() { }

    objectTypes GetObjectType();
};

class gameObjectStarmie : public gameObject
{
public:
    gameObjectStarmie() : gameObject() { }
    ~gameObjectStarmie() { }

    objectTypes GetObjectType();
};

class gameObjectGem : public gameObject
{
public:
    gameObjectGem() : gameObject() { }
    ~gameObjectGem() { }

    objectTypes GetObjectType();
};

class gameObjectGemKey : public gameObject
{
public:
    gameObjectGemKey() : gameObject() { }
    ~gameObjectGemKey() { }

    objectTypes GetObjectType();
};

class gameObjectOrbHole : public gameObject
{
public:
    gameObjectOrbHole() : gameObject() { }
    ~gameObjectOrbHole() { }

    objectTypes GetObjectType();
};

class gameObjectStick : public gameObject
{
public:
    gameObjectStick() : gameObject() { }
    ~gameObjectStick() { }

    objectTypes GetObjectType();
};

class gameObjectLantern : public gameObject
{
public:
    gameObjectLantern() : gameObject() { }
    ~gameObjectLantern() { }

    objectTypes GetObjectType();
};

class gameObjectMagicDoor : public gameObject
{
public:
    gameObjectMagicDoor() : gameObject() { }
    ~gameObjectMagicDoor() { }

    objectTypes GetObjectType();
};

#endif // GAME_OBJECTS_HPP