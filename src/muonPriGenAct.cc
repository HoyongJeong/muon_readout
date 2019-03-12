////////////////////////////////////////////////////////////////////////////////
//   BT2017PriGenAct.cc for beamtest2017 of JEDI                              //
//                                                                            //
//   Definitions of BT2017PriGenAct class's member functions.                 //
//                                                                            //
//                    - 21. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////


#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

#include "muonPriGenAct.hh"

//////////////////////////////////////////////////
//   Constructor and destructor                 //
//////////////////////////////////////////////////
muonPriGenAct::muonPriGenAct()
{
	PG = new G4ParticleGun();

	// Gun position
	m_WorldZ = -300.0 * mm;
	m_BeamPX =   50.0 * mm;
	m_BeamPY =   50.0 * mm;
	m_BeamDX =   10.0 * mm;
	m_BeamDY =   10.0 * mm;;

	// Set particle definition
	G4ParticleTable* PT = G4ParticleTable::GetParticleTable();
	m_Par = PT -> FindParticle("mu+");
	PG -> SetParticleDefinition(m_Par);

	// Momentum direction
	m_MomDir = G4ThreeVector(0., 0., 1.);
	PG -> SetParticleMomentumDirection(m_MomDir);

	// Kinetic energy
	m_KinEgy = 10.0 * MeV;
	PG -> SetParticleEnergy(m_KinEgy);

	// Polarization
	m_Pol = G4ThreeVector(0., 0., 0.);
	PG -> SetParticlePolarization(m_Pol);
}

muonPriGenAct::~muonPriGenAct()
{
	delete PG;
}


//////////////////////////////////////////////////
//   Shoot!                                     //
//////////////////////////////////////////////////
void muonPriGenAct::GeneratePrimaries(G4Event* anEvent)
{
	// 2D Gaussian
	G4double dX = G4RandGauss::shoot(0., m_BeamDX / mm / 3.0); // 3 sigma
	G4double dY = G4RandGauss::shoot(0., m_BeamDY / mm / 3.0); // 3 sigma
	m_GunPos = G4ThreeVector(m_BeamPX + dX * mm, m_BeamPY + dY * mm, m_WorldZ/2);
	PG -> SetParticlePosition(m_GunPos);

	PG -> GeneratePrimaryVertex(anEvent);
}
