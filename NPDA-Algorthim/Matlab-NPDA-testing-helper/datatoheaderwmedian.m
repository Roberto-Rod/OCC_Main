function [] = datatoheaderwmedian( data, offsets, medians, corneal_thickness, corneal_thickness_accuracy, mean_weight, valid_blocks, cal_data, var_name, file_out, file_out_path, original_file_name, scan_size, total_scans, interrupt_lvl )
%DATATOHEADERWMEDIAN Creates header file with scan data compatible with ceedling tests

    file = fopen(file_out_path,'w');

    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'/**\n');
    fprintf(file,' * @file %s\n',file_out);
    fprintf(file,' * @author datatoheaderwmedian.m \n');
    fprintf(file,' * @brief Restricted test data file for the NPDA algorithm.\n');
    fprintf(file,' * @note SCAN SIZE: %d\n', scan_size);
    fprintf(file,' * @note NUMBER OF SCANS: %d\n', total_scans);
    fprintf(file,' * @note OFFSETS: WINDOW SIZE 1000\n');
    fprintf(file,' * @note THRESHOLD %d\n', interrupt_lvl);
    fprintf(file,' * @note WINDOW HEADER 200\n');
    fprintf(file,' * @note BASED ON: %s\n',original_file_name);
    fprintf(file,'*/\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'\n');
    fprintf(file,'#ifndef _TEST_M_NPDA_SCAN_DATA_%s_H\n', upper(var_name));
    fprintf(file,'#define _TEST_M_NPDA_SCAN_DATA_%s_H\n', upper(var_name));
    fprintf(file,'\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'/* Section: Included Files                                                    */\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'\n');
    fprintf(file,'#include "pdab_types.h"\n');
    fprintf(file,'#include "npda.h"\n');
    fprintf(file,'\n');
    fprintf(file,'/* Provide C++ Compatibility */\n');
    fprintf(file,'#ifdef __cplusplus\n');
    fprintf(file,'extern "C" {\n');
    fprintf(file,'#endif\n');
    fprintf(file,'\n');
    fprintf(file,'    /* ************************************************************************** */\n');
    fprintf(file,'    /* ************************************************************************** */\n');
    fprintf(file,'    /* Section: Constants                                                         */\n');
    fprintf(file,'    /* ************************************************************************** */\n');
    fprintf(file,'    /* ************************************************************************** */\n');
    fprintf(file,'\n');
    fprintf(file,'    const fptype cal_data_%s[] = {', var_name);

    writeformatteddata(file, cal_data, length(cal_data), 500, 'float');

    fprintf(file,'};\n');
    fprintf(file,'\n');
    fprintf(file,'    _NPDA_SCAN_BUFFER scanData_%s = {\n', var_name);
    fprintf(file,'	.Scans = {	\n');
    for i=1:total_scans
        if i~=1
            fprintf(file,',\n');
        end
        fprintf(file,'	    			{.Data = {');
        writeformatteddata(file, data(:,i), length(data(:,i)), length(data(:,i)), 'int')
        fprintf(file,'}}');
    end
    fprintf(file,'    			 },\n');
    fprintf(file,'    	.Positions = {');
    writeformatteddata(file, offsets', total_scans, total_scans, 'int')
    fprintf(file,'    },\n');
    fprintf(file,'    	.DC_Level = {');
    writeformatteddata(file, medians', total_scans, total_scans, 'int')
    fprintf(file,'}\n');
    fprintf(file,'    };\n');
    fprintf(file,'\n');
    if valid_blocks < 6 || mean_weight < 0.7 || (corneal_thickness_accuracy / 1000) > 0.015
        fprintf(file,'    fptype expected_cor_thickness_%s = 0.0;\n', var_name);
        fprintf(file,'    fptype expected_cor_thickness_acuracy_%s = 0.0;\n', var_name);
        fprintf(file,'    uint16_t expected_valid_blocks_%s = 0;\n', var_name);
    else
        fprintf(file,'    fptype expected_cor_thickness_%s = %.5f;\n', var_name, corneal_thickness);
        fprintf(file,'    fptype expected_cor_thickness_acuracy_%s = %.5f;\n', var_name, corneal_thickness_accuracy);
        fprintf(file,'    uint16_t expected_valid_blocks_%s = %d;\n', var_name, valid_blocks);
    end
    if valid_blocks < 6
        fprintf(file,'    int expected_iret_%s = ERROR_TOO_FEW_BLOCKS;\n', var_name);
    elseif mean_weight < 0.7
        fprintf(file,'    int expected_iret_%s = ERROR_PC_PEAKS_TOO_SMALL;\n', var_name);
    elseif (corneal_thickness_accuracy / 1000) > 0.015
        fprintf(file,'    int expected_iret_%s = ERROR_SPREAD_TOO_HIGH;\n', var_name);
    else
        iret = 0;
        if valid_blocks < 8
            iret = iret + 1;
        end
        if mean_weight < 0.78
            iret = iret + 10;
        end
        if (corneal_thickness_accuracy / 1000) > 0.010
            iret = iret + 100;
        end

        if iret == 0
            fprintf(file,'    int expected_iret_%s = SUCCESS;\n', var_name); 
        elseif iret == 1
            fprintf(file,'    int expected_iret_%s = WARNING_FEW_VALID_BLOCKS;\n', var_name); 
        elseif iret == 10
            fprintf(file,'    int expected_iret_%s = WARNING_PC_PEAKS_SMALL;\n', var_name); 
        elseif iret == 11
            fprintf(file,'    int expected_iret_%s = WARNING_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS;\n', var_name); 
        elseif iret == 100
            fprintf(file,'    int expected_iret_%s = WARNING_HIGH_DATA_SPREAD;\n', var_name); 
        elseif iret == 101
            fprintf(file,'    int expected_iret_%s = WARNING_HIGH_DATA_SPREAD_AND_FEW_VALID_BLOCKS;\n', var_name); 
        elseif iret == 110
            fprintf(file,'    int expected_iret_%s = WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL;\n', var_name); 
        elseif iret == 111
            fprintf(file,'    int expected_iret_%s = WARNING_HIGH_DATA_SPREAD_AND_PC_PEAKS_SMALL_AND_FEW_VALID_BLOCKS;\n', var_name); 
        end
    end
        
    fprintf(file,'\n');
    fprintf(file,'    /* Provide C++ Compatibility */\n');
    fprintf(file,'#ifdef __cplusplus\n');
    fprintf(file,'}\n');
    fprintf(file,'#endif\n');
    fprintf(file,'\n');
    fprintf(file,'#endif //_TEST_M_NPDA_SCAN_DATA_%s_H\n', upper(var_name));

    fclose(file);
    
end