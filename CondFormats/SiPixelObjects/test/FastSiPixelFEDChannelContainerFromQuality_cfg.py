import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("summary")

##
## MessageLogger
##
process.load('FWCore.MessageService.MessageLogger_cfi')   
process.MessageLogger.categories.append("FastSiPixelFEDChannelContainerFromQuality")  
process.MessageLogger.categories.append("SiPixelFEDChannelContainer")  
process.MessageLogger.destinations = cms.untracked.vstring("cout")
process.MessageLogger.cout = cms.untracked.PSet(
    threshold = cms.untracked.string("INFO"),
    default   = cms.untracked.PSet(limit = cms.untracked.int32(0)),                       
    FwkReport = cms.untracked.PSet(limit = cms.untracked.int32(-1),
                                   reportEvery = cms.untracked.int32(1000)
                                   ),                                                      
    FastSiPixelFEDChannelContainerFromQuality = cms.untracked.PSet( limit = cms.untracked.int32(-1)),
    SiPixelFEDChannelContainer           = cms.untracked.PSet( limit = cms.untracked.int32(-1))
    )
process.MessageLogger.statistics.append('cout')  
  
##
## Empty Source
##                                      
process.source = cms.Source("EmptySource",
    numberEventsInRun = cms.untracked.uint32(1),
    firstRun = cms.untracked.uint32(1)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)

##
## Output database (in this case local sqlite file)
##
process.load("CondCore.CondDB.CondDB_cfi")
process.CondDB.connect = 'sqlite_file:SiPixelStatusScenarios_2017StuckTBM.db'
process.PoolDBOutputService = cms.Service("PoolDBOutputService",
                                          process.CondDB,
                                          timetype = cms.untracked.string('runnumber'),
                                          toPut = cms.VPSet(cms.PSet(record = cms.string('SiPixelStatusScenariosRcd'),
                                                                     tag = cms.string('SiPixelFEDChannelContainer_StuckTBM_2017_v1_mc')
                                                                     )
                                                            )
                                          )

##
## Configuration of the module
##
process.load("CondFormats.SiPixelObjects.FastSiPixelFEDChannelContainerFromQuality_cfi")
process.FastSiPixelFEDChannelContainerFromQuality.qualityTagName  = "SiPixelQualityOffline_2017_threshold1percent_stuckTBM"
process.FastSiPixelFEDChannelContainerFromQuality.startIOV = 1268368267018245
process.FastSiPixelFEDChannelContainerFromQuality.endIOV   = 1318907147191631
process.FastSiPixelFEDChannelContainerFromQuality.output   = "summary2017_StuckTBM.txt"

#process.FastSiPixelFEDChannelContainerFromQuality.qualityTagName  = "SiPixelQualityOffline_2017_threshold1percent_prompt"
#process.FastSiPixelFEDChannelContainerFromQuality.startIOV = 1268368267018245
#process.FastSiPixelFEDChannelContainerFromQuality.endIOV   = 1318907147191657
#process.FastSiPixelFEDChannelContainerFromQuality.output   = "summary2017_Prompt.txt"

#process.FastSiPixelFEDChannelContainerFromQuality.qualityTagName  = "SiPixelQualityOffline_2017_threshold1percent_other"
#process.FastSiPixelFEDChannelContainerFromQuality.startIOV = 1268368267018245
#process.FastSiPixelFEDChannelContainerFromQuality.endIOV   = 1318907147191657
#process.FastSiPixelFEDChannelContainerFromQuality.output   = "summary2017_Other.txt"

process.p = cms.Path(process.FastSiPixelFEDChannelContainerFromQuality)





