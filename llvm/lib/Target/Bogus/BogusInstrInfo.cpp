#include "BogusInstrInfo.h"

#include "BogusTargetMachine.h"
#include "BogusMachineFunction.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

#define DEBUG_TYPE "riscw-instrinfo"

#define GET_INSTRINFO_CTOR_DTOR
#include "BogusGenInstrInfo.inc"

BogusInstrInfo::BogusInstrInfo(const BogusSubtarget &STI)
  : BogusGenInstrInfo(), Subtarget(STI)
{
}
