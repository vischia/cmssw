#ifndef CSCCLCTDigiValidation_H
#define CSCCLCTDigiValidation_H

#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "DataFormats/CSCDigi/interface/CSCCLCTDigi.h"
#include "DataFormats/CSCDigi/interface/CSCCLCTDigiCollection.h"
#include "Validation/MuonCSCDigis/interface/CSCBaseValidation.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

class CSCCLCTDigiValidation : public CSCBaseValidation
{
public:
  CSCCLCTDigiValidation(DQMStore* dbe,
                        const edm::InputTag & inputTag,
                        edm::ConsumesCollector && iC);
  ~CSCCLCTDigiValidation();
  void analyze(const edm::Event&, const edm::EventSetup&);
  void endJob() {}

private:
  edm::EDGetTokenT<CSCCLCTDigiCollection> clcts_Token_;

  MonitorElement* theTimeBinPlots[10];
  MonitorElement* theNDigisPerLayerPlots[10];
  MonitorElement* theNDigisPerEventPlot;

};

#endif

