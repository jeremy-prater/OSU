#ifndef GAME_SPACES_HPP
#define GAME_SPACES_HPP

#include "gameSpace.hpp"

class gameSpaceForest : public gameSpace
{
public:
    gameSpaceForest(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceForest() { }

    std::string GetSpaceText();
};

class gameSpaceTrail1 : public gameSpace
{
public:
    gameSpaceTrail1(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceTrail1() { }

    std::string GetSpaceText();
};

class gameSpaceRiver : public gameSpace
{
public:
    gameSpaceRiver(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceRiver() { }

    std::string GetSpaceText();
};

class gameSpaceTrail2 : public gameSpace
{
public:
    gameSpaceTrail2(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceTrail2() { }

    std::string GetSpaceText();
};

class gameSpaceCabin : public gameSpace
{
public:
    gameSpaceCabin(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceCabin() { }

    std::string GetSpaceText();
};

class gameSpaceCabinBasement : public gameSpace
{
public:
    gameSpaceCabinBasement(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceCabinBasement() { }

    std::string GetSpaceText();
};

class gameSpaceTrail3 : public gameSpace
{
public:
    gameSpaceTrail3(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceTrail3() { }

    std::string GetSpaceText();
};

class gameSpaceCave : public gameSpace
{
public:
    gameSpaceCave(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceCave() { }

    std::string GetSpaceText();
};

class gameSpaceCaveRoom : public gameSpace
{
public:
    gameSpaceCaveRoom(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceCaveRoom() { }

    std::string GetSpaceText();
};

class gameSpaceTrail4 : public gameSpace
{
public:
    gameSpaceTrail4(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpaceTrail4() { }

    std::string GetSpaceText();
};

class gameSpacePond : public gameSpace
{
public:
    gameSpacePond(gameSpaceDescription * location) : gameSpace(location) { }
    ~gameSpacePond() { }

    std::string GetSpaceText();
};

#endif // GAME_SPACES_HPP