#include "MindControl.h"


MindControl::MindControl(char *portName)
{
	connected = false;
	connectionId = TG_GetNewConnectionId();
	if( connectionId < 0 ) {
        fprintf( stdout, "ERROR: TG_GetNewConnectionId() returned %d.\n", 
                 connectionId );
		connected = false;
        return;
    }

	printf("Connecting to %s\n", portName);
	errCode = TG_Connect( connectionId, 
                          portName, 
                          TG_BAUD_9600, 
                          TG_STREAM_PACKETS );
	if( errCode < 0 ) {
        fprintf( stdout, "ERROR: TG_Connect() returned %d.\n", errCode );
		connected = false;
        return;
    }
	if(TG_ReadPackets(connectionId, 1 ) < 0){
		connected = false;
	}
	else{
		connected = true;
	}	
}

MindControl::MindControl(int cId){
	connectionId = cId;
	if(TG_ReadPackets(connectionId, 1 ) < 0){
		connected = false;
	}
	else{
		connected = true;
	}	
}

MindControl::~MindControl(void)
{
	TG_FreeConnection( connectionId );
	connected = false;
}

bool MindControl::isConnected(void)
{
	return connected;
}

int MindControl::logOn(void)
{
	if(!isConnected()){
		return -1;
	}

	errCode = TG_SetStreamLog( connectionId, "streamLog.txt" );
    if( errCode < 0 ) {
        fprintf( stderr, "ERROR: TG_SetStreamLog() returned %d.\n", errCode );
        return errCode;
    }

    errCode = TG_SetDataLog( connectionId, "dataLog.txt" );
    if( errCode < 0 ) {
        fprintf( stderr, "ERROR: TG_SetDataLog() returned %d.\n", errCode );
        return errCode;
    }

	return 1;
}

int MindControl::logOff(void)
{
	if(!isConnected()){
		return -1;
	}
	TG_SetStreamLog( connectionId, NULL );
	TG_SetDataLog( connectionId, NULL );

	return 1;
}

void MindControl::analyzeData(void)
{
	float   meditationValue;
	float   attentionValue;
	printf("\tAttention\tMeditation\n");
	while(1){
		attentionValue = meditationValue = 0;
		TG_ReadPackets( connectionId, 1 );

		if(TG_GetValueStatus(connectionId, TG_DATA_ATTENTION) != 0){
			attentionValue = TG_GetValue(connectionId, TG_DATA_ATTENTION);
		}
		if(TG_GetValueStatus(connectionId, TG_DATA_MEDITATION) != 0){
			meditationValue = TG_GetValue(connectionId, TG_DATA_MEDITATION);
		}

		if(attentionValue || meditationValue){
			m.addValue(attentionValue, meditationValue);
			showValues(attentionValue, meditationValue, m.makeDecision_0());
		}
		if(TG_GetValueStatus(connectionId, TG_DATA_POOR_SIGNAL) != 0){
            if(TG_GetValue(connectionId, TG_DATA_POOR_SIGNAL) > 180){
				break;
			}
		}
	}
	printf("\nSignal lost\n");
}

void MindControl::showValues(float a, float m, bool takeOff)
{
	printf("\t%5.2f\t\t%5.2f", a, m);
	if(takeOff){
		printf("\t Take Off\n");
	}
	else{
		printf("\r");		// carriage-return !!!!
	}
	fflush(stdout);
}