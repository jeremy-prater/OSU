////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 4 - Graindeer Controller
//
// Jeremy Prater
//
//

#include "GraindeerController.hpp"

const float GraindeerController::GRAIN_GROWS_PER_MONTH   = 8.0;
const float GraindeerController::ONE_DEER_EATS_PER_MONTH = 0.5;

const float GraindeerController::AVG_PRECIP_PER_MONTH    = 6.0;	// average
const float GraindeerController::AMP_PRECIP_PER_MONTH    = 6.0;	// plus or minus
const float GraindeerController::RANDOM_PRECIP           = 2.0;	// plus or minus noise

const float GraindeerController::AVG_TEMP                = 50.0;	// average
const float GraindeerController::AMP_TEMP                = 20.0;	// plus or minus
const float GraindeerController::RANDOM_TEMP             = 10.0;	// plus or minus noise

const float GraindeerController::MIDTEMP                 = 40.0;
const float GraindeerController::MIDPRECIP               = 10.0;

void GraindeerController::GetInitialState(SystemState * state)
{
    // starting date and time:
    state->NowDay     = 14;
    state->NowMonth   = 5;
    state->NowYear    = 2017;

    // starting state (feel free to change this if you want):
    state->NowNumDeer = 1;
    state->NowHeight  = 1.;
}

void GraindeerController::UpdateDate(SystemState * state, int nowDay)
    float ang = (30. * (float)NowMonth + nowDay) * ( M_PI / 180. );

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    unsigned int seed = 0;
    NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
    if( NowPrecip < 0. )
        NowPrecip = 0.;
}

GraindeerController::GraindeerController()
{

}

GraindeerController::~GraindeerController()
{

}

void GraindeerController::GrainDeer()
{

}
void GraindeerController::Grain()
{

}

void GraindeerController::Watcher()
{

}

void GraindeerController::HMI()
{

}