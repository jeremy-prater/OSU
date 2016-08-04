#include "gameObjects.hpp"
#include "gameSpaceController.hpp"

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

//bool gameObjectKnife::canItemBeUsed(objectTypes objectType) { return objectTypeKnife; }
//bool gameObjectChest::canItemBeUsed(objectTypes objectType) { return objectTypeChest; }
//bool gameObjectLock::canItemBeUsed(objectTypes objectType) { return objectTypeLock; }
//bool gameObjectCrystalOrb::canItemBeUsed(objectTypes objectType) { return objectTypeCrystalOrb; }
//bool gameObjectFlower::canItemBeUsed(objectTypes objectType) { return objectTypeFlower; }
bool gameObjectTeaPot::canItemBeUsed(objectTypes objectType)
{
    return (objectType == objectTypeFlower);
}
//bool gameObjectElixer::canItemBeUsed(objectTypes objectType) { return objectTypeElixer; }
//bool gameObjectStarFish::canItemBeUsed(objectTypes objectType) { return booltarFish; }
//bool gameObjectSquirtle::canItemBeUsed(objectTypes objectType) { return boolquirtle; }
//bool gameObjectStarmie::canItemBeUsed(objectTypes objectType) { return booltarmie; }
//bool gameObjectGem::canItemBeUsed(objectTypes objectType) { return objectTypeGem; }
//bool gameObjectGemKey::canItemBeUsed(objectTypes objectType) { return objectTypeGemKey; }
//bool gameObjectOrbHole::canItemBeUsed(objectTypes objectType) { return objectTypeOrbHole; }
//bool gameObjectStick::canItemBeUsed(objectTypes objectType) { return booltick; }
//bool gameObjectLantern::canItemBeUsed(objectTypes objectType) { return objectTypeLantern; }
//bool gameObjectMagicDoor::canItemBeUsed(objectTypes objectType) { return objectTypeMagicDoor; }


std::string gameObjectKnife::GetText() { return "A rusty old knife with an intricate wooden handle.\n\nEngraved on the handle are the letters \"JP\"\n\n"; }
std::string gameObjectChest::GetText()
{
    if (chestOpened)
    {
        return "An opened chest.\n\nThe inside is padded with cloth and foam.\n\n";
    }
    else
    {
        return "A locked Chest.\n\nThe lock looks very weak and old.\n\n";
    }
}
std::string gameObjectLock::GetText()
{
    return "An old lock.\n\nThe tumbler looks intact.\n\n";
}
std::string gameObjectCrystalOrb::GetText() { return "A small glowing crystal orb.\n\nIt appears to emit a type of blue light.\n\n"; }
std::string gameObjectFlower::GetText() { return "A group of small orange flowers with many pedals.\n\n"; }
std::string gameObjectTeaPot::GetText() { return "A Teapot\n\n"; }
std::string gameObjectElixer::GetText() { return "The elixer brewed from orange flowers.\n\n"; }
std::string gameObjectStarFish::GetText() { return "A Starfish covered in some type of goo.\n\nIt looks sick.\n\n"; }
std::string gameObjectSquirtle::GetText() { return "A Squirtle (some type of turtle).\n\nIt appears to be sad.\n\n"; }
std::string gameObjectStarmie::GetText() { return "A happy Starmie.\n\nIt is swimming back and forth.\n\n"; }
std::string gameObjectGem::GetText() { return "A glowing green gem.\n\nIt appears to slide apart and something is inside.\n\n"; }
std::string gameObjectGemKey::GetText() { return "A key from the green gem.\n\n"; }
std::string gameObjectOrbHole::GetText()
{
    if (hasOrb)
    {
        return "A small hole in the wall that has a blue orb in it.\n\nThere are symbols around the hole that are glowing brightly.\n\n";
    }
    else
    {
        return "A small hole in the wall that has a slight blue glow.\n\nThere are symbols around the hole.\n\n";
    }
}
std::string gameObjectStick::GetText() { return "A dried out old stick.\n\nPerfect for burning.\n\n"; }
std::string gameObjectLantern::GetText()
{
    if (hasStick)
    {
        return "An old lantern.\n\nThere is an old stick inside of it burning.\n\n";
    }
    else
    {
        return "An old lantern.\n\nIt does not have any thing to burn inside of it.\n\n";
    }
    
}
std::string gameObjectMagicDoor::GetText()
{
    if (doorKey)
    {
        return "A magic door with the gem in the key hole.\n\nThe center of the door became transparent and looks like running water.";
    }
    else
    {
        return "A magic door with an empty key hole.\n\n";
    }
}

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
    static bool rewarded = false;
    if (Controller->GetGameSpaceByType(gameSpaceLocationRiver)->ContainsObject(objectTypeStarFish))
    {
        if (firstTime == true)
        {
            firstTime = false;
            return "\t\tHello traveler...\n\n\tI have a gift for you, but first you need to help my friend. There is a pond a short walk from here.\nMy friend that lives in it is sick and needs the brewed elixer from flowers that grow in this area to heal.\n\nPlease help him and I will reward you!\n\n";
        }
        else
        {
            return "\tHave you found my friend?\n\nIt makes me sad that he is still stick.\nThe flowers that grow in this area will cure him if they are brewed.";
        }
    }
    else
    {
        if (rewarded == false)
        {
            // Give reward.
            rewarded = true;
            return "\t\tMy friend is healed! Thank you so much!\n\tHere is a specal gem that I have been saving. I think it came from a nearby cave.";
            // Add gem to inventory or space...?
        }
        else
        {
            // Thanks
            return "Thanks again!";
        }
    }
}