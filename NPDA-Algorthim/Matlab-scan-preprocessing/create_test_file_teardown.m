function [] = create_test_file_teardown( fileID )

    fprintf(fileID,'/* ************************************************************************** */\n');
    fprintf(fileID,'/** \n');
    fprintf(fileID,' * @brief            This function contains code to be executed after unit\n');
    fprintf(fileID,' *                   tests.\n');
    fprintf(fileID,' *\n');
    fprintf(fileID,' * @note             For testing npda.c nothing needs to be set up. \n');
    fprintf(fileID,' */\n');
    fprintf(fileID,'/* ************************************************************************** */\n');
    fprintf(fileID,'void tearDown(void)\n');
    fprintf(fileID,'{\n');
    fprintf(fileID,'}\n');
    fprintf(fileID,'\n');

end