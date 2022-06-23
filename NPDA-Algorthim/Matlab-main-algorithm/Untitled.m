profile on; 
[a,b,pp,qq,weightedMean, wmSDE, mean_wt] = main_convol_GK('C:\testing\Handheld\18-05-15\Test5\A-Scan.csv',1,1,10,10,1,1,1);
profile off; 
p=profile('info'); 
findNonSuppressedOutput( p, 'C:\Repos\projects\R&D\iScan\System_Tags\V0.1.4\RG_PeakImprovementWork_V1.0' )
