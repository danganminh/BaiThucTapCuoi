
void GaussPlotSr(){
	TCanvas *c1 = new TCanvas("c1", "Gauss", 800, 600);
	
	TH1F *hist = new TH1F("hist", "Do Thi Histogram So Dem{}^{226}Ra 5#muCi", 200, 97, 170);
	
	
	std::ifstream file;
	file.open("Data_Output/Only_Source_1000.txt", std::ios::in);
	
	// Skip the first line
	std::string line;
	std::getline(file, line);
	// Skip the first line
	
	double value;
	
	if (file.is_open())	{
		while (file >> value) {
			hist->Fill(value);
		}
		file.close();
	} else {
		std::cout << "Failed to open the file" << std::endl;
		return 0;
	}
	
	
	hist->GetXaxis()->SetTitle("So Dem (2s)");
	hist->GetYaxis()->SetTitle("Tan Suat");
	
	hist->Draw();
	
	// Fit Gauss
	TF1 *mygauss = new TF1("mygauss", "gaus", 97, 170);
	mygauss->SetLineColor(kRed);
	hist->Fit(mygauss, "R");
	
	
	TLegend *legend = new TLegend(0.1, 0.9, 0.4, 0.75);
	legend->AddEntry(hist, "Du Lieu Thuc Nghiem", "f");
	legend->AddEntry(mygauss, "Gauss", "l");
	legend->Draw();

	
	c1->Update();
	c1->Modified();
}
