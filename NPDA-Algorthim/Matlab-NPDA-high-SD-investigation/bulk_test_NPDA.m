clear all

%cal_files_path = uigetdir('./', 'Select location of calibration data');
%if cal_files_path == 0
%    return
%end

%scan_files_path = uigetdir('./', 'Select location of scan data');
%if scan_files_path == 0
%    return
%end

%NPDA_path = uigetdir('./', 'Select location of the NPDA algorithm');
%if NPDA_path == 0
%    return
%end

%old_NPDA_path = uigetdir('./', 'Select location of the NPDA algorithm');
%if old_NPDA_path == 0
%    return
%end

cal_files_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\NPDA-Algorthim\Matlab-NPDA-high-SD-investigation';
scan_files_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\scan-data\P1 Handheld #001';
%scan_files_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\scan-data\P1 Data';
NPDA_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\NPDA-Algorthim\Matlab-main-algorithm';
old_NPDA_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\NPDA-Algorthim\Matlab-main-algorithm-as-sent-to-Robert';

i=1;
LENSTAR_results(i).initials='DB';
LENSTAR_results(i).date='18-09-2020';
LENSTAR_results(i).time='14-59-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=539;
LENSTAR_results(i).CCTSD=1.7;
i=i+1;
LENSTAR_results(i).initials='DB';
LENSTAR_results(i).date='18-09-2020';
LENSTAR_results(i).time='14-59-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=532;
LENSTAR_results(i).CCTSD=1.7;
i=i+1;
LENSTAR_results(i).initials='CG';
LENSTAR_results(i).date='30-09-2020';
LENSTAR_results(i).time='14-15-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=616;
LENSTAR_results(i).CCTSD=1.8;
i=i+1;
LENSTAR_results(i).initials='CG';
LENSTAR_results(i).date='30-09-2020';
LENSTAR_results(i).time='14-15-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=611;
LENSTAR_results(i).CCTSD=1.9;
i=i+1;
LENSTAR_results(i).initials='DD';
LENSTAR_results(i).date='12-08-2020';
LENSTAR_results(i).time='15-18-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=523;
LENSTAR_results(i).CCTSD=2.4;
i=i+1;
LENSTAR_results(i).initials='JS';%Jade
LENSTAR_results(i).date='02-11-2020';
LENSTAR_results(i).time='14-13-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=521;
LENSTAR_results(i).CCTSD=4.3;
i=i+1;
LENSTAR_results(i).initials='JS';%Jade
LENSTAR_results(i).date='02-11-2020';
LENSTAR_results(i).time='14-13-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=521;
LENSTAR_results(i).CCTSD=3.9;
i=i+1;
LENSTAR_results(i).initials='JS';%Jamie
LENSTAR_results(i).date='02-11-2020';
LENSTAR_results(i).time='14-24-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=553;
LENSTAR_results(i).CCTSD=2.8;
i=i+1;
LENSTAR_results(i).initials='JS';%Jamie
LENSTAR_results(i).date='02-11-2020';
LENSTAR_results(i).time='14-24-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=554;
LENSTAR_results(i).CCTSD=1.0;
i=i+1;
LENSTAR_results(i).initials='LPJ';
LENSTAR_results(i).date='30-09-2020';
LENSTAR_results(i).time='14-36-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=565;
LENSTAR_results(i).CCTSD=2.1;
i=i+1;
LENSTAR_results(i).initials='MK';
LENSTAR_results(i).date='02-11-2020';
LENSTAR_results(i).time='14-43-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=540;
LENSTAR_results(i).CCTSD=4.8;
i=i+1;
LENSTAR_results(i).initials='MK';
LENSTAR_results(i).date='02-11-2020';
LENSTAR_results(i).time='14-43-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=534;
LENSTAR_results(i).CCTSD=7.9;
i=i+1;
LENSTAR_results(i).initials='PL';
LENSTAR_results(i).date='02-11-2020';
LENSTAR_results(i).time='14-33-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=522;
LENSTAR_results(i).CCTSD=3.0;
i=i+1;
LENSTAR_results(i).initials='PL';
LENSTAR_results(i).date='02-11-2020';
LENSTAR_results(i).time='14-33-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=515;
LENSTAR_results(i).CCTSD=2.5;
i=i+1;
LENSTAR_results(i).initials='RT';
LENSTAR_results(i).date='12-08-2020';
LENSTAR_results(i).time='14-56-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=548;
LENSTAR_results(i).CCTSD=2.6;
i=i+1;
LENSTAR_results(i).initials='RT';
LENSTAR_results(i).date='12-08-2020';
LENSTAR_results(i).time='14-54-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=547;
LENSTAR_results(i).CCTSD=1.3;
i=i+1;
LENSTAR_results(i).initials='SB';
LENSTAR_results(i).date='12-08-2020';
LENSTAR_results(i).time='15-04-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=556;
LENSTAR_results(i).CCTSD=1.7;
i=i+1;
LENSTAR_results(i).initials='SB';
LENSTAR_results(i).date='12-08-2020';
LENSTAR_results(i).time='15-01-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=554;
LENSTAR_results(i).CCTSD=2.8;
i=i+1;
LENSTAR_results(i).initials='JR';
LENSTAR_results(i).date='12-08-2020';
LENSTAR_results(i).time='15-09-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=533;
LENSTAR_results(i).CCTSD=0.8;
i=i+1;
LENSTAR_results(i).initials='JR';
LENSTAR_results(i).date='12-08-2020';
LENSTAR_results(i).time='15-07-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=532;
LENSTAR_results(i).CCTSD=1.2;
i=i+1;
LENSTAR_results(i).initials='JR';
LENSTAR_results(i).date='16-11-2020';
LENSTAR_results(i).time='14-45-00';
LENSTAR_results(i).eye='L';
LENSTAR_results(i).CCT=533;
LENSTAR_results(i).CCTSD=2.9;
i=i+1;
LENSTAR_results(i).initials='JR';
LENSTAR_results(i).date='16-11-2020';
LENSTAR_results(i).time='14-36-00';
LENSTAR_results(i).eye='R';
LENSTAR_results(i).CCT=693;
LENSTAR_results(i).CCTSD=15.7;

