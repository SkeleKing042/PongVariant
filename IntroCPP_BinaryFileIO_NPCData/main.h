#pragma once

#include "raylib.h"
#include <string>
#include <vector>
#include "DataFile.h"

using namespace std;

class main
{
public:
	main();

	void Draw(DataFile data, int currentRecordIdx);
};