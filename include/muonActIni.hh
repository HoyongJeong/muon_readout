#ifndef MUONACTINI_h
#define MUONACTINI_h 1

////////////////////////////////////////////////////////////////////////////////
//   muonActIni.hh for Liz's 2018 winter project.                             //
//                                                                            //
//   This file is a header for muonActIni class. Every actions are            //
// initialized through this class.                                            //
//                                                                            //
//                    - 10. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4VUserActionInitialization.hh"

class muonActIni : public G4VUserActionInitialization
{
  public:
	muonActIni();
	virtual ~muonActIni();

	virtual void BuildForMaster() const;
	virtual void Build() const;
};

#endif
