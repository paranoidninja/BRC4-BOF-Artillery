#pragma once

#include "beacon.h"

#define PRINT(format, ...) BeaconPrintf(CALLBACK_OUTPUT, format, ##__VA_ARGS__)
#define EPRINT(format, ...) BeaconPrintf(CALLBACK_ERROR, format, ##__VA_ARGS__)