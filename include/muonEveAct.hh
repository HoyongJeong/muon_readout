#ifndef MUONEVEACT_h
#define MUONEVEACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   muonEveAct.hh for Liz's 2018 winter project                              //
//                                                                            //
//   This file is a header for muonEveAct class. User can add user-defined    //
// event action in this class.                                                //
//                                                                            //
//                    - 24. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "TH1D.h"

#include "G4UserEventAction.hh"
#include "G4String.hh"

class G4Event;

class muonEveAct : public G4UserEventAction
{
  public:
	muonEveAct();
	virtual ~muonEveAct();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);

	void FillHist(G4double t, G4double eDep);

	void CalculateLifetime();
	
  private:
	G4double m_Threshold;
	G4int m_SamplingRate;
	G4double m_MaxTime;
	G4int m_NBin;
	TH1D* m_Hist;
	G4bool m_Decay;
	G4double m_Lifetime;
};

#endif
