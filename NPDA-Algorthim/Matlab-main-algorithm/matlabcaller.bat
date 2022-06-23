REM matlabcaller "Testing\APC-RevZ\GK3 SS10 1 27-02-2018 13-38-Raw.csv" 3 10
cd "C:\Users\graham\Documents\projects\R&D\RG_PeakImprovementWork"
matlab -nodisplay -r main_convol('%1',1,1,%2,%3,1)
REM pause