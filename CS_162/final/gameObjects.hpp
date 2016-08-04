#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

#include "gameObject.hpp"

class gameObjectKnife : public gameObject
{
public:
    gameObjectKnife(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectKnife() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTake();
};

class gameObjectChest : public gameObject
{
public:
    gameObjectChest(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectChest() { }

    objectTypes GetObjectType();
    std::string GetName();
};

class gameObjectLock : public gameObject
{
public:
    gameObjectLock(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectLock() { }

    objectTypes GetObjectType();
    std::string GetName();
};

class gameObjectCrystalOrb : public gameObject
{
public:
    gameObjectCrystalOrb(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectCrystalOrb() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTake();
};

class gameObjectFlower : public gameObject
{
public:
    gameObjectFlower(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectFlower() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTake();
};

class gameObjectTeaPot : public gameObject
{
public:
    gameObjectTeaPot(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectTeaPot() { }

    objectTypes GetObjectType();
    std::string GetName();
};

class gameObjectElixer : public gameObject
{
public:
    gameObjectElixer(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectElixer() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTake();
};

class gameObjectStarFish : public gameObject
{
public:
    gameObjectStarFish(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectStarFish() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTalk();
    std::string talk();
};

class gameObjectSquirtle : public gameObject
{
public:
    gameObjectSquirtle(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectSquirtle() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTalk();
    std::string talk();
};

class gameObjectStarmie : public gameObject
{
public:
    gameObjectStarmie(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectStarmie() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTalk();
    std::string talk();
};

class gameObjectGem : public gameObject
{
public:
    gameObjectGem(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectGem() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTake();    
};

class gameObjectGemKey : public gameObject
{
public:
    gameObjectGemKey(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectGemKey() { }

    objectTypes GetObjectType();
    std::string GetName();
};

class gameObjectOrbHole : public gameObject
{
public:
    gameObjectOrbHole(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectOrbHole() { }

    objectTypes GetObjectType();
    std::string GetName();
};

class gameObjectStick : public gameObject
{
public:
    gameObjectStick(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectStick() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTake();
};

class gameObjectLantern : public gameObject
{
public:
    gameObjectLantern(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectLantern() { }

    objectTypes GetObjectType();
    std::string GetName();
    bool canTake();
};

class gameObjectMagicDoor : public gameObject
{
public:
    gameObjectMagicDoor(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectMagicDoor() { }

    objectTypes GetObjectType();
    std::string GetName();
};

#endif // GAME_OBJECTS_HPP