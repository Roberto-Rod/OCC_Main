function [] = create_test_file_footer( fileID )
    fprintf(fileID,'#endif //TEST_FILE_C\n');
end