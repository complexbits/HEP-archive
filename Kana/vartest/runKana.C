{
gROOT->SetStyle("Plain");
gStyle->SetOptStat(111111);
gROOT->ProcessLine(".L kanaD1.C");
gROOT->ProcessLine("kana_v2 t");
gROOT->ProcessLine("t.Loop()");
}
