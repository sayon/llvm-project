//===-- BogusSubtarget.cpp - Bogus Subtarget Information --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Bogus specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "Bogus.h"
#include "BogusSubtarget.h"
#include "BogusMachineFunction.h"
#include "BogusRegisterInfo.h"
#include "BogusTargetMachine.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "bogus"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "BogusGenSubtargetInfo.inc"

BogusSubtarget::BogusSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                               const TargetMachine &TM)
  : BogusGenSubtargetInfo(TT, CPU, "", FS),
      TSInfo(),
      InstrInfo(initializeSubtargetDependencies(TT, CPU, FS, TM)),
      FrameLowering(*this),
      TLInfo(TM, *this),
      RegInfo(*this) { }


BogusSubtarget &
BogusSubtarget::initializeSubtargetDependencies(const Triple &TT, StringRef CPU,
                                                StringRef FS,
                                                const TargetMachine &TM) {
  StringRef CPUName = CPU;
  if (CPUName.empty())
    CPUName = "generic";

  // Parse features string.
  ParseSubtargetFeatures(CPUName, "bogus subtarget", FS);

  return *this;
}
