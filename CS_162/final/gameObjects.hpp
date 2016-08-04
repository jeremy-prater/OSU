#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

#include "gameObject.hpp"

class gameObjectKnife : public gameObject
{
public:
    gameObjectKnife() : gameObject() { }
    ~gameObjectKnife() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectChest : public gameObject
{
public:
    gameObjectChest() : gameObject() { }
    ~gameObjectChest() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectRing : public gameObject
{
public:
    gameObjectRing() : gameObject() { }
    ~gameObjectRing() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectCrystalOrb : public gameObject
{
public:
    gameObjectCrystalOrb() : gameObject() { }
    ~gameObjectCrystalOrb() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectFlower : public gameObject
{
public:
    gameObjectFlower() : gameObject() { }
    ~gameObjectFlower() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectTeaPot : public gameObject
{
public:
    gameObjectTeaPot() : gameObject() { }
    ~gameObjectTeaPot() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectElixer : public gameObject
{
public:
    gameObjectElixer() : gameObject() { }
    ~gameObjectElixer() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectStarFish : public gameObject
{
public:
    gameObjectStarFish() : gameObject() { }
    ~gameObjectStarFish() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectSquirtle : public gameObject
{
public:
    gameObjectSquirtle() : gameObject() { }
    ~gameObjectSquirtle() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectStarmie : public gameObject
{
public:
    gameObjectStarmie() : gameObject() { }
    ~gameObjectStarmie() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectGem : public gameObject
{
public:
    gameObjectGem() : gameObject() { }
    ~gameObjectGem() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectGemKey : public gameObject
{
public:
    gameObjectGemKey() : gameObject() { }
    ~gameObjectGemKey() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectOrbHole : public gameObject
{
public:
    gameObjectOrbHole() : gameObject() { }
    ~gameObjectOrbHole() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectStick : public gameObject
{
public:
    gameObjectStick() : gameObject() { }
    ~gameObjectStick() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectLantern : public gameObject
{
public:
    gameObjectLantern() : gameObject() { }
    ~gameObjectLantern() { }

    objectTypes GetObjectType();
     std::string GetName();
};

class gameObjectMagicDoor : public gameObject
{
public:
    gameObjectMagicDoor() : gameObject() { }
    ~gameObjectMagicDoor() { }

    objectTypes GetObjectType();
     std::string GetName();
};

#endif // GAME_OBJECTS_HPP