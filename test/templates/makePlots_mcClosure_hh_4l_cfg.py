import FWCore.ParameterSet.Config as cms

import os

from tthAnalysis.HiggsToTauTau.makePlots_mcClosure_cfg import process

process.makePlots_mcClosure.processesBackground = cms.vstring(
    "TT",
    "TTW",
    "TTZ",
    "EWK",
    "Rares",
    "fakes_data"
)
process.makePlots_mcClosure.processSignal = cms.string("signal")

process.makePlots_mcClosure.categories = cms.VPSet(
    cms.PSet(
        name = cms.string("4l_OS_Fakeable_mcClosure_wFakeRateWeights"),
        label = cms.string("4l")
    )
)

process.makePlots.distributions.extend([
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/m4Vis'),
        xAxisTitle = cms.string('m_{HH}^{vis} [GeV]'),
        yAxisTitle = cms.string('dN/dm_{HH}^{vis} [1/GeV]')
    ),
    cms.PSet(
        histogramName = cms.string('sel/evt/$PROCESS/m4'),
        xAxisTitle = cms.string('m_{HH} [GeV]'),
        yAxisTitle = cms.string('dN/dm_{HH} [1/GeV]')
    )
])
