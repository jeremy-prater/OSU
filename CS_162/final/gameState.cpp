#include "gameState.hpp"
#include "gameSpaceController.hpp"
#include "gamePlayer.hpp"
#include <iostream>
#include "lib_flip_display.hpp"

gameState::gameState()
{
    Controller = new gameSpaceController();
    Player = new gamePlayer(Controller);
    Player->MoveToSpace (gameSpaceLocationForest);
    MovesLeft = 50;  
}

gameState::~gameState()
{
    delete Controller;
    delete Player;
}

std::string gameState::PrintRound()
{
    if (DebugConsole::GetDebugLevel() == 0)
    {
        DebugConsole::screen_clear();
    }

    DebugConsole::debug_print (0, false, COLOR_CYAN, "Moves left: ");

    if (MovesLeft <= 10)
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "%d\n\n", MovesLeft);
    }
    else if (MovesLeft <= 20)
    {
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "%d\n\n", MovesLeft);
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_GREEN, "%d\n\n", MovesLeft);
    }
    

    DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\n\nLocation [%s]\n\n", Controller->GetCurrentSpace()->GetSpaceDescription().spaceName.c_str());
    DebugConsole::debug_print (0, false, COLOR_WHITE, "%s\n\n", Controller->GetCurrentSpace()->GetSpaceText().c_str());

    std::string inventory = "Inventory: ";
    std::string inventoryList = "";
    bool inventoryEmpy = true;
    for (int inventoryCount = 0; inventoryCount < NUM_ITEMS_INVENTORY; inventoryCount++)
    {
        gameObject * backpackItem = Player->GetBackpack()[inventoryCount]; 
        if (backpackItem != __null)
        {
            inventoryList += std::string("\t") + std::to_string(inventoryCount + 1) + ": " + backpackItem->GetName();
            inventoryEmpy = false; 
        }
    }
    if (inventoryEmpy)
    {
        inventory = "Inventory Empty.\n\n\n";
    }

    DebugConsole::debug_print (0, true, COLOR_CYAN, "%s", inventory.c_str());
    if (!inventoryEmpy)
    {
        DebugConsole::debug_print (0, false, COLOR_WHITE, "%s\n\n", inventoryList.c_str());
    }

    DebugConsole::debug_print (0, true, COLOR_CYAN, "Moves: ", inventory.c_str());
    std::string moveList = "";
    for (int moveCount = 0; moveCount < NUM_CONNECTED_SPACES; moveCount++)
    {
        if (Player->GetCurrentSpace()->GetSpaceDescription().connectedSpaces[moveCount] != gameSpaceLocationInvalid)
        {
            moveList += std::string("\t ") + std::to_string(moveCount + 1) + ": " + Controller->GetGameSpaceByType (Player->GetCurrentSpace()->GetSpaceDescription().connectedSpaces[moveCount])->GetSpaceDescription().spaceName;
        } 
    }
    DebugConsole::debug_print (0, false, COLOR_WHITE, "%s\n\n\n", moveList.c_str());

    DebugConsole::debug_print (0, true, COLOR_CYAN, "Objects in space: ", inventory.c_str());
    if (Player->GetCurrentSpace()->GetObjects().size() > 0)
    {
        std::string objectList = "";
        for (int objectCount = 0; objectCount < Player->GetCurrentSpace()->GetObjects().size(); objectCount++)
        {
            objectList += std::string("\t ") + std::to_string(objectCount + 1) + ": " + Player->GetCurrentSpace()->GetObjects()[objectCount]->GetName();   
        }    
        DebugConsole::debug_print (0, false, COLOR_WHITE, "%s\n\n\n", objectList.c_str());
    }
    else
    {
        DebugConsole::debug_print (0, false, COLOR_WHITE, "None.\n\n\n");
    }

    DebugConsole::debug_print (0, true, COLOR_WHITE, "Commands:\n\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "m<id> - Move to new space. Example : >m2\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "i<id> - Interact wth inventory item. Example : >i2\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "o<id> - Interact with object in space. Example : >o1\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "q     - Abandon the quest.\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "\n\nEnter Command >");
    std::string command;
    std::cin >> command;
    return command;
}

void gameState::GameLoop()
{
    bool playing = true;
    while (playing)
    {
        const char * commandPtr = PrintRound().c_str();
        switch (commandPtr[0])
        {
            case 'q':
            case 'Q':
            {
                playing = false;
            }
            break;
            case 'm':
            case 'M':
            {
                int moveTo = atoi (&commandPtr[1]);
                if ((moveTo > 0) && (moveTo <= NUM_CONNECTED_SPACES))
                {
                    if (Player->MoveToSpace (Player->GetCurrentSpace()->GetSpaceDescription().connectedSpaces[moveTo - 1]))
                    {
                        MovesLeft--;
                    }
                }
            }
            break;
            case 'o':
            case 'O':
            {
                int objectID = atoi (&commandPtr[1]);
                if ((objectID > 0) && (objectID <= Player->GetCurrentSpace()->GetObjects().size()))
                {
                    InteractObject (Player->GetCurrentSpace()->GetObjects()[objectID - 1]);
                }
            }
            break;
            case 'i':
            case 'I':
            {
                int objectID = atoi (&commandPtr[1]);
                if ((objectID > 0) && (objectID <= NUM_ITEMS_INVENTORY) && (Player->GetBackpack()[objectID - 1] != __null))
                {
                    InteractObject (Player->GetBackpack()[objectID - 1]);
                }
            }
            break;
        }

        if (Player->GameWon() == true)
        {
            playing = false;
            DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\n\t\tThank you for freeing me!\n\n\tThe creatures of the forest are saved!!\n\n");
        }
        if (MovesLeft == 0)
        {
            playing = false;
            DebugConsole::debug_print (0, true, COLOR_RED, "\n\n\t\tTime is up!!\n\nThe creatures of the forest are doomed...\n\n");
        }
    }
}

void gameState::InteractObject (gameObject * object)
{
    DebugConsole::debug_print (0, true, COLOR_CYAN, "\n\nInteracting with %s.\n\n", object->GetName().c_str());
    DebugConsole::debug_print (0, true, COLOR_WHITE, "\n\nCommands: \n\n");
    if (object->canTalk())
    {
        DebugConsole::debug_print (0, true, COLOR_WHITE, "t - Talk to %s\n", object->GetName().c_str());
    }
    if (object->canTake())
    {
        DebugConsole::debug_print (0, true, COLOR_WHITE, "g - Take to %s\n", object->GetName().c_str());
    }
    if (object->canRead())
    {
        DebugConsole::debug_print (0, true, COLOR_WHITE, "r - Look at %s\n", object->GetName().c_str());
    }
    DebugConsole::debug_print (0, true, COLOR_WHITE, "u - Use %s\n", object->GetName().c_str());
    DebugConsole::debug_print (0, true, COLOR_WHITE, "c - Walk away from %s\n", object->GetName().c_str());
    DebugConsole::debug_print (0, true, COLOR_WHITE, "\n\nEnter Command >");
    std::string command;
    std::cin >> command;
}