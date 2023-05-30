void ThreePlotBg() {

	// Set value
	int count_min = 0;
	int count_max = 18;
	int Fre_Max = 181;
	//

    TCanvas *c1 = new TCanvas("c1", "Poisson, Gaussian, and Lorentzian Plot", 800, 600);

    TH1F *hist = new TH1F("hist", "Do Thi Histogram So Dem Phong 1000", 100, count_min, count_max);
    TH1F *hist2 = new TH1F("hist2", "Do Thi Histogram So Dem Phong 1000", 100, count_min, count_max);
    TH1F *hist3 = new TH1F("hist3", "Do Thi Histogram So Dem Phong 1000", 100, count_min, count_max);

    std::ifstream file;
    file.open("Data_Output/Only_BackGround_1000.txt", std::ios::in);
    
    double value;

    if (file.is_open()) {
        while (file >> value) {
		hist->Fill(value);
		hist2->Fill(value);
		hist3->Fill(value);
        }
        file.close();
    } else {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    hist->GetXaxis()->SetTitle("So Dem (10s)");
    hist->GetYaxis()->SetTitle("Tan Suat");

    hist->GetXaxis()->SetRangeUser(0, 18);
    hist->GetYaxis()->SetRangeUser(0, 220);
    
    hist->Draw();
    hist2->Draw("SAME");
    hist3->Draw("SAME");

    // Fit a Poisson distribution to hist
    TF1 *mypoisson = new TF1("mypoisson", "[0]*TMath::Poisson(x, [1])", count_min, count_max);
    mypoisson->SetParameters(hist->GetEntries(), hist->GetMean());
    mypoisson->SetLineColor(kRed);
    hist->Fit(mypoisson, "R");

    // Fit a Gaussian distribution to hist2
    TF1 *mygauss = new TF1("mygauss", "gaus", count_min, count_max);
    mygauss->SetLineColor(kBlue);
    hist2->Fit(mygauss, "R");

    // Fit a Lorentzian distribution to hist3
    TF1 *mylorentz = new TF1("mylorentz", "[0]/TMath::Pi() * [2] / ((x - [1])*(x - [1]) + [2]*[2])", count_min, count_max);
    mylorentz->SetParameters(hist->GetEntries(), hist3->GetMean(), hist3->GetRMS());
    mylorentz->SetLineColor(kGreen);
    hist3->Fit(mylorentz, "R");

    TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.75);
    legend->AddEntry(hist, "Du Lieu Thuc Nghiem", "f");
    legend->AddEntry(mypoisson, "Poisson", "l");
    legend->AddEntry(mygauss, "Gaussian", "l");
    legend->AddEntry(mylorentz, "Lorentzian", "l");
    legend->Draw();
	   
    c1->Update();
    c1->Modified();
}

