

void PoissonPlotBg() {
    	TCanvas *c1 = new TCanvas("c1", "Poisson Plot", 800, 600);
	
	TH1F *hist = new TH1F("hist", "Do Thi Histogram So Dem Phong 1000", 100, 0, 20);
	
	fstream file;
	file.open("Data_Output/Only_BackGround_1000.txt", ios::in);
	
	// Skip the first line
	string line;
	getline(file, line);
	// Skip the first line
	
	double value;

	if (file.is_open()) {
		while (file >> value) {
			hist->Fill(value);
		    }
		file.close();
	} else {
		std::cout << "Failed to open the file." << std::endl;
		return;
	}
	
	hist->GetXaxis()->SetTitle("So Dem (10s)");
	hist->GetYaxis()->SetTitle("Tan Suat");
	
	hist->Draw();        
	
	// Fit a Poisson distribution to the histogram
	TF1 *fitFunc = new TF1("fitFunc", "[0]*TMath::Poisson(x, [1])", 0, 20);
	fitFunc->SetParameters(1000, hist->GetMean()); // Set initial parameters
	hist->Fit(fitFunc);
	
	TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.75); // Create a legend object
	legend->AddEntry(hist, "Du Lieu Thuc Nghiem", "f"); // Add entry for histogram with "f" option for fill style
	legend->AddEntry(fitFunc, "Poisson", "l"); // Add entry for fit function with "l" option for line style
	legend->Draw(); // Draw the legend


	c1->Update();
    	c1->Modified();
}
