#pragma once

#define BUF_LENGHT 10
#define THRESHOLD 70

class MindStatistic
{

private:	
	float attentionBuf[BUF_LENGHT];
	float meditationBuf[BUF_LENGHT];
	int count;
	
	float meanAttention(void);
	float meanMeditation(void);
	
public:
	MindStatistic():count(0) { };
	int getCount(void);
	void addValue(float a, float m);
	//grazina true, jei naujausia Meditation reiksme didesne uz THRESHOLD nustatyta .h faile.
	bool makeDecision_0(void);
	// grazina true, jeigu naujausia Meditation reiksme 10% didesne nei buferio reiksmiu vidurikis.
	bool makeDecision_1(void);
	// true, jeigu paskutnes 5 meditation reiksmes didejancios
	bool makeDecision_2(void);
	
};
