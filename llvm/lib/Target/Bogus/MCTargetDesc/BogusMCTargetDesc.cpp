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
#include "BogusBaseInfo.h"
#include "BogusELFStreamer.h"
#include "BogusInstPrinter.h"
#include "BogusMCAsmInfo.h"
#include "BogusMCCodeEmitter.h"
#include "BogusTargetStreamer.h"
#include "TargetInfo/BogusTargetInfo.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
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

namespace {
MCStreamer *createBogusELFStreamer(const Triple &T, MCContext &Context,
                                   std::unique_ptr<MCAsmBackend> &&MAB,
                                   std::unique_ptr<MCObjectWriter> &&MOW,
                                   std::unique_ptr<MCCodeEmitter> &&MCE,
                                   bool RelaxAll) {
  return createBogusELFStreamer(Context, std::move(MAB), std::move(MOW),
                                std::move(MCE), RelaxAll);
}
MCTargetStreamer *
  createBogusObjectTargetStreamer(MCStreamer &S, const MCSubtargetInfo &STI) {
  const Triple &TT = STI.getTargetTriple();
  if (TT.isOSBinFormatELF())
    return new BogusTargetELFStreamer(S, STI);
  return nullptr;
}

static MCTargetStreamer *createBogusAsmTargetStreamer(MCStreamer &S,
                                                      formatted_raw_ostream &OS,
                                                      MCInstPrinter *InstPrint,
                                                      bool isVerboseAsm) {
  return new BogusTargetAsmStreamer(S, OS);
}

static MCTargetStreamer *createBogusNullTargetStreamer(MCStreamer &S) {
  return new BogusTargetStreamer(S);
}
} // namespace
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

    // Register the MCInstPrinter.
    TargetRegistry::RegisterMCCodeEmitter(*T, createBogusMCCodeEmitter);

    TargetRegistry::RegisterMCAsmBackend(*T, createBogusAsmBackend);

    TargetRegistry::RegisterELFStreamer(*T, createBogusELFStreamer);

    TargetRegistry::RegisterObjectTargetStreamer(*T, createBogusObjectTargetStreamer);

    TargetRegistry::RegisterAsmTargetStreamer(*T, createBogusAsmTargetStreamer);
    // Register the null target streamer.
    TargetRegistry::RegisterNullTargetStreamer(*T,
                                               createBogusNullTargetStreamer);
  }
}
