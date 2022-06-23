// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.regex.Matcher;
import javafx.beans.value.ObservableValue;
import javafx.application.Platform;
import java.util.regex.Pattern;
import java.util.function.Consumer;
import java.util.Observer;
import javafx.beans.value.ChangeListener;
import java.util.Observable;
import java.util.ResourceBundle;
import java.net.URL;
import javafx.event.ActionEvent;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.fxml.FXML;
import javafx.scene.control.ProgressBar;
import javafx.fxml.Initializable;

class Bootloader16Controller implements Initializable
{
    @FXML
    public ProgressBar progress;
    @FXML
    public TextField endAddress;
    @FXML
    public TextField startAddress;
    @FXML
    public Label labelStatusResult;
    @FXML
    public Label labelConfigStatus;
    @FXML
    public Button programButton;
    @FXML
    public CheckBox resetCheckBox;
    @FXML
    public CheckBox readBackVerifyCheckBox;
    @FXML
    public CheckBox selfVerifyCheckBox;
    private final Bootloader16Model model;
    
    public Bootloader16Controller(final Bootloader16Model model) {
        this.model = model;
    }
    
    @FXML
    public void programDevice(final ActionEvent actionEvent) {
        this.model.program();
    }
    
    @FXML
    public void readDeviceSettings(final ActionEvent actionEvent) {
        this.model.readDeviceSettings();
    }
    
    public void initialize(final URL location, final ResourceBundle resources) {
        final Observer modelObserver = new Bootloader16ModelObserver(d -> this.fx(() -> this.progress.progressProperty().set((double)d)), s0 -> this.fx(() -> this.labelStatusResult.setText(s0)), s1 -> this.fx(() -> this.labelConfigStatus.setText(s1)), b -> this.fx(() -> this.programButton.setDisable((boolean)b)), sa -> this.fx(() -> this.startAddress.setText(String.format("0x%04X", sa))), ea -> this.fx(() -> this.endAddress.setText(String.format("0x%04X", ea))));
        this.model.addObserver(modelObserver);
        modelObserver.update(this.model, null);
        this.startAddress.setText(String.format("0x%04X", this.model.getStartAddress()));
        this.endAddress.setText(String.format("0x%04X", this.model.getEndAddress()));
        this.startAddress.textProperty().addListener((ChangeListener)this.getValue(this.model::setStartAddress));
        this.endAddress.textProperty().addListener((ChangeListener)this.getValue(this.model::setEndAddress));
        this.resetCheckBox.selectedProperty().addListener((observable, oldValue, newValue) -> this.model.setResetEnabled(newValue));
        this.readBackVerifyCheckBox.selectedProperty().addListener((observable, oldValue, newValue) -> this.model.setReadBackVerifyEnabled(newValue));
        this.selfVerifyCheckBox.selectedProperty().addListener((observable, oldValue, newValue) -> this.model.setSelfVerifyEnabled(newValue));
    }
    
    private ChangeListener<String> getValue(final Consumer<Integer> consumer) {
        final Pattern compile = Pattern.compile("(\\s*)?(0x)?(?<value>[0-9a-fA-F]+)\\s*?");
        return (ChangeListener<String>)((observable, oldValue, newValue) -> {
            final Matcher matcher = compile.matcher(newValue);
            if (matcher.matches()) {
                consumer.accept(Integer.parseInt(matcher.group("value"), 16));
            }
        });
    }
    
    private void fx(final Runnable runnable) {
        if (Platform.isFxApplicationThread()) {
            runnable.run();
        }
        else {
            Platform.runLater(runnable);
        }
    }
    
    private static class Bootloader16ModelObserver implements Observer
    {
        private final Consumer<Double> progress;
        private final Consumer<String> statusResult;
        private final Consumer<String> configState;
        private final Consumer<Boolean> programDisable;
        private final Consumer<Integer> startAddress;
        private final Consumer<Integer> endAddress;
        
        Bootloader16ModelObserver(final Consumer<Double> progress, final Consumer<String> statusResult, final Consumer<String> configState, final Consumer<Boolean> programDisable, final Consumer<Integer> startAddress, final Consumer<Integer> endAddress) {
            this.progress = progress;
            this.statusResult = statusResult;
            this.configState = configState;
            this.programDisable = programDisable;
            this.startAddress = startAddress;
            this.endAddress = endAddress;
        }
        
        @Override
        public void update(final Observable o, final Object arg) {
            if (o instanceof Bootloader16Model) {
                final Bootloader16Model model = (Bootloader16Model)o;
                this.progress.accept(model.getProgress());
                this.statusResult.accept(model.getStatusResult());
                this.configState.accept(model.getConfigState());
                this.programDisable.accept(model.getProgramDisable());
                this.startAddress.accept(model.getStartAddress());
                this.endAddress.accept(model.getEndAddress());
            }
        }
    }
}
