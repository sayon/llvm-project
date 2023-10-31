#pragma once

#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"

namespace llvm {

class formatted_raw_ostream;

enum class BogusOptionArchArgType {
  Full,
  Plus,
  Minus,
};

struct BogusOptionArchArg {
  BogusOptionArchArgType Type;
  std::string Value;

  BogusOptionArchArg(BogusOptionArchArgType Type, std::string Value)
      : Type(Type), Value(Value) {}
};

class BogusTargetStreamer : public MCTargetStreamer {
  // BogusABI::ABI TargetABI = BogusABI::ABI_Unknown;

public:
  BogusTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
  // void finish() override;
  // virtual void reset();

  // virtual void emitDirectiveOptionPush();
  // virtual void emitDirectiveOptionPop();
  // virtual void emitDirectiveOptionPIC();
  // virtual void emitDirectiveOptionNoPIC();
  // virtual void emitDirectiveOptionRVC();
  // virtual void emitDirectiveOptionNoRVC();
  // virtual void emitDirectiveOptionRelax();
  // virtual void emitDirectiveOptionNoRelax();
  // virtual void emitDirectiveOptionArch(ArrayRef<BogusOptionArchArg> Args);
  // virtual void emitDirectiveVariantCC(MCSymbol &Symbol);
  // virtual void emitAttribute(unsigned Attribute, unsigned Value);
  // virtual void finishAttributeSection();
  // virtual void emitTextAttribute(unsigned Attribute, StringRef String);
  // virtual void emitIntTextAttribute(unsigned Attribute, unsigned IntValue,
  //                                   StringRef StringValue);

  // void emitTargetAttributes(const MCSubtargetInfo &STI, bool EmitStackAlign);
  // void setTargetABI(BogusABI::ABI ABI);
  // BogusABI::ABI getTargetABI() const { return TargetABI; }
};

// This part is for ascii assembly output
class BogusTargetAsmStreamer : public BogusTargetStreamer {
  formatted_raw_ostream &OS;

  // void finishAttributeSection() override;
  // void emitAttribute(unsigned Attribute, unsigned Value) override;
  // void emitTextAttribute(unsigned Attribute, StringRef String) override;
  // void emitIntTextAttribute(unsigned Attribute, unsigned IntValue,
  //                           StringRef StringValue) override;

public:
  BogusTargetAsmStreamer(MCStreamer &S, formatted_raw_ostream &OS) : BogusTargetStreamer(S), OS(OS) {}

  // void emitDirectiveOptionPush() override;
  // void emitDirectiveOptionPop() override;
  // void emitDirectiveOptionPIC() override;
  // void emitDirectiveOptionNoPIC() override;
  // void emitDirectiveOptionRVC() override;
  // void emitDirectiveOptionNoRVC() override;
  // void emitDirectiveOptionRelax() override;
  // void emitDirectiveOptionNoRelax() override;
  // void emitDirectiveOptionArch(ArrayRef<BogusOptionArchArg> Args) override;
  // void emitDirectiveVariantCC(MCSymbol &Symbol) override;
};

} // namespace llvm
