#ifndef EELedTask_H
#define EELedTask_H

/*
 * \file EELedTask.h
 *
 * \author G. Della Ricca
 *
*/

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/EcalRawData/interface/EcalRawDataCollections.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

class MonitorElement;
class DQMStore;

class EELedTask: public edm::EDAnalyzer{

public:

/// Constructor
EELedTask(const edm::ParameterSet& ps);

/// Destructor
virtual ~EELedTask();

protected:

/// Analyze
void analyze(const edm::Event& e, const edm::EventSetup& c);

/// BeginJob
void beginJob(void);

/// EndJob
void endJob(void);

/// BeginRun
void beginRun(const edm::Run & r, const edm::EventSetup & c);

/// EndRun
void endRun(const edm::Run & r, const edm::EventSetup & c);

/// Reset
void reset(void);

/// Setup
void setup(void);

/// Cleanup
void cleanup(void);

private:

int ievt_;

DQMStore* dqmStore_;

std::string prefixME_;

bool enableCleanup_;

bool mergeRuns_;

edm::EDGetTokenT<EcalRawDataCollection> EcalRawDataCollection_;
edm::EDGetTokenT<EEDigiCollection> EEDigiCollection_;
edm::EDGetTokenT<EcalPnDiodeDigiCollection> EcalPnDiodeDigiCollection_;
edm::EDGetTokenT<EcalUncalibratedRecHitCollection> EcalUncalibratedRecHitCollection_;
std::vector<int> ledWavelengths_;

MonitorElement* meShapeMapL1_[18];
MonitorElement* meAmplMapL1_[18];
MonitorElement* meTimeMapL1_[18];
MonitorElement* meAmplPNMapL1_[18];
MonitorElement* mePnAmplMapG01L1_[18];
MonitorElement* mePnPedMapG01L1_[18];
MonitorElement* mePnAmplMapG16L1_[18];
MonitorElement* mePnPedMapG16L1_[18];

MonitorElement* meShapeMapL2_[18];
MonitorElement* meAmplMapL2_[18];
MonitorElement* meTimeMapL2_[18];
MonitorElement* meAmplPNMapL2_[18];
MonitorElement* mePnAmplMapG01L2_[18];
MonitorElement* mePnPedMapG01L2_[18];
MonitorElement* mePnAmplMapG16L2_[18];
MonitorElement* mePnPedMapG16L2_[18];

bool init_;

};

#endif
