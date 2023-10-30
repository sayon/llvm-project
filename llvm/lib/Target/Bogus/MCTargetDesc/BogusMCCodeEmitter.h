#ifndef LLVM_LIB_TARGET_BOGUS_MCTARGETDESC_BOGUSMCCODEEMITTER_H
#define LLVM_LIB_TARGET_BOGUS_MCTARGETDESC_BOGUSMCCODEEMITTER_H

#include "llvm/MC/MCCodeEmitter.h"
#include <cstdint>

namespace llvm {

class MCContext;
class MCExpr;
class MCFixup;
class MCInst;
class MCInstrInfo;
class MCOperand;
class MCSubtargetInfo;
class raw_ostream;

class BogusMCCodeEmitter : public MCCodeEmitter {
  const MCInstrInfo &MCII;
  MCContext &Ctx;

public:
  BogusMCCodeEmitter(const MCInstrInfo &mcii, MCContext &Ctx)
      : MCII(mcii), Ctx(Ctx) {}

  BogusMCCodeEmitter(const BogusMCCodeEmitter &) = delete;
  BogusMCCodeEmitter &operator=(const BogusMCCodeEmitter &) = delete;
  ~BogusMCCodeEmitter() override = default;

  void EmitByte(unsigned char C, raw_ostream &OS) const;

  void encodeInstruction(const MCInst &MI, SmallVectorImpl<char> &CB,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  // getBinaryCodeForInstr - TableGen'erated function for getting the
  // binary encoding for an instruction.
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_BOGUS_MCTARGETDESC_BOGUSMCCODEEMITTER_H
