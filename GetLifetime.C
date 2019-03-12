////////////////////////////////////////////////////////////////////////////////
//   GetLifetime.C for Liz's 2018 winter project                              //
//                                                                            //
//   This file is a ROOT macro to draw histrogram from the result of the      //
// GEANT simulation.                                                          //
//                                                                            //
//                    - 24. Jan. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

void GetLifetime()
{
	// Read ntuple
	TChain* data = new TChain("hits");
	data -> Add("muon-*");

	// Histogram
	TH1D* dist = new TH1D("dist", "dist", 200, 0, 20);
	dist -> SetFillColor(kGray);
	dist -> SetLineColor(1);

	// Draw
	data -> Draw("lifetime >> dist");
	cout << endl << "\033[1;32m [NOTICE] " << dist -> GetEntries()
	     << " events detected.\033[0m" << endl << endl;

	// Fit and get result
	dist -> Fit("expo");
	double ti  = dist -> GetFunction("expo") -> GetParameter(1);
	double eti = dist -> GetFunction("expo") -> GetParError(1);
	double t   = - 1.0 / ti;
	double et  = eti / ti / ti;
	cout << endl << "\033[1;32m [NOTICE] Lifetime from fit is ("
	     << t << " +- " << et << ") us.\033[0m" << endl;

	cout << endl << "\033[1;34m [INFO] The lifetime of the muon is known as "
	     << "(2.1969811 +- 0.0000022) us.\033[0m" << endl << endl; 
}
