// -*- C++ -*-
// Framework
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

class L3MuonCleaner : public edm::EDProducer {
 public:
  L3MuonCleaner(const edm::ParameterSet&);
  virtual ~L3MuonCleaner(){}
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
 private:
  edm::InputTag m_input; 
  int m_minTrkHits;
  int m_minMuonHits;
  double m_maxNormalizedChi2;
};

L3MuonCleaner::L3MuonCleaner(const edm::ParameterSet& parameterSet){
  m_input = parameterSet.getParameter<edm::InputTag>("input");
  m_minTrkHits = parameterSet.getParameter<int>("minTrkHits");
  m_minMuonHits = parameterSet.getParameter<int>("minMuonHits");
  m_maxNormalizedChi2 = parameterSet.getParameter<double>("maxNormalizedChi2");
  produces<reco::TrackCollection>();
}

void L3MuonCleaner::produce(edm::Event& event, const edm::EventSetup&){
  edm::Handle<reco::TrackCollection> tracks; 
  event.getByLabel(m_input,tracks);
  std::auto_ptr<reco::TrackCollection> outTracks( new reco::TrackCollection() );
  for ( reco::TrackCollection::const_iterator trk=tracks->begin(); trk!=tracks->end(); ++trk ){
    if (trk->normalizedChi2()>m_maxNormalizedChi2) continue;
    if (trk->hitPattern().numberOfValidTrackerHits()<m_minTrkHits) continue;
    if (trk->hitPattern().numberOfValidMuonHits()<m_minMuonHits) continue;
    outTracks->push_back(*trk);
  }
  event.put(outTracks);
}
DEFINE_FWK_MODULE(L3MuonCleaner);
