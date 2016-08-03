#include "gameObject.hpp"

gameObject::gameObject()
{

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
