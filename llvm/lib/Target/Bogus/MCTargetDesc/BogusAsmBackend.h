#pragma once

#include "MCTargetDesc/BogusBaseInfo.h"
#include "MCTargetDesc/BogusMCTargetDesc.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"

namespace llvm {
class MCAssembler;
class MCObjectTargetWriter;
class raw_ostream;

class BogusAsmBackend : public MCAsmBackend {
  const MCSubtargetInfo &STI;

public:
  BogusAsmBackend(const MCSubtargetInfo &STI)
      : MCAsmBackend(llvm::endianness::little), STI(STI) {}

  ~BogusAsmBackend() override = default;

  // Return Size with extra Nop Bytes for alignment directive in code section.
  bool shouldInsertExtraNopBytesForCodeAlign(const MCAlignFragment &AF,
                                             unsigned &Size) override { return false; }

  // Insert target specific fixup type for alignment directive in code section.
  bool shouldInsertFixupForCodeAlign(MCAssembler &Asm,
                                     const MCAsmLayout &Layout,
                                     MCAlignFragment &AF) override { return false; }

  bool evaluateTargetFixup(const MCAssembler &Asm, const MCAsmLayout &Layout,
                           const MCFixup &Fixup, const MCFragment *DF,
                           const MCValue &Target, uint64_t &Value,
                           bool &WasForced) override { return false; }

  bool handleAddSubRelocations(const MCAsmLayout &Layout, const MCFragment &F,
                               const MCFixup &Fixup, const MCValue &Target,
                               uint64_t &FixedValue) const override { return false; }

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved,
                  const MCSubtargetInfo *STI) const override { }

  std::unique_ptr<MCObjectTargetWriter>
  createObjectTargetWriter() const override;

  bool shouldForceRelocation(const MCAssembler &Asm, const MCFixup &Fixup,
                             const MCValue &Target) override { return false; }

  bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                            const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override {
    llvm_unreachable("Handled by fixupNeedsRelaxationAdvanced");
  }

  bool fixupNeedsRelaxationAdvanced(const MCFixup &Fixup, bool Resolved,
                                    uint64_t Value,
                                    const MCRelaxableFragment *DF,
                                    const MCAsmLayout &Layout,
                                    const bool WasForced) const override { return false; }

  std::optional<MCFixupKind> getFixupKind(StringRef Name) const override { return std::nullopt; }

  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override { return MCAsmBackend::getFixupKindInfo(FK_NONE); }

  bool mayNeedRelaxation(const MCInst &Inst,
                         const MCSubtargetInfo &STI) const override { return false; }

  void relaxInstruction(MCInst &Inst,
                        const MCSubtargetInfo &STI) const override { }

  bool relaxDwarfLineAddr(MCDwarfLineAddrFragment &DF, MCAsmLayout &Layout,
                          bool &WasRelaxed) const override { return false; }
  bool relaxDwarfCFA(MCDwarfCallFrameFragment &DF, MCAsmLayout &Layout,
                     bool &WasRelaxed) const override { return false; }

  bool writeNopData(raw_ostream &OS, uint64_t Count,
                    const MCSubtargetInfo *STI) const override { return false; }

  unsigned getNumFixupKinds() const override { return 0; }
};
} // namespace llvm
