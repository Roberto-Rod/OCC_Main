function [res] = median_uint16_t(arr, n)
    global S;
    l = 1; % Should be 0 in C implementation
    ir = n - mod(n-1, S); % Should be n-1 - ((n-1)%s); in C implementation
    m = floor((ir-l)/(2*S)); %Should be (ir-l)/(2*s); in C implementation
    k = l+S*m; % Should be l+s*m; in C implementation
    while(1)
        if (ir <= l+S) % Two elements only 
            if ir == l+S && arr(ir) < arr(l)
                arr = elem_swap(arr, l, ir);
            end
            res = arr(k);
            return;
        else
            m = floor((ir-l)/(2*S)); %Should be (ir-l)/(2*s); in C implementation
            mid = l+S*m; % Should be l+s*m; in C implementation
            arr = elem_swap(arr, mid, l+S);
            
            if (arr(l) > arr(ir))
                arr = elem_swap(arr, l, ir);
            end
            if (arr(l+S) > arr(ir))
                arr = elem_swap(arr, l+S, ir);
            end
            if (arr(l) > arr(l+S))
                arr = elem_swap(arr, l, l+S);
            end

            i=l+S;
            j=ir;
            a=arr(l+S);
            while(1)
                while(1) % This is the MATLAB do-while: do ll+=step; while (vector[low] > vector[ll]);
                    i = i + S;
                    if (arr(i) >= a)
                        break;
                    end
                end

                while(1) % This is the MATLAB do-while: do ll+=step; while (vector[low] > vector[ll]);
                    j = j - S;
                    if (arr(j) <= a)
                        break;
                    end
                end

                if (j < i)
                    break;
                end

                arr = elem_swap(arr, i, j);
            end

            arr(l+S)=arr(j);
            arr(j)=a;
            if (j >= k)
                ir=j-S;
            end
            if (j <= k)
                l=i;
            end
        end
    end
end