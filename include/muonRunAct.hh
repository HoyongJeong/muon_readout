#ifndef MUONRUNACT_h
#define MUONRUNACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   muonRunAct.hh for Liz's 2018 winter project.                             //
//                                                                            //
//   This file is a header for muonRunAct class. In addition to the basic     //
// actions, user can add additional user-defined actions.This class can set   //
// actions for every run.                                                     //
//                                                                            //
//                    - 24. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4UserRunAction.hh"

class G4Run;

class muonRunAct : public G4UserRunAction
{
  public:
	muonRunAct();
    virtual ~muonRunAct();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};

#endif
