

void PoissonPlotBg() {
	
	// Set value
	int count_min = 0;
	int count_max = 18;
	int Fre_Max = 181;
	//
	
    	TCanvas *c1 = new TCanvas("c1", "Poisson Plot", 800, 600);
	
	TH1F *hist = new TH1F("hist", "Do Thi Histogram So Dem Phong 1000", 100, count_min, count_max);
	
	fstream file;
	file.open("Data_Output/Only_BackGround_1000.txt", ios::in);
	
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
	TF1 *mypoisson = new TF1("mypoisson", "[0]*TMath::Poisson(x, [1])", count_min, count_max);
    	mypoisson->SetParameters(hist->GetEntries(), hist->GetMean());
    	mypoisson->SetParNames("Constant","Mean_value");
    	mypoisson->SetLineColor(kRed);
   	hist->Fit(mypoisson, "R");
	
	TLegend *legend = new TLegend(0.6, 0.5, 0.9, 0.4); // Create a legend object
	legend->AddEntry(hist, "Du Lieu Thuc Nghiem", "f"); // Add entry for histogram with "f" option for fill style
	legend->AddEntry(mypoisson, "Poisson", "l"); // Add entry for fit function with "l" option for line style
	legend->Draw(); // Draw the legend
	
	c1->Update();
    	c1->Modified();
}
