#pragma once
#include "BogusTargetStreamer.h"
#include "llvm/MC/MCELFStreamer.h"

using namespace llvm;

class BogusELFStreamer : public MCELFStreamer {
  // void reset() override;
  // void emitDataMappingSymbol();
  // void emitInstructionsMappingSymbol();
  // void emitMappingSymbol(StringRef Name);

  // enum ElfMappingSymbol { EMS_None, EMS_Instructions, EMS_Data };

  // int64_t MappingSymbolCounter = 0;
  // DenseMap<const MCSection *, ElfMappingSymbol> LastMappingSymbols;
  // ElfMappingSymbol LastEMS = EMS_None;

public:
  BogusELFStreamer(MCContext &C, std::unique_ptr<MCAsmBackend> MAB,
                   std::unique_ptr<MCObjectWriter> MOW,
                   std::unique_ptr<MCCodeEmitter> MCE)
      : MCELFStreamer(C, std::move(MAB), std::move(MOW), std::move(MCE)) {}

  // void changeSection(MCSection *Section, const MCExpr *Subsection) override;
  // void emitInstruction(const MCInst &Inst, const MCSubtargetInfo &STI) override;
  // void emitBytes(StringRef Data) override;
  // void emitFill(const MCExpr &NumBytes, uint64_t FillValue, SMLoc Loc) override;
  // void emitValueImpl(const MCExpr *Value, unsigned Size, SMLoc Loc) override;
};

namespace llvm {

class BogusTargetELFStreamer : public BogusTargetStreamer {
private:
  StringRef CurrentVendor;

  MCSection *AttributeSection = nullptr;
  const MCSubtargetInfo &STI;

  // void emitAttribute(unsigned Attribute, unsigned Value) override;
  // void emitTextAttribute(unsigned Attribute, StringRef String) override;
  // void emitIntTextAttribute(unsigned Attribute, unsigned IntValue,
  //                           StringRef StringValue) override;
  // void finishAttributeSection() override;

  // void reset() override;

public:
  BogusELFStreamer &getStreamer();
  BogusTargetELFStreamer(MCStreamer &S, const MCSubtargetInfo &STI);

  // void emitDirectiveOptionPush() override;
  // void emitDirectiveOptionPop() override;
  // void emitDirectiveOptionPIC() override;
  // void emitDirectiveOptionNoPIC() override;
  // void emitDirectiveOptionRVC() override;
  // void emitDirectiveOptionNoRVC() override;
  // void emitDirectiveOptionRelax() override;
  // void emitDirectiveOptionNoRelax() override;
  // void emitDirectiveVariantCC(MCSymbol &Symbol) override;

  void finish() override {} //
};

MCELFStreamer *createBogusELFStreamer(MCContext &C,
                                      std::unique_ptr<MCAsmBackend> MAB,
                                      std::unique_ptr<MCObjectWriter> MOW,
                                      std::unique_ptr<MCCodeEmitter> MCE,
                                      bool RelaxAll);
}
