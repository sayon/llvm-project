//===-- BogusMCTargetDesc.cpp - Bogus Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Bogus specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "BogusMCTargetDesc.h"
#include "BogusInstPrinter.h"
#include "BogusMCAsmInfo.h"
#include "TargetInfo/BogusTargetInfo.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "BogusGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "BogusGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "BogusGenRegisterInfo.inc"

static MCInstrInfo *createBogusMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitBogusMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createBogusMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  return X;
}

static MCSubtargetInfo *
createBogusMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  StringRef CPUName = CPU.empty()? "generic": CPU;
  return createBogusMCSubtargetInfoImpl(TT, CPUName, CPUName, FS);
}

static MCInstPrinter *createBogusMCInstPrinter(const Triple &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
  return new BogusInstPrinter(MAI, MII, MRI);
}

static MCAsmInfo *createBogusMCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TT,
                                       const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new BogusMCAsmInfo(TT);

  unsigned WP = MRI.getDwarfRegNum(Bogus::X2, true);
  MCCFIInstruction Inst = MCCFIInstruction::createDefCfaRegister(nullptr, WP, SMLoc::getFromPointer(nullptr));
  MAI->addInitialFrameState(Inst);

  return MAI;
}

// std::pair<const char *, uint64_t> BogusInstPrinter::getMnemonic(const MCInst *MI) {
//   static const uint64_t BitsLeft = 0;
//   return std::make_pair("no-mnemonic", BitsLeft);
// }


  extern "C" void LLVMInitializeBogusTargetMC() {
  for (Target *T : {&getTheBogusTarget()}) {
    // Register the MC asm info.
    TargetRegistry::RegisterMCAsmInfo(*T, createBogusMCAsmInfo);

    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(*T, createBogusMCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(*T, createBogusMCRegisterInfo);

    // Register the MC subtarget info.
    TargetRegistry::RegisterMCSubtargetInfo(*T, createBogusMCSubtargetInfo);

    // Register the MCInstPrinter.
    TargetRegistry::RegisterMCInstPrinter(*T, createBogusMCInstPrinter);
  }
}
