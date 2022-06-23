% List of files:
%
% Main functions:
%
% main.m: Main code that calls to secondary functions. It uses single scans
% and averaged blocks of scans. The peak detection algorithm is
% threshold-dependent.
%
% main_convol.m: Main code that calls to secondary functions. It uses single
% scans and averaged blocks, and applies a matched filter. The peak
% detection algorithm is prominence-based.
%
% Secondary functions:
%
% Average.m: Pointwise average of a set of scans. 
% findAC_quad.m: Find AC position by applying a threshold and fitting a
% quadratic.
%
% findPC_quad.m: It looks for the PC position within a window from the AC
% position. Same way as before.
%
% findPC_max.m It looks for the PC position by selecting the peak with
% highest prominence. (No need of threshold)
%
% convol_AC.m: Matched filter with AC peak profile as a template. (Prefered)
%
% convol_prof.m: Matched filter with Zemax simulated peak profile as a
% template (Produces similar results to moving average filter).
%
% weightedMedian.m: Weighte median of data
%
% Datasets: (First column contains positions of the front lens)
%
% Summary_RGaligned: 60 scans (subject RG)
% Summary_CHaligned: 50 scans (subject CH)
% RGSummaryAllScans: 90 scans (subject RG, different day)
% JRSummaryAllScans: 60 scans (subject JR)
% AC Peak profile: Zemax simulated peak intensities
