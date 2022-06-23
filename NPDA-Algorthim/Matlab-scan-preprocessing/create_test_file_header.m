function [] = create_test_file_header( fileID, filename, brief, header_filenames )

    fprintf(fileID,'/* ************************************************************************** */\n');
    fprintf(fileID,'/** @file %s\n', filename);
    fprintf(fileID,' *\n');
    fprintf(fileID,' *  @brief %s.\n', brief);
    fprintf(fileID,' *\n');
    fprintf(fileID,' *  @copyright Occuity Limited (c) 2021\n');
    fprintf(fileID,' */\n');
    fprintf(fileID,'/* ************************************************************************** */\n');
    fprintf(fileID,'\n');
    fprintf(fileID,'#ifndef TEST_FILE_C /* Guard against accidental multiple inclusion */\n');
    fprintf(fileID,'#define TEST_FILE_C\n');
    fprintf(fileID,'\n');
    fprintf(fileID,'/* ************************************************************************** */\n');
    fprintf(fileID,'/* Section: Included Files                                                    */\n');
    fprintf(fileID,'/* ************************************************************************** */\n');
    fprintf(fileID,'\n');
    fprintf(fileID,'/* Header file for selective initialisation of hardware modules. */\n');
    fprintf(fileID,'#include "init_minimum_plus_timer.h" \n');
    fprintf(fileID,'/* Library containing the test harness. */\n');
    fprintf(fileID,'#include "unity.h" \n');
    fprintf(fileID,'/* Header file for memory monitoring. */\n');
    fprintf(fileID,'#include "stack_monitoring.h"\n');
    fprintf(fileID,'\n');
    fprintf(fileID,'/* ************************************************************************** */\n');
    fprintf(fileID,'/* Include additional files to compile here                                   */\n');
    fprintf(fileID,'/* ************************************************************************** */\n');
    fprintf(fileID,'//TEST_FILE("file_to_compile.c")\n');
    fprintf(fileID,'\n');
    fprintf(fileID,'/* ************************************************************************** */\n');
    fprintf(fileID,'/* Include files to test here                                                 */\n');
    fprintf(fileID,'/* ************************************************************************** */\n');
    for i=1:length(header_filenames)
        fprintf(fileID,'#include "%s"\n', header_filenames{i});
    end
    
end