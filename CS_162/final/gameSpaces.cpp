#include "gameSpaces.hpp"

std::string gameSpaceForest::GetSpaceText()
{
    static bool firstTime = true;
    std::string text = "";
    if (firstTime == true)
    {
        text += "You awake with a note in your pocket that says \n\t\"Help me, I am trapped behind a door in a room made of rock.\n\tI know who is enslaving the creature of this land.\n\tGo find my friend in the pond, he will help you.\n\tYou must hurry and free me, time is short!\n\tYou are in danger!\"\n\n";
        firstTime = false;
    }
    text += "You are in a small clearing in the woods. Light gleams through the gaps between the trees and casts moving shadows all over the ground. There are three trails that leave from this area.";
    return text;
}
std::string gameSpaceTrail1::GetSpaceText()
{
    return "";
}
std::string gameSpaceRiver::GetSpaceText()
{
    return "";
}
std::string gameSpaceTrail2::GetSpaceText()
{
    return "";
}
std::string gameSpaceCabin::GetSpaceText()
{
    return "";
}
std::string gameSpaceCabinBasement::GetSpaceText()
{
    return "";
}
std::string gameSpaceTrail3::GetSpaceText()
{
    return "";
}
std::string gameSpaceCave::GetSpaceText()
{
    return "";
}
std::string gameSpaceCaveRoom::GetSpaceText()
{
    return "";
}
std::string gameSpaceTrail4::GetSpaceText()
{
    return "";
}
std::string gameSpacePond::GetSpaceText()
{
    return "";
}