#include <string.h>
#include "gamePlayer.hpp"
#include "gameSpaceController.hpp"
#include "lib_flip_display.hpp"

gamePlayer::gamePlayer(gameSpaceController * instance)
{
    gameSpaceControllerInstance = instance;
    memset (backpackItems, 0, sizeof (backpackItems));
    memset (recycleItems, 0, sizeof (recycleItems));
    gameWon = false;
}

gamePlayer::~gamePlayer()
{
    // Delete any backpack items...
    for (int itemIndex = 0; itemIndex < NUM_ITEMS_INVENTORY; itemIndex++)
    {
        if (backpackItems[itemIndex] != __null)
        {
            delete backpackItems[itemIndex];
            backpackItems[itemIndex] = __null;
        }
    }
}

bool gamePlayer::CanMoveToSpace (gameSpaceLocation location)
{
    gameSpace * gameSpaceObject = gameSpaceControllerInstance->GetGameSpaceByType(location);
    if (gameSpaceObject == __null)
    {
        DebugConsole::debug_print (1, true, COLOR_RED, "[%s] Defaulting to false due to bad location (%d)\n", __func__, location);
        return false;
    }
    return gameSpaceObject->CanMoveTo(this);
}


bool gamePlayer::MoveToSpace (gameSpaceLocation location)
{
    if (!CanMoveToSpace(location))
    {
        DebugConsole::debug_print (1, true, COLOR_YELLOW, "[%s] Attempted to move player to (%d) is not allowed by location!\n", __func__, location);
        return false;
    }  
    currentSpace = gameSpaceControllerInstance->GetGameSpaceByType(location);
    DebugConsole::debug_print (1, true, COLOR_YELLOW, "[%s] Player moved to space %s (0x%p)!\n", __func__, currentSpace->GetSpaceDescription().spaceName.c_str(), currentSpace);
    gameSpaceControllerInstance->SetCurrentSpace (currentSpace);    
    return true;
}

gameObject ** gamePlayer::GetBackpack()
{
    return backpackItems;
}

gameSpace * gamePlayer::GetCurrentSpace()
{
    return currentSpace;
}

bool gamePlayer::GameWon()
{
    return gameWon;
}

void gamePlayer::SetWin()
{
    gameWon = true;
}

bool gamePlayer::MoveObjectToBackpack (gameObject * object)
{
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {
        if (backpackItems[currentObject] == __null)
        {
            backpackItems[currentObject] = object;
            return true;
        }
    }
    return false;
}

void gamePlayer::DestroyObjectInBackpack (gameObject * object)
{
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {
        if (backpackItems[currentObject] == object)
        {
            //delete object;
            recycleItems[currentObject] = backpackItems[currentObject]; 
            backpackItems[currentObject] = __null;
            return;
        }
    }    
}

void gamePlayer::CreateObjectInBackpack (objectTypes type)
{
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {
        if (backpackItems[currentObject] == __null)
        {
            gameObject * newObject = gameObject::CreateObjectFromType (type, gameSpaceControllerInstance);
            DebugConsole::debug_print (1, false, COLOR_WHITE, "Creaing Object %s in backpack\n", newObject->GetName().c_str());
            backpackItems[currentObject] = newObject;
            return;
        }
    }    
}

void gamePlayer::SortAndRecycleItems()
{
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {
        if (recycleItems[currentObject] != __null)
        {
            delete recycleItems[currentObject];
            recycleItems[currentObject] = __null; 
        }
    }        
    int numItemsInBackpack = 0;
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {

        if (backpackItems[currentObject] != __null)
        {
            numItemsInBackpack++;
        }
    }
    for (int currentObject = 0; currentObject < numItemsInBackpack; currentObject++)
    {
        if (backpackItems[currentObject] == __null)
        {
            for (int nextObject = currentObject; nextObject < NUM_ITEMS_INVENTORY; nextObject++)
            {
                if (backpackItems[nextObject] != __null)
                {
                    gameObject * swapObject = backpackItems[nextObject];
                    backpackItems[nextObject] = backpackItems[currentObject];
                    backpackItems[currentObject] = swapObject;
                    break;
                }                   
            }
        }        
    }
}