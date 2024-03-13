/*
FILENAME...     PICoordinateSystem.cpp

Original Author: Guilherme Rodrigues de Lima
Created: 05.03.2024
*/

#include "PICoordinateSystem.h"
#include "PIasynAxis.h"
#include "PIInterface.h"
using namespace std;

asynStatus PICoordinateSystem::getStatus(PIasynAxis* pAxis, int& homing, int& moving, int& negLimit, int& posLimit, int& servoControl)
{
    char cmd[100];
    char buf[255];
    asynStatus status = asynSuccess;

	status = getMoving(pAxis, moving);
	if (status != asynSuccess)
	{
		return status;
	}

	homing = 0;
	negLimit = 0; 
	posLimit = 0;
	
	status = getServo(pAxis, servoControl);
	if (status != asynSuccess)
	{
		return status;
	} 

    return status;
}

asynStatus PICoordinateSystem::setActivate(const char* value)
{
    char cmd[100];
	char buf[255];

	sprintf(cmd, "KEN %s", value);
    printf(cmd);
	asynStatus status = m_pInterface->sendOnly(cmd);
    
	if (status != asynSuccess)
	{
		return status;
	}

    return status;
}

asynStatus PICoordinateSystem::getActivate(string &value)
{
    char cmd[100];
	char buf[255];

	sprintf(cmd, "KEN?");

	asynStatus status = m_pInterface->sendAndReceive(cmd, buf, 255);
    value = string(buf);
    value.erase(remove(value.begin(), value.end(), '\n'), value.end());

	if (status != asynSuccess)
	{
		return status;
	}
    
    return status;
}

asynStatus PICoordinateSystem::getLink(string &value)
{
    char cmd[100];
	char buf[255];

	sprintf(cmd, "KLN?");

	asynStatus status = m_pInterface->sendAndReceive(cmd, buf, 255);
    value = string(buf);
    value.erase(remove(value.begin(), value.end(), '\n'), value.end());
    replace(value.begin(), value.end(), '\t', ' ');

	if (status != asynSuccess)
	{
		return status;
	}
    
    return status;
}

asynStatus PICoordinateSystem::setLink(const char* value)
{
    char cmd[100];
	char buf[255];

	sprintf(cmd, "KLN %s", value);
    printf(cmd);
	asynStatus status = m_pInterface->sendOnly(cmd);
    
	if (status != asynSuccess)
	{
		return status;
	}

    return status;
}

asynStatus PICoordinateSystem::setToolOffset(const char* value)
{
    char cmd[100];
	char buf[255];

	sprintf(cmd, "KST %s", value);
    printf(cmd);
	asynStatus status = m_pInterface->sendOnly(cmd);
    
	if (status != asynSuccess)
	{
		return status;
	}

    return status;
}

asynStatus PICoordinateSystem::setWorkOffset(const char* value)
{
    char cmd[100];
	char buf[255];

	sprintf(cmd, "KSW %s", value);
    printf(cmd);
	asynStatus status = m_pInterface->sendOnly(cmd);
    
	if (status != asynSuccess)
	{
		return status;
	}

    return status;
}

asynStatus PICoordinateSystem::getTravelLimits(PIasynAxis* pAxis, double& negLimit, double& posLimit)
{   
    char cmd[100];
	char buf[255];
	asynStatus status = asynSuccess;

	sprintf(cmd, "TRA? %s -1", pAxis->m_szAxisName);
	status = m_pInterface->sendAndReceive(cmd, buf, 255);

	if (status != asynSuccess)
	{
		return status;
	}

	if (!getValue(buf, negLimit))
	{
		return asynError;
	}

	sprintf(cmd, "TRA? %s 1", pAxis->m_szAxisName);
	status = m_pInterface->sendAndReceive(cmd, buf, 255);

	if (status != asynSuccess)
	{
		return status;
	}

	if (!getValue(buf, posLimit))
	{
		return asynError;
	}

    return status;
}
