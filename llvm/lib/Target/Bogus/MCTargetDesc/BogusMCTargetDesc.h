#pragma once

#include "BogusBaseInfo.h"

// Defines symbolic names for Bogus registers. This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "BogusGenRegisterInfo.inc"

// Defines symbolic names for the Bogus instructions.
#define GET_INSTRINFO_ENUM
#include "BogusGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "BogusGenSubtargetInfo.inc"
