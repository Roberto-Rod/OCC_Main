// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.ResourceBundle;
import java.net.URL;
import javafx.fxml.FXML;
import javafx.event.ActionEvent;
import javafx.fxml.Initializable;

interface PortSettingsController extends Initializable
{
    @FXML
    void actionApplySettings(final ActionEvent p0);
    
    @FXML
    void actionRefreshComList(final ActionEvent p0);
    
    void initialize(final URL p0, final ResourceBundle p1);
}
