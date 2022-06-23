 function s = lein_nansum( A, varargin )
    sum(isfinite(cell2mat(A)),1)
   colMean = sum(isfinite(cell2mat(A)),1) ./ sum(isfinite(cell2mat(A~=0)),1)
 end
