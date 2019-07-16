#include "Iteratiron_method.h"

sqlite3* db1 = nullptr;
float resultTime = 10;
float resultPressure = 60;
float resultTemperature = 1000;
HWND hWnd1;

Iteratiron_method::Iteratiron_method()
{
	int rb = sqlite3_open16(L"Info.db", &db1);


}


Iteratiron_method::~Iteratiron_method()
{
	std::string calculationResultReturn = "Best results for:\n temperature = " + std::to_string(resultTime) + "\n pressure = " + std::to_string(resultPressure)
		+ "\n time = " + std::to_string(resultTime);
	MessageBox(hWnd1, (char*)calculationResultReturn.c_str(),
		"", MB_OK | MB_ICONWARNING);
}

void Iteratiron_method::Method()
{
	double result1, result2, result3;
	double temperature1, temperature2, temperature3;
	double newResultTemperature;
	double pressure1, pressure2, pressure3;
	double newResultPressure;
	double time1, time2, time3;
	double newResultTime;
	double weightTemperature = 0, weightPressure = 0, weightTime = 0;
	double weightTemperature1 = 0, weightPressure1 = 0, weightTime1 = 0;
	double weightTemperature2 = 0, weightPressure2 = 0, weightTime2 = 0;
	double newWeightTemperature, newWeightPressure, newWeightTime;
	double delError = 1000;
	double Error1, Error2, Error3;

	for (int i = 0; i < 3; i++)
	{
		while (delError > 0.001)
		{
			result1 = atof(outputInfoName(1 + i * 3)) / 100;
			result2 = atof(outputInfoName(2 + i * 3)) / 100;
			result3 = atof(outputInfoName(3 + i * 3)) / 100;
			temperature1 = atof(outputInfoTemperature(1 + i * 3));
			temperature2 = atof(outputInfoTemperature(2 + i * 3));
			temperature3 = atof(outputInfoTemperature(3 + i * 3));
			pressure1 = atof(outputInfoPressure(1 + i * 3));
			pressure2 = atof(outputInfoPressure(2 + i * 3));
			pressure3 = atof(outputInfoPressure(3 + i * 3));
			time1 = atof(outputInfoPressure(1 + i * 3));
			time2 = atof(outputInfoPressure(2 + i * 3));
			time3 = atof(outputInfoPressure(3 + i * 3));
			if (i == 0)
			{
				newWeightTemperature = (result1 - (pressure1 * weightPressure) - (time1 * weightTime)) / temperature1;
				newWeightPressure = (result2 - (temperature2 * weightTemperature) - (time2 * weightTime)) / pressure2;
				newWeightTime = (result3 - (temperature3 * weightTemperature) - (pressure3 * weightPressure)) / time3;
				weightTemperature = newWeightTemperature;
				weightPressure = newWeightPressure;
				weightTime = newWeightTime;
				Error1 = abs(weightTemperature - newWeightTemperature);
				Error2 = abs(weightPressure - newWeightPressure);
				Error3 = abs(weightTime - newWeightTime);
			}
			else if (i == 1)
			{
				newWeightTemperature = (result1 - (pressure1 * weightPressure1) - (time1 * weightTime1)) / temperature1;
				newWeightPressure = (result2 - (temperature2 * weightTemperature1) - (time2 * weightTime1)) / pressure2;
				newWeightTime = (result3 - (temperature3 * weightTemperature1) - (pressure3 * weightPressure1)) / time3;
				weightTemperature1 = newWeightTemperature;
				weightPressure1 = newWeightPressure;
				weightTime1 = newWeightTime;
				Error1 = abs(weightTemperature1 - newWeightTemperature);
				Error2 = abs(weightPressure1 - newWeightPressure);
				Error3 = abs(weightTime1 - newWeightTime);
			}
			else if (i == 2)
			{
				newWeightTemperature = (result1 - (pressure1 * weightPressure2) - (time1 * weightTime2)) / temperature1;
				newWeightPressure = (result2 - (temperature2 * weightTemperature2) - (time2 * weightTime2)) / pressure2;
				newWeightTime = (result3 - (temperature3 * weightTemperature2) - (pressure3 * weightPressure2)) / time3;
				weightTemperature2 = newWeightTemperature;
				weightPressure2 = newWeightPressure;
				weightTime2 = newWeightTime;
				Error1 = abs(weightTemperature2 - newWeightTemperature);
				Error2 = abs(weightPressure2 - newWeightPressure);
				Error3 = abs(weightTime2 - newWeightTime);
			}

			if (Error1 > Error2 && Error1 > Error3)
			{
				delError = Error1;
			}
			else if (Error2 > Error3)
			{
				delError = Error2;
			}
			else
			{
				delError = Error3;
			}

		}
	}
	delError = 1000;
	while (delError > 0.25)
	{
		newResultTemperature = (1 - (resultPressure * weightPressure) - (resultTime * weightTime));
		newResultPressure = (1 - (resultTemperature * weightTemperature1) - (resultTime * weightTime1));
		newResultTime = (1 - (newResultPressure * weightPressure2) - (resultTemperature * weightTemperature2));
		Error1 = abs(resultTemperature - newResultTime);
		Error2 = abs(resultPressure - newResultPressure);
		Error3 = abs(resultTemperature - newResultTemperature);
		resultTime = newResultTime;
		resultPressure = newResultPressure;
		resultTemperature = newResultTemperature;

		if (Error1 > Error2 && Error1 > Error3)
		{
			delError = Error1;
		}
		else if (Error2 > Error3)
		{
			delError = Error2;
		}
		else
		{
			delError = Error3;
		}

	}

}
