#include <iostream>
#include <fstream>
#include "AudioFile.h"

// Turn seconds into a string literal that spice understands
// We're using relative measurements so prepend the string with a +
// e.g. 0.00001s -> +10u
std::string getTimeStep(double seconds)
{
	int ACC = 0;
	std::string timeStep = "";

	while (seconds < 1)
	{
		seconds *= 1000;
		ACC++;
	}
	switch (ACC)
	{
	case 1:	// mili
		timeStep = "+" + std::to_string(seconds) + "m ";
		break;
	case 2:	// micro
		timeStep = "+" + std::to_string(seconds) + "u ";
		break;
	case 3:	// nano
		timeStep = "+" + std::to_string(seconds) + "n ";
		break;
	default: // seconds
		timeStep = "+" + std::to_string(seconds) + "s ";
		break;
	}

	return timeStep;
}

int main(int argc, char* argv[])
{
	std::string filePath = argv[1];
	AudioFile<float> WAVFile;
	std::ofstream PWLFile;

	WAVFile.load(filePath);

	int numSamples			= WAVFile.getNumSamplesPerChannel();
	double lengthInSeconds	= WAVFile.getLengthInSeconds();
	double secondsPerSample	= lengthInSeconds / numSamples;
	std::string timeStepStr = getTimeStep(secondsPerSample);

	PWLFile.open("./PWL.txt");

	for (int i = 0; i < numSamples; i++)
	{
		if (i == 0)
		{
			PWLFile << "0 ";
		}
		else
		{
			PWLFile << timeStepStr;
		}

		PWLFile << WAVFile.samples[0][i];
		PWLFile << "\n";
	}

	return 0;
}