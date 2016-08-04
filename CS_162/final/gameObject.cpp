#include "gameObject.hpp"
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

int gameObject::useItem(gameObject * target)
{
    return 0;
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

bool gameObject::canItemBeUsed(objectTypes objectType)
{
    // Objects must be explicitly allowed to be used.
    return false;
}