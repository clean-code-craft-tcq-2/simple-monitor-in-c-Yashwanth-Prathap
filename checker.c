#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct {  
  char parameterName[20];
  float minThreshold;
  float maxThreshold; 
  float warningLimitHigh;
  float warningLimitLow;
} BatteryParamInfo;

BatteryParamInfo paramInfo[3];

void PopulateparamInfo(){
  
	strcpy(paramInfo[0].parameterName,"Temperature");
	paramInfo[0].minThreshold = 0;
	paramInfo[0].maxThreshold = 45;
	paramInfo[0].warningLimitHigh = 45;
	paramInfo[0].warningLimitHigh = 45;
	
	strcpy(paramInfo[1].parameterName, "SOC");
	paramInfo[1].minThreshold = 20;
	paramInfo[1].maxThreshold = 80;
	paramInfo[0].warningLimitHigh = 45;
	paramInfo[0].warningLimitHigh = 45;
	
	strcpy(paramInfo[2].parameterName, "Charge Rate");  
	paramInfo[2].minThreshold = 0.0;
	paramInfo[2].maxThreshold = 0.8;
	paramInfo[0].warningLimitHigh = 45;
	paramInfo[0].warningLimitHigh = 45;
}

void printToConsole(char message[])
{
printf(message);
}

/*int checkparamlimits(char parameter[], float value, float minvalue, float maxvalue){
if(value < minvalue){
	printToConsole(strcat(parameter , "is less than lowerlimit \n"));
	return 0;
	}
else if( value > maxvalue){
	printToConsole(strcat(parameter , "exceeds upperlimit \n"));
	return 0;
	}
else {
	return 1;
	}
}*/


int checkparamlimits(BatteryParameterInfo parameterInfo,  float value){
	
if(value < parameterInfo.minimumThreshold){
	printToConsole(strcat(paramInfo.parameterName , "is less than lowerlimit \n"));
	return 0;
	}
else if( value > paramInfo.maximumThreshold){
	printToConsole(strcat(paramInfo.parameterName , "exceeds upperlimit \n"));
	return 0;
	}
else {
	return 1;
	}
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
int output;

	
output = checkparamlimits (paramInfo[0], temperature)&
checkparamlimits (paramInfo[1], soc) &
checkparamlimits (paramInfo[2], chargeRate);

return output;
}

int main() {
  PopulateparamInfo();
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 60, 0.7));
  assert(!batteryIsOk(30, 85, 0.1));
  assert(!batteryIsOk(25, 70, 0.9));
}
