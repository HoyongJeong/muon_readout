#ifndef MUONSTEACT_h
#define MUONSTEACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   muonSteAct.hh for Liz's 2018 winter project                              //
//                                                                            //
//   This file is a header for muonSteAct class. User can add user-defined    //
// stepping action in this class. So this class works at every step.          //
// The most busiest class :)                                                  //
//                                                                            //
//                    - 24. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////i///////////////////////////////////////////////////////////////////////////

#include <map>

#include "G4UserSteppingAction.hh"

#include "muonEveAct.hh"

class muonEveAct;

class muonSteAct : public G4UserSteppingAction
{
  public:
	muonSteAct(muonEveAct* EA);
	virtual ~muonSteAct();

	virtual void UserSteppingAction(const G4Step*);

  private:
	muonEveAct* m_EA;
};

#endif
