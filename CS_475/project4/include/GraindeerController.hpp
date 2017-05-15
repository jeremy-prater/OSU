////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 4 - Control Threads
//
// Jeremy Prater
//
// Main Header
//

#ifndef PROJECT4_GRAINDEER_CONTROLLER_H
#define PROJECT4_GRAINDEER_CONTROLLER_H

#include "project4.hpp"

class GraindeerController
{
public:
    GraindeerController();
    ~GraindeerController();

    void GetInitialState(SystemState * state);

    static void GrainDeer();
    static void Grain();
    static void Watcher();
    static void HMI();
};

#endif // PROJECT4_GRAINDEER_CONTROLLER_H
