#include "muonEveAct.hh"
#include "muonSteAct.hh"

#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"

////////////////////////////////////////////////////////////////////////////////
//   muonSteAct.cc for Liz's 2018 winter project                              //
//                                                                            //
//   Definitions of muonSteAct class's member functions. Details of user      //
// actions are here.                                                          //
//                                                                            //
//                    - 24. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
//   Constrctor                                 //
//////////////////////////////////////////////////
muonSteAct::muonSteAct(muonEveAct* EA) : G4UserSteppingAction(), m_EA(EA)
{
	// Not only G4UserSteppingAction, but also muonEveAct class is used to
	// initialize. We need to get pointer of event action. This pointer will be
	// used to hand over the lifetime data into the event action object.
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
muonSteAct::~muonSteAct()
{
}

//////////////////////////////////////////////////
//   User stepping action                       //
//////////////////////////////////////////////////
void muonSteAct::UserSteppingAction(const G4Step* step)
{
	// I wrote examplse of some information which can be extracted from a step.
	// Uncomment whatever you want to use.

	// // Is first?
	G4bool isFirst = step -> IsFirstStepInVolume();
	// // Track ID
	G4int trackID = step -> GetTrack() -> GetTrackID();
	// // Parent track ID
	G4int parentID = step -> GetTrack() -> GetParentID();
	// // Particle name
	G4String parName = step -> GetTrack() -> GetDefinition() -> GetParticleName();
	// // Particle ID
//	G4int parID = step -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
	// // Particle charge
//	G4int parCharge = step -> GetTrack() -> GetDefinition() -> GetPDGCharge();
	// // Process name
	const G4VProcess* creProc = step -> GetTrack() -> GetCreatorProcess();
	G4String crePName = "I am your mather.";
	if ( creProc ) crePName = creProc -> GetProcessName();
	G4String procName = step -> GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName();
	// // Physical volume
	G4String namePrePV = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName();
//	G4String namePostPV;
//	G4VPhysicalVolume* postPV = step -> GetPostStepPoint() -> GetPhysicalVolume();
//	if ( postPV != 0 ) namePostPV = postPV -> GetName();
//	else namePostPV = "outside";
	// // Status
//	G4StepStatus preStat = step -> GetPreStepPoint() -> GetStepStatus();
//	G4StepStatus postStat = step -> GetPostStepPoint() -> GetStepStatus();
	// // Position
//	G4ThreeVector prePos = step -> GetPreStepPoint() -> GetPosition();
//	G4ThreeVector postPos = step -> GetPostStepPoint() -> GetPosition();
	// // Momentum
	G4ThreeVector preMom = step -> GetPreStepPoint() -> GetMomentum();
	G4ThreeVector postMom = step -> GetPostStepPoint() -> GetMomentum();
	// // Kinetic energy
//	G4double preKinEgy = step -> GetPreStepPoint() -> GetKineticEnergy();
//	G4double postKinEgy = step -> GetPostStepPoint() -> GetKineticEnergy();
	// // Energy deposition
	G4double eDep = step -> GetTotalEnergyDeposit();
	// // Global time
	G4double time = step -> GetPostStepPoint() -> GetGlobalTime();

	// Send information to the event action object.
	if ( namePrePV == "solidPV" ) m_EA -> FillHist(time/microsecond, eDep/MeV);

	double motherPx, motherPy, motherPz;
	double daughterPx, daughterPy, daughterPz;
	// Get parent momentum when decaying
	if ( trackID == 1 && procName == "Decay" )
	{
		motherPx = preMom.x();
		motherPy = preMom.y();
		motherPz = preMom.z();
//		G4cout << "Liz... please take care of my daughter... X_X" << G4endl;
//		G4cout << "\033[1;32m(" << preMom.x() << ", " << preMom.y() << ", " << preMom.z() << ")\033[0m"<< G4endl;
		FILE* file = fopen("decay.log", "a");
		fprintf(file, "%f %f %f ", motherPx, motherPy, motherPz);
		fclose(file);
	}

	// Mom!! Don't die!
	if ( parentID == 1 && crePName == "Decay" && parName == "e+" && isFirst && namePrePV == "solidPV" )
	{
		daughterPx = preMom.x();
		daughterPy = preMom.y();
		daughterPz = preMom.z();
//		G4cout << "Mom!" << G4endl;
//		G4cout << "(" << preMom.x() << ", " << preMom.y() << ", " << preMom.z() << ")"<< G4endl;
		FILE* file = fopen("decay.log", "a");
		fprintf(file, "%f %f %f\n", daughterPx, daughterPy, daughterPz);
		fclose(file);
	}
}
