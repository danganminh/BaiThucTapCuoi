
void ThreePlotSr(){
	
	// Set value
	int count_min = 97;
	int count_max = 170;
	int Fre_Max = 139;
	//

	TCanvas *c1 = new TCanvas("c1", "Gauss", 800, 600);
	
	TH1F *hist = new TH1F("hist", "Do Thi Histogram So Dem {}^{226}Ra 5#muCi", 200, count_min, count_max);
	TH1F *hist2 = new TH1F("hist2", "Do Thi Histogram So Dem {}^{226}Ra 5#muCi", 200, count_min, count_max);
	TH1F *hist3 = new TH1F("hist3", "Do Thi Histogram So Dem {}^{226}Ra 5#muCi", 200, count_min, count_max);	

	std::fstream file;
	file.open("Data_Output/Only_Source_1000.txt", std::ios::in);

	double value;
	
	if (file.is_open())	{
		while (file >> value) {
			hist->Fill(value);
			hist2->Fill(value);
			hist3->Fill(value);
		}
		file.close();
	} else {
		std::cout << "Failed to open the file" << std::endl;
		return;
	}
	
	hist->GetXaxis()->SetTitle("So Dem (2s)");
	hist->GetYaxis()->SetTitle("Tan Suat");
	
	hist->Draw();
	hist2->Draw("SAME");
	hist3->Draw("SAME");
	
	// Fit Gauss
	TF1 *mygauss = new TF1("mygauss", "gaus", count_min, count_max);
	mygauss->SetLineColor(kRed);
	hist->Fit(mygauss, "R");
	
	// Poisson
	TF1 *mypoisson = new TF1("mypoisson", "[0]*TMath::Poisson(x, [1])", count_min, count_max);
	mypoisson->SetParameters(hist->GetEntries(), hist->GetMean());
	mypoisson->SetLineColor(kBlue);
	hist2->Fit(mypoisson, "R");

	// Fit Lorentzian
	TF1 *mylorentz = new TF1("mylorentz", "[0]/TMath::Pi() * [2] / ((x - [1])*(x - [1]) + [2]*[2])", count_min, count_max);
	mylorentz->SetParameters(hist->GetEntries(), hist->GetMean(), hist->GetRMS());
	mylorentz->SetLineColor(kGreen);
	hist3->Fit(mylorentz, "R");
	
	TLegend *legend = new TLegend(0.1, 0.9, 0.4, 0.75);
	legend->AddEntry(hist, "Du Lieu Thuc Nghiem", "f");
	legend->AddEntry(mygauss, "Gauss", "l");
	legend->AddEntry(mypoisson, "Poisson", "l");
    	legend->AddEntry(mylorentz, "Lorentzian", "l");
	legend->Draw();
	
	c1->Update();
	c1->Modified();
}
