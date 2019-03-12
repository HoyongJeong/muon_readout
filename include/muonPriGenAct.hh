#ifndef MUONPRIGENACT_h
#define MUONPRIGENACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   muonPriGenAct.hh for Liz's 2018 winter project.                          //
//                                                                            //
//   This file is a header for muonPriGenAct class. You can set primary       //
// beam options in this class.                                                //
//                                                                            //
//                    - 10. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"

class G4ParticleGun;

class muonPriGenAct: public G4VUserPrimaryGeneratorAction
{
  private:
	G4ParticleGun* PG;

  public:
	muonPriGenAct();
	~muonPriGenAct();

	virtual void GeneratePrimaries(G4Event* anEvent);

  private:
	G4double m_BeamPX, m_BeamPY;
	G4double m_BeamDX, m_BeamDY;
	G4double m_WorldZ;
	G4ThreeVector m_GunPos;
	G4ParticleDefinition* m_Par;
	G4ThreeVector m_MomDir;
	G4double m_Mom;
	G4double m_KinEgy;
	G4ThreeVector m_Pol;
};

#endif
