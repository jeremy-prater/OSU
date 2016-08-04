#ifndef GAME_SPACES_HPP
#define GAME_SPACES_HPP

#include "gameSpace.hpp"

class gameSpaceForest : public gameSpace
{
public:
    gameSpaceForest(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceForest() { }

    std::string GetSpaceText();
};

class gameSpaceTrail1 : public gameSpace
{
public:
    gameSpaceTrail1(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceTrail1() { }

    std::string GetSpaceText();
};

class gameSpaceRiver : public gameSpace
{
public:
    gameSpaceRiver(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceRiver() { }

    std::string GetSpaceText();
};

class gameSpaceTrail2 : public gameSpace
{
public:
    gameSpaceTrail2(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceTrail2() { }

    std::string GetSpaceText();
};

class gameSpaceCabin : public gameSpace
{
public:
    gameSpaceCabin(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceCabin() { }

    std::string GetSpaceText();
};

class gameSpaceCabinBasement : public gameSpace
{
public:
    gameSpaceCabinBasement(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceCabinBasement() { }

    std::string GetSpaceText();
};

class gameSpaceTrail3 : public gameSpace
{
public:
    gameSpaceTrail3(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceTrail3() { }

    std::string GetSpaceText();
};

class gameSpaceCave : public gameSpace
{
public:
    gameSpaceCave(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceCave() { }

    std::string GetSpaceText();
};

class gameSpaceCaveRoom : public gameSpace
{
public:
    gameSpaceCaveRoom(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceCaveRoom() { }

    std::string GetSpaceText();
};

class gameSpaceTrail4 : public gameSpace
{
public:
    gameSpaceTrail4(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpaceTrail4() { }

    std::string GetSpaceText();
};

class gameSpacePond : public gameSpace
{
public:
    gameSpacePond(gameSpaceDescription * location, const gameSpaceController * controller) : gameSpace(location, controller) { }
    ~gameSpacePond() { }

    std::string GetSpaceText();
};

#endif // GAME_SPACES_HPP