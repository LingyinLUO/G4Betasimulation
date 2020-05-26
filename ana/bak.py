import ROOT

ROOT.gStyle.SetOptStat(0)
names = ['postion8','postion7','postion6','postion5','postion4','postion3','postion2','postion1']
hist_dict = {}
for i,name in enumerate(names):
    hist_dict[name] = ROOT.TH1D(name,name,100,0,2)
    hist_dict[name].GetXaxis().SetTitle('energy [MeV]')
    hist_dict[name].GetYaxis().SetTitle('candidates [0.01/MeV]')
    hist_dict[name].SetFillColorAlpha(i+1,0.99)
    hist_dict[name].SetLineColor(i+1)
    hist_dict[name].SetFillStyle(0)

chain_dict ={}
for i,name in enumerate(names):
    chain_dict[name] = ROOT.TChain("mytree")
    chain_dict[name].Add('../../mac/air/air{0}.root'.format(8-i))
    #chain_dict[name].Add('../../mac/vacuum1/vacuum{0}.root'.format(8-i))

for name in names:
    chain_dict[name].Project(name,'energy')

c = ROOT.TCanvas()
hist_dict['postion8'].Draw()
for name in names[1:]:
    hist_dict[name].Draw('same')

leg = ROOT.TLegend(0.1,0.9,0.3,0.5)
for name in names:
    leg.AddEntry(name,name,"f")
leg.Draw("same")
c.Print('spectrum.pdf')

for name in names:
    peak = 0 
    for i in range(2,100-2):
        if hist_dict[name].GetBinContent(i)>hist_dict[name].GetBinContent(i-1) and\
                hist_dict[name].GetBinContent(i)>hist_dict[name].GetBinContent(i+1) and\
                hist_dict[name].GetBinContent(i)>hist_dict[name].GetBinContent(i-2) and\
                hist_dict[name].GetBinContent(i)>hist_dict[name].GetBinContent(i+2):
            peak = i*0.02
    yr = chain_dict[name].GetMaximum('energy')
    ym = peak*2 - yr
    sum1 = 0
    min1 = hist_dict[name].FindBin(ym)
    max1 = hist_dict[name].FindBin(yr)
    #print('caonima!:',min1*0.02,peak,max1*0.02)
    for i in range(min1,max1+1):
        A0 = hist_dict[name].Integral(min1,max1)
        Ai = hist_dict[name].Integral(min1,i)
        bkg = Ai/A0*(hist_dict[name].GetBinContent(min1)-hist_dict[name].GetBinContent(max1))+hist_dict[name].GetBinContent(max1)
        #print('A0:',A0,'Ai',Ai,'min:',hist_dict[name].GetBinContent(min1),'max:',hist_dict[name].GetBinContent(max1),'sig:',hist_dict[name].GetBinContent(i),'bkg:',bkg,'sumi:',hist_dict[name].GetBinContent(i)- bkg)
        if hist_dict[name].GetBinContent(i)- bkg >0 :
            #sum += hist_dict[name].GetBinContent(i)- bkg
            sum1+=hist_dict[name].GetBinContent(i)
    #print(peak,min1,max1)
    #print(name+' sum:',sum)
    print (sum1-(hist_dict[name].GetBinContent(min1)+hist_dict[name].GetBinContent(max1))*(max1-min1+1.)/2.)
