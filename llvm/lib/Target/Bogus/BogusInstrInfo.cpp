#include "BogusInstrInfo.h"

#include "BogusMachineFunction.h"
#include "BogusTargetMachine.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define DEBUG_TYPE "bogus-instrinfo"

#define GET_INSTRINFO_CTOR_DTOR
#include "BogusGenInstrInfo.inc"

BogusInstrInfo::BogusInstrInfo(const BogusSubtarget &STI)
    : BogusGenInstrInfo(), Subtarget(STI) {}