list_of_scan_data_files = dirrec(scan_files_path, '.csv');
list_of_filtered_scan_data_files = list_of_scan_data_files(cellfun(@numel, regexp(list_of_scan_data_files, '[A-Z][A-Z]-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$'))==1);

list_of_cal_data_files = dirrec(cal_files_path, '.csv');
list_of_filtered_cal_data_files = list_of_cal_data_files(cellfun(@numel, regexp(list_of_cal_data_files, 'Cal lookup [0-9]{6}.*\.csv$'))==1);


for i = 1:length(list_of_filtered_cal_data_files)
    cal_data_file_with_path = char(list_of_filtered_cal_data_files(i));
    [cal_data_file_path, cal_data_file_wo_extension, cal_data_file_extension] = fileparts(cal_data_file_with_path);
    cal_data_file = strcat(cal_data_file_wo_extension, cal_data_file_extension);

    [~, tok] = regexp(cal_data_file, 'Cal lookup ([0-9]{6}).*\.csv$', 'match', 'tokens');
    tmp_cal_data_files(i).name = cal_data_file_with_path;
    tmp_cal_data_files(i).from = datenum(char(tok{1}(1)),'ddmmyy');
    array_to_sort(i) = datenum(char(tok{1}(1)),'ddmmyy');
end

[~,srt_idx] = sort(array_to_sort);
for i = 1:length(tmp_cal_data_files)
    cal_data_files(i).name = tmp_cal_data_files(srt_idx(i)).name;
    if srt_idx(i) == 1
        cal_data_files(i).from = 0;
    else
        cal_data_files(i).from = tmp_cal_data_files(srt_idx(i)).from;
    end
    if srt_idx(i) == length(tmp_cal_data_files)
        cal_data_files(i).to = Inf;
    else
        cal_data_files(i).to = tmp_cal_data_files(srt_idx(i+1)).from;
    end
end



