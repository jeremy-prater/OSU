#include "gameObject.hpp"

gameObject::gameObject(unsigned int id, unsigned int type)
{
    objectID = id;
    objectType = type;
}

gameObject::~gameObject()
{

}
unsigned int gameObject::GetObjectID()
{
    return objectID;
}
unsigned int gameObject::GetObjectType()
{
    return objectType;
}