function [res] = elem_swap(vector, idx1, idx2) % ELEM_SWAP(vector[idx1], vector[idx2]) ;
    temp = vector(idx1); 
    vector(idx1) = vector(idx2);
    vector(idx2) = temp;
    res = vector;
end
