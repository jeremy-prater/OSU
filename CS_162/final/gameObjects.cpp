#include "gameObjects.hpp"

objectTypes gameObjectKnife::GetObjectType() { return objectTypeKnife; }
objectTypes gameObjectChest::GetObjectType() { return objectTypeChest; }
objectTypes gameObjectLock::GetObjectType() { return objectTypeLock; }
objectTypes gameObjectCrystalOrb::GetObjectType() { return objectTypeCrystalOrb; }
objectTypes gameObjectFlower::GetObjectType() { return objectTypeFlower; }
objectTypes gameObjectTeaPot::GetObjectType() { return objectTypeTeaPot; }
objectTypes gameObjectElixer::GetObjectType() { return objectTypeElixer; }
objectTypes gameObjectStarFish::GetObjectType() { return objectTypeStarFish; }
objectTypes gameObjectSquirtle::GetObjectType() { return objectTypeSquirtle; }
objectTypes gameObjectStarmie::GetObjectType() { return objectTypeStarmie; }
objectTypes gameObjectGem::GetObjectType() { return objectTypeGem; }
objectTypes gameObjectGemKey::GetObjectType() { return objectTypeGemKey; }
objectTypes gameObjectOrbHole::GetObjectType() { return objectTypeOrbHole; }
objectTypes gameObjectStick::GetObjectType() { return objectTypeStick; }
objectTypes gameObjectLantern::GetObjectType() { return objectTypeLantern; }
objectTypes gameObjectMagicDoor::GetObjectType() { return objectTypeMagicDoor; }

std::string gameObjectKnife::GetName() { return "Knife"; }
std::string gameObjectChest::GetName() { return "Chest"; }
std::string gameObjectLock::GetName() { return "Lock"; }
std::string gameObjectCrystalOrb::GetName() { return "CrystalOrb"; }
std::string gameObjectFlower::GetName() { return "Flower"; }
std::string gameObjectTeaPot::GetName() { return "TeaPot"; }
std::string gameObjectElixer::GetName() { return "Elixer"; }
std::string gameObjectStarFish::GetName() { return "StarFish"; }
std::string gameObjectSquirtle::GetName() { return "Squirtle"; }
std::string gameObjectStarmie::GetName() { return "Starmie"; }
std::string gameObjectGem::GetName() { return "Gem"; }
std::string gameObjectGemKey::GetName() { return "Gem Key"; }
std::string gameObjectOrbHole::GetName() { return "OrbHole"; }
std::string gameObjectStick::GetName() { return "Stick"; }
std::string gameObjectLantern::GetName() { return "Lantern"; }
std::string gameObjectMagicDoor::GetName() { return "MagicDoor"; }

bool gameObjectStick::canTake() { return true; }
bool gameObjectFlower::canTake() { return true; }
bool gameObjectCrystalOrb::canTake() { return true; }
bool gameObjectGem::canTake() { return true; }
bool gameObjectKnife::canTake() { return true; }
bool gameObjectElixer::canTake() { return true; }
bool gameObjectLantern::canTake() { return true; }


bool gameObjectStarFish::canTalk () { return true; }
std::string gameObjectStarFish::talk()
{
    return "Not yet";
}

bool gameObjectStarmie::canTalk () { return true; }
std::string gameObjectStarmie::talk()
{
    return "Not yet";
}

bool gameObjectSquirtle::canTalk () { return true; }
std::string gameObjectSquirtle::talk()
{
    static bool firstTime = true;
    if (firstTime == true)
    {
        return "\t\tHello traveler...\n\n\tI have a gift for you, but first you need to help my friend. There is a pond a short walk from here.\nMy friend that lives in it is sick and needs the brewed elixer from flowers that grow in this area to heal.\n\nPlease help him and I will reward you!\n\n";
        firstTime = false;
    }
    else
    {
        return "\tHave you found my friend?\n\nIt makes me sad that he is still stick.\nThe flowers that grow in this area will cure him if they are brewed.";
    }
}