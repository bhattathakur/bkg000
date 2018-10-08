{
  c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(42);
  graph_expected=new TGraphErrors("TabulatedvsCalculatedE.dat","%lg%lg%lg%lg","");
  graph_expected->SetTitle("Tabulated Energy vs Fitted Energy plot;E_{estimated}(eV);E_{true}(eV);");
  graph_expected->SetMarkerColor(4);
  graph_expected->SetMarkerStyle(21);
  graph_expected->SetLineColor(7);
  graph_expected->SetLineWidth(2);
  graph_expected->Draw("AP");
  graph_expected->Fit("pol1");
  graph_expected->GetFunction("pol1")->SetLineStyle(2);
  graph_expected->GetFunction("pol1")->SetParName(0,"intercept");
  graph_expected->GetFunction("pol1")->SetParName(1,"slope");
  c->Update();
  c->GetFrame()->SetFillColor(21);
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetOptFit();
  graph_expected->Draw();
  c->Modified();
  
}
