////////////////////////////////////////////////////////////////////////////////
//   muon.cc for Liz's 2018 winter project.                                   //
//                                                                            //
//   This is main function of the simulation program.                         //
//                                                                            //
//                    - 10. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "muonDetCon.hh"
#include "muonActIni.hh"

#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4String.hh"

#include "Randomize.hh"
#include "QGSP_BERT.hh"

int main (int argc, char** argv)
{
	// Randomizer
	CLHEP::RanluxEngine defaultEngine(1234567, 4);
	G4Random::setTheEngine(&defaultEngine);
	G4int seed = time(NULL);
	G4Random::setTheSeed(seed);

	// Detect interactive mode (if any arguments) and define UI session
	G4UIExecutive* UI = 0;
	// argc means how many argument when you execute a program.
	// argv is a array of argument data in character.
	// You should find more information about these.
	if ( argc != 1 ) UI = new G4UIExecutive(argc, argv);

	// Run manager
	#ifdef G4MULTITHREADED
	G4MTRunManager* RM = new G4MTRunManager();
	RM -> SetNumberOfThreads(1);
	#else
	G4RunManager* RM = new G4MTRunManager();
	#endif

	// Detector construction from configuration (Geometry)
	// You will define everything about geometrical setup is this class.
	muonDetCon* muonDC = new muonDetCon();
	RM -> SetUserInitialization(muonDC);

	// Physics list to be used
	// We are going to use a basic list.
	// If you are good at Geant, of course, you can generate your own physics list.
	G4VModularPhysicsList* PL = new QGSP_BERT;
	PL -> SetVerboseLevel(0);
	RM -> SetUserInitialization(PL);

	// User actions
	RM -> SetUserInitialization(new muonActIni());

	// Initialize
	RM -> Initialize();

	// Visualization manger
	// This will give us nice 3D drawing!
	G4VisManager* VM = new G4VisExecutive();
	VM -> Initialize();

	// Get the pointer to the user interface manager
	G4UImanager* UM = G4UImanager::GetUIpointer();

	// Process macro or start UI session
	if ( !UI )
	{
		// batch mode
		G4UIsession* US = new G4UIterminal(new G4UItcsh);
		US -> SessionStart();

		delete US;
	}

	else
	{
		// Interactive mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UM -> ApplyCommand(command + fileName);
		UI -> SessionStart();

		delete UI;
	}

	// Job termination
	// Free the store: user actions, physics_list and detector_description are
	// owned and deleted by the run manager, so they should not be deleted 
	// in the main() program!
	delete VM;
	delete RM;

	return 0;
}