analysis_counter = 1;
for i = 1:length(list_of_filtered_scan_data_files)
        
        scan_data_file_with_path = char(list_of_filtered_scan_data_files(i));
        [scan_data_file_path, scan_data_file_wo_extension, scan_data_file_extension] = fileparts(scan_data_file_with_path);
        scan_data_file_path = strcat(scan_data_file_path, '\');
        scan_data_file = strcat(scan_data_file_wo_extension, scan_data_file_extension);

        %% Get initials, side (if avaialble) number of scans and number of blocks
        [mat, tok] = regexp(scan_data_file, '([A-Z]{2,3})-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-([0-9]+)-([0-9]+)-Raw\.csv$', 'match', 'tokens');

        initials = char(tok{1}(1));
        number_of_blocks = str2double(tok{1}(2));
        number_of_scans = str2double(tok{1}(3));
        number_of_scans_per_block = number_of_scans / number_of_blocks;
        side = '';
        if length(initials) == 3 && initials(3) == 'L'
            side = 'L';
            initials = initials(1:2);
        end
        if strcmp(initials, 'LHS')
            [mat, tok] = regexp(scan_data_file, '([A-Z]{2,3})-[A-Z]{2,3}-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$', 'match', 'tokens');
            initials = char(tok{1}(1));
            side = 'L';
        end
        if strcmp(initials, 'RHS')
            [mat, tok] = regexp(scan_data_file, '([A-Z]{2,3})-[A-Z]{2,3}-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$', 'match', 'tokens');
            initials = char(tok{1}(1));
            side = 'R';
        end    

        %% Get scan date
        if any(regexp(scan_data_file, '[A-Z]{2,3}-([0-9]{4}-[0-9]{2}-[0-9]{2})-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$')) && 1
            [mat, tok] = regexp(scan_data_file, '[A-Z]{2,3}-([0-9]{4}-[0-9]{2}-[0-9]{2})-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$', 'match', 'tokens');
            date = datenum(char(tok{1}(1)),'yyyy-mm-dd');
        elseif any(regexp(scan_data_file, '[A-Z]{2,3}-([0-9]{2}-[0-9]{2}-[0-9]{4})-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$')) && 1
            [mat, tok] = regexp(scan_data_file, '[A-Z]{2,3}-([0-9]{2}-[0-9]{2}-[0-9]{4})-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$', 'match', 'tokens');
            date = datenum(char(tok{1}(1)),'dd-mm-yyyy');
        end


        for j = 1:length(cal_data_files)
            if date >= cal_data_files(j).from && date < cal_data_files(j).to
                cal_file = char(cal_data_files(j).name);
            end
        end
        
        %scan_data_file_with_path
        %cal_file
        %number_of_blocks
        %number_of_scans_per_block
        %number_of_scans_per_block
        %% Run NPDA algorithm on the cal and scan data
        current_folder = pwd;
        cd(NPDA_path)
        [~, ~, ~, ~, weightedMean, wmSDE, mean_wt, valid, weight, thick] = main_convol_GK_cal2(scan_data_file_with_path, cal_file, 0, 1, number_of_blocks, number_of_scans_per_block, number_of_scans_per_block, 0, 0, 1, 1, 1);
        cd(current_folder)
        NPDA_comparison(i).new.corneal_thickness = weightedMean;
        NPDA_comparison(i).new.corneal_thickness_accuracy = wmSDE;
        NPDA_comparison(i).new.mean_weight = mean_wt;
        NPDA_comparison(i).new.valid_blocks = valid;
        for j = 1:length(weight)
            w_analysis(analysis_counter) = weight(j);
            t_analysis(analysis_counter) = abs(thick(j) - median(thick));
            analysis_counter = analysis_counter + 1;
        end
            
        clear weightedMean wmSDE mean_wt valid
        %pause
        cd(old_NPDA_path)
        [~, ~, ~, ~, weightedMean, wmSDE, mean_wt, valid] = main_convol_GK2(scan_data_file_with_path, 0, 1, number_of_blocks, number_of_scans_per_block, number_of_scans_per_block, 0, 0, 1);
        cd(current_folder)
        NPDA_comparison(i).old.corneal_thickness = weightedMean;
        NPDA_comparison(i).old.corneal_thickness_accuracy = wmSDE;
        NPDA_comparison(i).old.mean_weight = mean_wt;
        NPDA_comparison(i).old.valid_blocks = valid;
        clear weightedMean wmSDE mean_wt valid

        %% Find corresponding Lenstar data (only by initials)
        NPDA_comparison(i).ls.corneal_thickness = 0;
        NPDA_comparison(i).ls.corneal_thickness_accuracy = 0;
        counter = 0;
        for j = 1:length(LENSTAR_results)
            if strcmp(side,'')
                if strcmp(LENSTAR_results(j).initials, initials)
                    NPDA_comparison(i).ls.corneal_thickness = NPDA_comparison(i).ls.corneal_thickness + LENSTAR_results(j).CCT;
                    NPDA_comparison(i).ls.corneal_thickness_accuracy = NPDA_comparison(i).ls.corneal_thickness_accuracy + LENSTAR_results(j).CCTSD;
                    counter = counter + 1;
                end
            elseif strcmp(side,'R')
                if strcmp(LENSTAR_results(j).initials, initials) && strcmp(LENSTAR_results(j).eye, 'R')
                    NPDA_comparison(i).ls.corneal_thickness = NPDA_comparison(i).ls.corneal_thickness + LENSTAR_results(j).CCT;
                    NPDA_comparison(i).ls.corneal_thickness_accuracy = NPDA_comparison(i).ls.corneal_thickness_accuracy + LENSTAR_results(j).CCTSD;
                    counter = counter + 1;
                end
            elseif strcmp(side,'L')
                if strcmp(LENSTAR_results(j).initials, initials) && strcmp(LENSTAR_results(j).eye, 'L')
                    NPDA_comparison(i).ls.corneal_thickness = NPDA_comparison(i).ls.corneal_thickness + LENSTAR_results(j).CCT;
                    NPDA_comparison(i).ls.corneal_thickness_accuracy = NPDA_comparison(i).ls.corneal_thickness_accuracy + LENSTAR_results(j).CCTSD;
                    counter = counter + 1;
                end
            end
        end
        if counter ~= 0
            NPDA_comparison(i).ls.corneal_thickness = NPDA_comparison(i).ls.corneal_thickness / counter;
            NPDA_comparison(i).ls.corneal_thickness_accuracy = NPDA_comparison(i).ls.corneal_thickness_accuracy / counter;
        end
        
        if NPDA_comparison(i).ls.corneal_thickness == 0 || NPDA_comparison(i).ls.corneal_thickness_accuracy == 0 && ~strcmp(initials, 'MJ')
            fprintf('HELP')
        end

        fprintf('%d/%d Test results for %s\n', i, length(list_of_filtered_scan_data_files), scan_data_file); 
        fprintf('New NPDA thickness (SD): %.2f(%.2f)\n', NPDA_comparison(i).new.corneal_thickness, NPDA_comparison(i).new.corneal_thickness_accuracy); 
        fprintf('Old NPDA thickness (SD): %.2f(%.2f)\n', NPDA_comparison(i).old.corneal_thickness, NPDA_comparison(i).old.corneal_thickness_accuracy); 

        fprintf('\n'); 
end

j = 1;
for i = 1:length(NPDA_comparison)
    if NPDA_comparison(i).ls.corneal_thickness ~= 0
        bar_corneal_thickness(j,1) = NPDA_comparison(i).old.corneal_thickness;
        bar_corneal_thickness(j,2) = NPDA_comparison(i).new.corneal_thickness;
        bar_corneal_thickness(j,3) = NPDA_comparison(i).ls.corneal_thickness;

        bar_corneal_thickness_residual(j,1) = abs(NPDA_comparison(i).old.corneal_thickness - NPDA_comparison(i).ls.corneal_thickness);
        bar_corneal_thickness_residual(j,2) = abs(NPDA_comparison(i).new.corneal_thickness - NPDA_comparison(i).ls.corneal_thickness);

        bar_corneal_thickness_sd(j,1) = NPDA_comparison(i).old.corneal_thickness_accuracy;
        bar_corneal_thickness_sd(j,2) = NPDA_comparison(i).new.corneal_thickness_accuracy;
        bar_corneal_thickness_sd(j,3) = NPDA_comparison(i).ls.corneal_thickness_accuracy;
        j=j+1;
    end
end

figure;
bar(bar_corneal_thickness)
figure;
bar(bar_corneal_thickness_residual)
figure;
bar(bar_corneal_thickness_sd)
figure;
plot(w_analysis,t_analysis, 'ko')
xlabel('weight')
ylabel('thickness deviation from median')

fprintf('NPDA thickness residual (new/old): %.2f/%.2f\n', mean(bar_corneal_thickness_residual(:,2)), mean(bar_corneal_thickness_residual(:,1)));
fprintf('NPDA thickness SD (new/old): %.2f/%.2f\n', mean(bar_corneal_thickness_sd(:,2)), mean(bar_corneal_thickness_sd(:,1)));

% w_threshold = 0:0.01:0.3;
% for j = 1:length(w_threshold)
%     good_rejects(j) = 0;
%     bad_rejects(j) = 0;
%     for i = 1:length(w_analysis)
%         if w_analysis(i) < w_threshold(j)
%             if t_analysis(i) < 0.05
%                 bad_rejects(j) = bad_rejects(j) + 1;
%             else
%                 good_rejects(j) = good_rejects(j) + 1;
%             end
%         end
%     end
% end
% figure;
% plot(w_threshold, good_rejects./bad_rejects, 'b-')
%hold on
%plot(w_threshold, bad_rejects, 'r-')

    