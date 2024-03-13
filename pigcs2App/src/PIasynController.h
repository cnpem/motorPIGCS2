/*
FILENAME...     PIasynController.cpp
 
*************************************************************************
* Copyright (c) 2011-2013 Physik Instrumente (PI) GmbH & Co. KG
* This file is distributed subject to the EPICS Open License Agreement
* found in the file LICENSE that is included with this distribution.
*************************************************************************
 

Based on drvMotorSim.c

Mark Rivers
December 13, 2009

*/

#ifndef PI_ASYN_DRIVER_INCLUDED_
#define PI_ASYN_DRIVER_INCLUDED_

#include <string.h>
#include "asynMotorController.h"
#include "asynMotorAxis.h"
#include "PIGCS2PiezoCL.h"

class PIasynAxis;
class PIGCSController;

class PIasynController : asynMotorController {
public:
    PIasynController(const char *portName, const char* asynPort, int numAxes, int priority, int stackSize, int movingPollPeriod, int idlePollPeriod);
    asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
    asynStatus writeFloat64(asynUser *pasynUser, epicsFloat64 value);
    
    asynStatus readOctet(asynUser *pasynUser, char *value, size_t maxChars, size_t *nActual, int *eomReason);
    asynStatus writeOctet(asynUser *pasynUser, const char *value, size_t maxChars, size_t *nActual);

    void report(FILE *fp, int level);
    asynStatus profileMove(asynUser *pasynUser, int npoints, double positions[], double times[], int relative, int trigger);
    asynStatus triggerProfile(asynUser *pasynUser);
    asynStatus configAxis(PIasynAxis *pAxis);

    PIasynAxis* getPIAxis(asynUser *pasynUser) { return (PIasynAxis*)asynMotorController::getAxis(pasynUser); }
    PIasynAxis* getPIAxis(int axisNo) { return (PIasynAxis*)asynMotorController::getAxis(axisNo); }

    virtual asynStatus poll();

    u_PIGCS2PiezoCLParams m_CloseLoopParam;
    PIGCS2PiezoCLValues m_CloseLoopValue;

    friend class PIasynAxis;

private:
//    void process(PIasynAxis *pAxis);
    epicsThreadId motorThread;
    int movesDeferred;
    //int numAxes;
    asynStatus processDeferredMoves();
    //PIasynAxis** m_pAxes;
    
    PIGCSController* m_pGCSController;

    int PI_SUP_POSITION;
    int PI_SUP_TARGET;
    int PI_SUP_SERVO;
    int PI_SUP_LAST_ERR;
    int PI_SUP_CLEAR_ERR;
    int PI_SUP_PIVOT_X;
    int PI_SUP_PIVOT_Y;
    int PI_SUP_PIVOT_Z;
    int PI_SUP_RBPIVOT_X;
    int PI_SUP_RBPIVOT_Y;
    int PI_SUP_RBPIVOT_Z;

    int PI_CS_TARGETMODE;
    int PI_CS_ACTIVATE;
    int PI_CS_LINK;
    int PI_CS_KST;
    int PI_CS_KSW;

};

#define PI_SUP_POSITION_String		"PI_SUP_POSITION"
#define PI_SUP_TARGET_String		"PI_SUP_TARGET"
#define PI_SUP_SERVO_String			"PI_SUP_SERVO"
#define PI_SUP_LAST_ERR_String		"PI_SUP_LAST_ERR"
#define PI_SUP_CLEAR_ERR_String		"PI_SUP_CLEAR_ERR"
#define PI_SUP_PIVOT_X_String		"PI_SUP_PIVOT_X"
#define PI_SUP_PIVOT_Y_String		"PI_SUP_PIVOT_Y"
#define PI_SUP_PIVOT_Z_String		"PI_SUP_PIVOT_Z"
#define PI_SUP_RBPIVOT_X_String		"PI_SUP_RBPIVOT_X"
#define PI_SUP_RBPIVOT_Y_String		"PI_SUP_RBPIVOT_Y"
#define PI_SUP_RBPIVOT_Z_String		"PI_SUP_RBPIVOT_Z"

#define PI_CS_TARGETMODE_String		"PI_CS_TARGETMODE"
#define PI_CS_ACTIVATE_String		"PI_CS_ACTIVATE"
#define PI_CS_LINK_String		    "PI_CS_LINK"
#define PI_CS_KST_String		    "PI_CS_KST"
#define PI_CS_KSW_String		    "PI_CS_KSW"

typedef struct PIasynControllerNode {
    ELLNODE node;
    const char *portName;
    PIasynController *pController;
} PIasynControllerNode;

#endif // PI_ASYN_DRIVER_INCLUDED_
