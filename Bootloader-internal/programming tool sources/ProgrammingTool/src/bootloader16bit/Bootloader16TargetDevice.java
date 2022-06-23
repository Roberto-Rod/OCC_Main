// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.io.IOException;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;

public class Bootloader16TargetDevice
{
    private final Bootloader16Model bootloader16Model;
    
    public Bootloader16TargetDevice(final Bootloader16AbstractFactory factory) {
        this.bootloader16Model = factory.makeBootloader16Model();
    }
    
    public Parent getViewer() {
        try {
            final FXMLLoader fxmlLoader = new FXMLLoader(this.getClass().getResource("bootloader16.fxml"));
            fxmlLoader.setControllerFactory(param -> new Bootloader16Controller(this.getModel()));
            return (Parent)fxmlLoader.load();
        }
        catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }
    
    public Bootloader16Model getModel() {
        return this.bootloader16Model;
    }
}
