if exist ".\FW\DAR_app.hex" del ".\FW\DAR_app.hex"
if exist "PIB_Firmware.X.production.hex" ren "PIB_Firmware.X.production.hex" "DAR_app.hex"
if exist "DAR_app.hex" move "DAR_app.hex" ".\FW\DAR_app.hex"