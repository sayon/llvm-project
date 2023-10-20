//===-- BogusInstrInfo.cpp - Bogus Instruction Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Bogus implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

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
    : BogusGenInstrInfo(Bogus::ADJCALLSTACKDOWN, Bogus::ADJCALLSTACKUP),
      Subtarget(STI)
{
}
