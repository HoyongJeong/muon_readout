////////////////////////////////////////////////////////////////////////////////
//   muonEveAct.cc for Liz's 2018 winter project                              //
//                                                                            //
//   Definitions of muonEveAct class's member functions. Details of user      //
// actions are here.                                                          //
//                                                                            //
//                    - 24. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "muonEveAct.hh"
#include "muonAna.hh"

#include "G4Event.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
muonEveAct::muonEveAct()
{
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
muonEveAct::~muonEveAct()
{
}

//////////////////////////////////////////////////
//   Begin of evect action                      //
//////////////////////////////////////////////////
void muonEveAct::BeginOfEventAction(const G4Event* anEvent)
{
	// Initialize
	m_Hist = new TH1D();
	m_Threshold    = 1.0; // in MeV
	m_SamplingRate = 500; // in MHz
	m_MaxTime      =  20; // in us
	m_NBin = (G4int)m_SamplingRate*m_MaxTime;
	m_Hist -> SetBins(m_NBin, 0, m_MaxTime);
	m_Decay = false;

//	G4cout << anEvent -> GetEventID() << G4endl;
}

//////////////////////////////////////////////////
//   End of evect action                        //
//////////////////////////////////////////////////
void muonEveAct::EndOfEventAction(const G4Event* anEvent)
{
	// Get analysis manager
	G4AnalysisManager* AM = G4AnalysisManager::Instance();

	// Calculate
	CalculateLifetime();
	delete m_Hist;

	// Fill ntuple with result
	if ( m_Decay )
	{
		G4int eID = anEvent -> GetEventID();
		AM -> FillNtupleIColumn(0, eID);
		AM -> FillNtupleDColumn(1, m_Lifetime);
		AM -> AddNtupleRow();
	}
}

//////////////////////////////////////////////////
//   Add energy deposition at given time        //
//////////////////////////////////////////////////
void muonEveAct::FillHist(G4double t, G4double eDep)
{
	m_Hist -> Fill(t, eDep);
}

//////////////////////////////////////////////////
//   Calculate lifetime                         //
//////////////////////////////////////////////////
void muonEveAct::CalculateLifetime()
{
	// This function calculate lifetime from measure result.

	// Count number of peaks
	G4int nPeak = 0;
	G4double nowtime;
	G4double previous = 0.0;
	G4double current;
	G4double tFirst, tSecond;
	for ( G4int i = 1; i <= m_NBin; i++ )
	{
		nowtime = m_Hist -> GetBinCenter(i);
		current = m_Hist -> GetBinContent(i);
		// Signal detected!
		if ( (previous < m_Threshold) && (current >= m_Threshold) )
		{
			// First peak
			if ( nPeak == 0 )
			{
				tFirst = nowtime;
				nPeak++;
			}
			// Second peak
			else if ( nPeak == 1 )
			{
				tSecond = nowtime;
				nPeak++;
				break;
			}
		}
		previous = current;
	}

	// If at leaat two peaks go over threshold, the event is regarded as a decay.
	if ( nPeak == 2 )
	{
		m_Decay = true;
		m_Lifetime = tSecond - tFirst;
	}
}
