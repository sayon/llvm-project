//===-- BogusTargetMachine.cpp - Define TargetMachine for Bogus -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Bogus target spec.
//
//===----------------------------------------------------------------------===//

#include "BogusTargetMachine.h"
#include "BogusISelDAGToDAG.h"
#include "BogusSubtarget.h"
#include "BogusTargetObjectFile.h"
#include "TargetInfo/BogusTargetInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeBogusTarget() {
  // Register the target.
  //- Little endian Target Machine
  RegisterTargetMachine<BogusTargetMachine> X(getTheBogusTarget());
}

static std::string computeDataLayout() {
  std::string Ret =
  // Little endian
  "e"
  // ELF name mangling
  "-m:e"
  // 32-bit pointers, 32-bit aligned
  "-p:32:32"
  // 64-bit integers, 64 bit aligned
  "-i64:64"
  // 32-bit native integer width i.e register are 32-bit
  "-n32"
  // 128-bit natural stack alignment
  "-S128";

  return Ret;
}

static Reloc::Model getEffectiveRelocModel(std::optional<CodeModel::Model> CM,
                                           std::optional<Reloc::Model> RM) {
  if (!RM.has_value())
    return Reloc::Static;
  return *RM;
}

BogusTargetMachine::BogusTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL,
                                       bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(), TT, CPU, FS, Options,
                        getEffectiveRelocModel(CM, RM),
                        getEffectiveCodeModel(CM, CodeModel::Medium), OL),
      TLOF(std::make_unique<BogusTargetObjectFile>()) {
  // initAsmInfo will display features by llc -march=riscw on 3.7
  initAsmInfo();
}

const BogusSubtarget *
BogusTargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  std::string CPU = !CPUAttr.hasAttribute(Attribute::None)
                        ? CPUAttr.getValueAsString().str()
                        : TargetCPU;
  std::string FS = !FSAttr.hasAttribute(Attribute::None)
                       ? FSAttr.getValueAsString().str()
                       : TargetFS;

  auto &I = SubtargetMap[CPU + FS];
  if (!I) {
    // This needs to be done before we create a new subtarget since any
    // creation will depend on the TM and the code generation flags on the
    // function that reside in TargetOptions.
    resetTargetOptions(F);
    I = std::make_unique<BogusSubtarget>(TargetTriple, CPU, FS, *this);
  }
  return I.get();
}

namespace {
class BogusPassConfig : public TargetPassConfig {
public:
  BogusPassConfig(BogusTargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  BogusTargetMachine &getBogusTargetMachine() const {
    return getTM<BogusTargetMachine>();
  }

  bool addInstSelector() override;
  void addPreEmitPass() override;
};
}

TargetPassConfig *BogusTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new BogusPassConfig(*this, PM);
}

// Install an instruction selector pass using
// the ISelDag to gen Bogus code.
bool BogusPassConfig::addInstSelector() {
  addPass(new BogusDAGToDAGISel(getBogusTargetMachine(), getOptLevel()));
  return false;
}

// Implemented by targets that want to run passes immediately before
// machine code is emitted. return true if -print-machineinstrs should
// print out the code after the passes.
void BogusPassConfig::addPreEmitPass() {
}
