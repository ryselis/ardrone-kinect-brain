#include "MindStatistic.h"

int MindStatistic::getCount(void)
{
	return count;
}

void MindStatistic::addValue(float a, float m)
{
	for(int i = 1; i < BUF_LENGHT; i++){
		attentionBuf[i] = attentionBuf[i - 1];
		meditationBuf[i] = meditationBuf[i - 1];
		attentionBuf[0] = a;
		meditationBuf[0] = m;
		count = count < BUF_LENGHT ? count++ : count;
	}
}

float MindStatistic::meanMeditation(void)
{
	float sum = 0;
	for(int i = 0; i < count; i++){
		sum += meditationBuf[i];
	}
	return sum/count;
}

float MindStatistic::meanAttention(void)
{
	float sum = 0;
	for(int i = 0; i < count; i++){
		sum += attentionBuf[i];
	}
	return sum/count;
}

//grazina true, jei naujausia Meditation reiksme didesne uz THRESHOLD nustatyta .h faile.
bool MindStatistic::makeDecision_0(void)
{
	return meditationBuf[0] > THRESHOLD;
}

// grazina true, jeigu naujausia Meditation reiksme 10% didesne nei buferio reiksmiu vidurikis.
bool MindStatistic::makeDecision_1(void)
{
	return meditationBuf[0] > (meanMeditation() * 0.1);
}

// true, jeigu paskutnes 5 meditation reiksmes didejancios
bool MindStatistic::makeDecision_2(void)
{
	bool bigger = true;		// prielaida, kad reiksmes dideja.

	for(int i = 0; i < 5; i++){
		if(meditationBuf[i + 1] > meditationBuf[i]){
			bigger = false;
			break;
		}
	}
	return bigger;
}