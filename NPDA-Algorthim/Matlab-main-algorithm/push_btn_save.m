function push_btn_save(src, event)

   global save_file; 
   global inputs_valid; 
   global txt_valid;
    
   if inputs_valid == 1
      save_file = 1; 
      inputs_valid  =0; 
   else 
      set(txt_valid, 'String', 'Save Failed: Some inputs are invalid');
   end
    
end

