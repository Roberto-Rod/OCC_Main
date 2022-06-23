function [ output_args ] = caltoheader( data )
%CALTOHEADER Converts Cal lookup.csv to header file
%   Usage: caltoheader(csvread('Cal lookup.csv'))
%   Uses second column from the "Cal lookup.csv" file.
%   Uses only first 5000 points - ignores the rest if present.
%   Assumes no header rows in the "Cal lookup.csv" file.

file = fopen('calibration_data.h','w');

fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/** @file calibration.h\n');
fprintf(file,' *\n');
fprintf(file,' *  @brief Contains calibration data for the specific P1 Pachymeter unit.\n');
fprintf(file,' *\n');
fprintf(file,' *  @copyright Occuity Limited (c) 2021.\n');
fprintf(file,' */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'\n');
fprintf(file,'#ifndef _CALIBRATION_H    /* Guard against multiple inclusion */\n');
fprintf(file,'#define _CALIBRATION_H\n');
fprintf(file,'\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* Section: Included Files                                                    */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'\n');
fprintf(file,'/* Provide C++ Compatibility */\n');
fprintf(file,'#ifdef __cplusplus\n');
fprintf(file,'extern "C" {\n');
fprintf(file,'#endif\n');
fprintf(file,'\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* Section: Global data types                                                 */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* Section: Global variables                                                  */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* ************************************************************************** */\n');

j = 2; % Use second column

x = data(1:5000,j);

i=0;

fprintf(file,'static const float cal_data[PDAB_SCAN_LENGTH_16] = { %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f,\n', x(i+1), x(i+2), x(i+3), x(i+4), x(i+5), x(i+6), x(i+7), x(i+8), x(i+9), x(i+10) );

for k = 1:1:(length(x)-20)/10
    i = k*10;
    fprintf(file,'                                                     %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f,\n', x(i+1), x(i+2), x(i+3), x(i+4), x(i+5), x(i+6), x(i+7), x(i+8), x(i+9), x(i+10) );
end
i = length(x)-10;

fprintf(file,'                                                     %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f, %0.5f };\n', x(i+1), x(i+2), x(i+3), x(i+4), x(i+5), x(i+6), x(i+7), x(i+8), x(i+9), x(i+10) );

fprintf(file,'\n');
fprintf(file,'\n');


fprintf(file,'\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* Section: Interface functions                                               */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'/* ************************************************************************** */\n');
fprintf(file,'\n');
fprintf(file,'/* Provide C++ Compatibility */\n');
fprintf(file,'#ifdef __cplusplus\n');
fprintf(file,'}\n');
fprintf(file,'#endif\n');
fprintf(file,'\n');
fprintf(file,'#endif /* _CALIBRATION_H */\n');
fprintf(file,'\n');
fprintf(file,'/* ************************************************************************** */\n');
fclose(file);

end

