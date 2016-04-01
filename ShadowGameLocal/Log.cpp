#include <stdlib.h>
#include <stdio.h>
#include "log.h"

bool LogCreated = false;

void Log(std::string message)
{
	FILE *file;

	if (!LogCreated) {
		file = fopen(LOGFILE, "w");
		LogCreated = true;
	}
	else
		file = fopen(LOGFILE, "a");

	if (file == NULL) {
		if (LogCreated)
			LogCreated = false;
		return;
	}
	else
	{
		message += "\n";
		fputs(message.c_str(), file);
		fclose(file);
	}

	if (file)
		fclose(file);
}

void LogErr(std::string message)
{
	Log(message);
	Log("\n");
	// Bad thing
}