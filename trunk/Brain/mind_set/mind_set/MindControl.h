#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "thinkgear.h"
#include "MindStatistic.h"

class MindControl
{
private:
	bool connected;
    int   connectionId;
    int   errCode;
	MindStatistic m;
	void showValues(float a, float m, bool takeOff);

public:
	MindControl(char *portName);
	MindControl(int cId);
	~MindControl(void);

	bool isConnected(void);
	int logOn(void);
	int logOff(void);
	void analyzeData(void);

};

