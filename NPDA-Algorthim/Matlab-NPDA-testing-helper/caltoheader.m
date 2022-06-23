function [] = caltoheader( data_in, cal_var_name, file_out, file_out_path )
%CALTOHEADER Creates header file with cal data compatible with ceedling tests

    file = fopen(file_out_path,'w');

    cal_data_len = 5000;
    data_in_one_row = 500;

    %First, create some static file sections
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'/** @file %s\n', file_out);
    fprintf(file,' *\n');
    fprintf(file,' *  @brief Calibration data for testing npda.c module.\n');
    fprintf(file,' *\n');
    fprintf(file,' *  @copyright Occuity Limited (c) 2020\n');
    fprintf(file,' *\n');
    fprintf(file,' */\n');
    fprintf(file,'/* ************************************************************************** */');
    fprintf(file,'\n');
    fprintf(file,'#ifndef _%s_H    /* Guard against multiple inclusion */\n', upper(cal_var_name));
    fprintf(file,'#define _%s_H\n', upper(cal_var_name));
    fprintf(file,'\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'/* Section: Included Files                                                    */\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'\n');
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
    fprintf(file,'    const fptype cal_data_%s[%d] = {', cal_var_name, cal_data_len);

    writeformatteddata(file, data_in, cal_data_len, data_in_one_row, 'float');

    fprintf(file,'};\n');
    fprintf(file,'\n');
    fprintf(file,'    /* ************************************************************************** */\n');
    fprintf(file,'    /* ************************************************************************** */\n');
    fprintf(file,'    /* Section: Interface Functions                                               */\n');
    fprintf(file,'    /* ************************************************************************** */\n');
    fprintf(file,'    /* ************************************************************************** */\n');
    fprintf(file,'\n');
    fprintf(file,'    /* Provide C++ Compatibility */\n');
    fprintf(file,'#ifdef __cplusplus\n');
    fprintf(file,'}\n');
    fprintf(file,'#endif\n');
    fprintf(file,'\n');
    fprintf(file,'#endif /* _%s_H */\n', upper(cal_var_name));
    fprintf(file,'/* ************************************************************************** */\n');
    fprintf(file,'/* Section: End of File                                                       */\n');
    fprintf(file,'/* ************************************************************************** */\n');
    fclose(file);

end

