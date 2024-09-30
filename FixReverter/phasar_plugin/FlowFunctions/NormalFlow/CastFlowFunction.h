#ifndef CASTFLOWFUNCTION_H_
#define CASTFLOWFUNCTION_H_

#include "Utils/Utils.h"
#include "Utils/Logs.h"

struct CastFlowFunction : psr::FlowFunction<DependenceAnalyzer::d_t> {
private:
  GlobalDataHolder *GlobalData;
  const llvm::CastInst *CastInst;
  psr::FlowFactManager<MyFlowFact> &FFManager;

public:
  CastFlowFunction(
    GlobalDataHolder *GlobalData,
    const llvm::CastInst *CastInst,
    psr::FlowFactManager<MyFlowFact> &FFManager) : GlobalData(GlobalData), CastInst(CastInst), FFManager(FFManager) {}

  std::set<DependenceAnalyzer::d_t> computeTargets(DependenceAnalyzer::d_t source) override {
    if (GlobalData->timeLimit != -1) {
      time_t now = time(0);
      double diff = difftime(now, GlobalData->startTime);
      if (((int) diff) % 30 <= 1 || ((int) diff) % 30 >= 29) {
        llvm::outs() << "Analyzer - [DEBUG] Time elapsed: " << diff << " seconds [" << diff / GlobalData->timeLimit * 100 << "%]\n";
      }
      if (diff > GlobalData->timeLimit) {
        llvm::outs() << "Analyzer - [DEBUG] Time limit reached, skip this flow\n";
        return {};
      }
    }
    if (source->as<MyFlowFact>()->isZero()) {
      return {source};
    }
    auto SourceValue = source->as<MyFlowFact>()->get().value();
    logFromToFlow(llvm::outs(), SourceValue, CastInst, "Cast");
    auto Operand = CastInst->getOperand(0);
    if (SourceValue == Operand) {
      updateTaintPaths(std::make_shared<ValueNode>(CastInst), std::make_shared<ValueNode>(SourceValue), GlobalData->TaintPaths);
      logGeneralInfo(llvm::outs(), "Analyzer - [DEBUG] Cast flow: connected value operand");
      return FFManager.getOrCreateFlowFacts(SourceValue, CastInst);
    } else {
      return {source};
    }
  }
};

#endif
