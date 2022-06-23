function [scan, scan_cnt, gain, ip_valid] = validate_data(data)

    %Check if data is the right size
    if size(data, 1) < 1 || size(data, 2) ~= 5003
        error('Wrong data size');
    end

    %Remove errorneous scans, i.e. such that do not start with 1,2,3 or 
    %have wrong length
    i = 1;
    while i <= size(data, 1)
        if length(data(i,:)) == 5003
            scan = data(i,4:end);
            if (isequal(scan(1:3),[1,2,3]) && isequal(scan(end-2:end),[4998,4999,5000])) || ...
              (isequal(scan(1:3),[5000,4999,4998]) && isequal(scan(end-2:end), [3,2,1]))
                i = i + 1;
                continue
            end
        end
        data(i,:) = [];
    end

    %Count number of scans
    scans_no = size(data, 1);
    
    %Throw an error if no good scans are left
    if scans_no < 1
        error('No good scans');
    end

    %Work out if scans should start with 1,2,3 on even or odd scan counts
    even = 0;
    odd = 0;
    for i=1:scans_no
        scan = data(i,4:end);
        scan_cnt = data(i,1);
        if isequal(scan(1:3),[1,2,3]) && mod(scan_cnt,2) == 0 || ...
                isequal(scan(1:3),[5000,4999,4998]) && mod(scan_cnt,2) == 1
            even = even + 1;
        else
            odd = odd + 1;
        end
    end
    
    %Remove scans that do not follow the most common patters
    i = 1;
    while i <= size(data, 1)
        scan = data(i,4:end);
        scan_cnt = data(i,1);
        if even < odd
            if isequal(scan(1:3),[1,2,3]) && mod(scan_cnt,2) == 0 || ...
                isequal(scan(1:3),[5000,4999,4998]) && mod(scan_cnt,2) == 1
                data(i,:) = [];
                continue
            end
        else
            if isequal(scan(1:3),[1,2,3]) && mod(scan_cnt,2) == 1 || ...
                isequal(scan(1:3),[5000,4999,4998]) && mod(scan_cnt,2) == 0
                data(i,:) = [];
                continue
            end
        end
        i = i + 1;
    end
    
    %Throw an error if no good scans are left
    if scans_no < 1
        error('No good scans');
    end
    
    %Extract scan data, count, gain and ip_valid
    scan = data(:,4:end);
    scan_cnt = data(:,1);
    gain = data(:,2);
    ip_valid = data(:,3);

end