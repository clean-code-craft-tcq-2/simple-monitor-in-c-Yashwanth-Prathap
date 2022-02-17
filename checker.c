#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LOWER_THRESHOLD_BATT_TEMP 0
#define UPPER_THRESHOLD_BATT_TEMP 45
#define LOWER_THRESHOLD_BATT_SOC 20
#define UPPER_THRESHOLD_BATT_SOC 80
#define UPPER_THRESHOLD_BATT_CHARGE_RATE 0.8
#define LOWER_THRESHOLD_BATT_CHARGE_RATE 0.5
#define TOLERANCE_PERCENTAGE 0.05

typedef struct {
  
  char parameterName[20];
  float minThreshold;
  float maxThreshold; 
  float warningLimitHigh;
  float warningLimitLow;
} BatteryParamInfo;

BatteryParamInfo paramInfo[3];

enum Language{
	English,
	German} language;

void PopulateParameterInfo(){
  
	strcpy(paramInfo[0].parameterName,"Temperature");
	paramInfo[0].minThreshold = LOWER_THRESHOLD_BATT_TEMP;
	paramInfo[0].maxThreshold = UPPER_THRESHOLD_BATT_TEMP;
	paramInfo[0].warningLimitHigh = (UPPER_THRESHOLD_BATT_TEMP + (UPPER_THRESHOLD_BATT_TEMP * TOLERANCE_PERCENTAGE));
	paramInfo[0].warningLimitLow = (LOWER_THRESHOLD_BATT_TEMP - (UPPER_THRESHOLD_BATT_TEMP * TOLERANCE_PERCENTAGE));
	
	strcpy(paramInfo[1].parameterName, "SOC");
	paramInfo[1].minThreshold = LOWER_THRESHOLD_BATT_SOC;
	paramInfo[1].maxThreshold = UPPER_THRESHOLD_BATT_SOC;
	paramInfo[1].warningLimitHigh = (UPPER_THRESHOLD_BATT_SOC + (UPPER_THRESHOLD_BATT_SOC * TOLERANCE_PERCENTAGE));
	paramInfo[1].warningLimitLow = (LOWER_THRESHOLD_BATT_SOC - (UPPER_THRESHOLD_BATT_SOC * TOLERANCE_PERCENTAGE));
	
	strcpy(paramInfo[2].parameterName, "Charge Rate");  
	paramInfo[2].minThreshold = LOWER_THRESHOLD_BATT_CHARGE_RATE;
	paramInfo[2].maxThreshold = UPPER_THRESHOLD_BATT_CHARGE_RATE;
	paramInfo[2].warningLimitHigh = (UPPER_THRESHOLD_BATT_CHARGE_RATE + (UPPER_THRESHOLD_BATT_CHARGE_RATE * TOLERANCE_PERCENTAGE));
	paramInfo[2].warningLimitLow = (LOWER_THRESHOLD_BATT_CHARGE_RATE - (UPPER_THRESHOLD_BATT_CHARGE_RATE * TOLERANCE_PERCENTAGE));
}

char* EnglishMessage[]= {
	"is okay \n",
	"is less than lowerlimit \n",
	"exceeds upperlimit \n",
	"is approaching lowerlimit \n"
	"is approaching upperlimit \n"
	};

char* GermanMessage[]= {
	"es ist okay \n",
	"ist kleiner als untere Grenze \n",
	"Obergrenze überschreitet \n",
	"nähert sich der unteren Grenze \n"
	"nähert sich der Obergrenze \n"
	};


	
void printToConsole(char message[])
{
printf(message);
}

setMessageToPrint (char parameter[], int parameterStatus){
	if(language == 0) {
	printToConsole(strcat(parameter , EnglishMessage[parameterStatus]));	
	}
	else if (language ==1){
	printToConsole(strcat(parameter , GermanMessage[parameterStatus]));	
	}
}



int checkparamlimits(BatteryParameterInfo parameterInfo,  float value){	
	
if(value < parameterInfo.minimumThreshold){
	//printToConsole(strcat(parameterInfo.parameterName , "is less than lowerlimit \n"));
	setMessageToPrint (parameterInfo.parameterName , 1);
	return 0;
	}
else if( value > parameterInfo.maximumThreshold){
	//printToConsole(strcat(parameterInfo.parameterName , "exceeds upperlimit \n"));
	setMessageToPrint (parameterInfo.parameterName , 2);
	return 0;
	}
else {
	setMessageToPrint (parameterInfo.parameterName , 0);
	return 1;
	}
}

int checkForWarnings(BatteryParameterInfo parameterInfo,  float value){	
if(value < parameterInfo.warningLimitLow){
	//printToConsole(strcat(parameterInfo.parameterName , "is approaching lowerlimit \n"));
	setMessageToPrint (parameterInfo.parameterName , 3);
	return 0;
	}
else if( value > parameterInfo.warningLimitHigh){
	//printToConsole(strcat(parameterInfo.parameterName , "is approaching upperlimit \n"));
	setMessageToPrint (parameterInfo.parameterName , 4);
	return 0;
	}
else {
	return 1;
	}
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
int output;
/* Check for breaches */	
output = checkparamlimits (parameterInfo[0], temperature)&
checkparamlimits (parameterInfo[1], soc) &
checkparamlimits (parameterInfo[2], chargeRate);

/* If there are no breaches, check for warnings */
if(output==1)
{
output = checkForWarnings (parameterInfo[0], temperature)&
checkForWarnings (parameterInfo[1], soc) &
checkForWarnings (parameterInfo[2], chargeRate);
}

return output;
}

int main() {
  PopulateParameterInfo();
	language = 0;
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 60, 0.7));
	language =1;
  assert(!batteryIsOk(30, 85, 0.1));
  assert(!batteryIsOk(25, 70, 0.9));
}
