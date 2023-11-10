#include "BogusAsmBackend.h"
#include "llvm/ADT/APInt.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCAsmLayout.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/LEB128.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;


std::unique_ptr<MCObjectTargetWriter>
BogusAsmBackend::createObjectTargetWriter() const {
  return createBogusELFObjectWriter(0, true);
}

MCAsmBackend *llvm::createBogusAsmBackend(const Target &T,
                                          const MCSubtargetInfo &STI,
                                          const MCRegisterInfo &MRI,
                                          const MCTargetOptions &Options) {
  const Triple &TT = STI.getTargetTriple();
  return new BogusAsmBackend(STI);
}

bool BogusAsmBackend::writeNopData(raw_ostream &OS, uint64_t Count,
                  const MCSubtargetInfo *STI) const {
    for (uint64_t i = 0 ; i < Count; ++i ) {
      OS.write("\0", 1);
    }
    return true;
  }
