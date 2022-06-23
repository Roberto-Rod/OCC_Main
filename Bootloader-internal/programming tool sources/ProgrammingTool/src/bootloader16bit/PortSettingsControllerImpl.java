// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.ArrayList;
import java.util.List;
import javafx.scene.Node;
import javafx.scene.image.ImageView;
import javafx.scene.image.Image;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import java.util.ResourceBundle;
import java.net.URL;
import java.util.Collection;
import javafx.event.ActionEvent;
import javafx.beans.value.ChangeListener;
import javafx.collections.ObservableList;
import javafx.beans.property.SimpleObjectProperty;
import javafx.stage.Stage;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.Button;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;

public class PortSettingsControllerImpl implements PortSettingsController
{
    @FXML
    public ComboBox<Integer> comboBaud;
    @FXML
    public ComboBox<String> comboDataBits;
    @FXML
    public ComboBox<String> comboStopBits;
    @FXML
    public ComboBox<String> comboParity;
    @FXML
    public Button settingUpdate;
    @FXML
    public Label labelComPort;
    @FXML
    public Button buttonRefresh;
    @FXML
    public ComboBox<String> comboComPort;
    @FXML
    public CheckBox mockEnable;
    private final Stage dialogStage;
    private final PortModel model;
    private SimpleObjectProperty<ObservableList<Integer>> comboBaudTimes;
    private SimpleObjectProperty<ObservableList<String>> comboComPortItems;
    private ChangeListener<String> comboComPortCL;
    private ChangeListener<Integer> comboBaudCL;
    private ChangeListener<Boolean> mockEnableCL;
    
    PortSettingsControllerImpl(final Stage stage, final PortModel model) {
        this.dialogStage = stage;
        this.model = model;
        this.comboComPortCL = (ChangeListener<String>)((observable, oldValue, newValue) -> model.setSerialPortName(newValue));
        this.comboBaudCL = (ChangeListener<Integer>)((observable, oldValue, newValue) -> model.setBaudRate(newValue));
        this.mockEnableCL = (ChangeListener<Boolean>)((observable, oldValue, newValue) -> {
            model.setMockEnable(newValue);
            ((ObservableList)this.comboComPortItems.get()).setAll((Collection)model.getPorts());
            this.comboComPort.getSelectionModel().select(0);
        });
    }
    
    @FXML
    @Override
    public void actionApplySettings(final ActionEvent actionEvent) {
        this.dialogStage.close();
        this.model.buildAdapter();
    }
    
    @FXML
    @Override
    public void actionRefreshComList(final ActionEvent actionEvent) {
        this.removeListeners();
        ((ObservableList)this.comboComPortItems.get()).setAll((Collection)this.model.getPorts());
        this.comboComPort.getSelectionModel().select((Object)this.model.getPort());
        this.addListeners();
    }
    
    @Override
    public void initialize(final URL location, final ResourceBundle resources) {
        this.renderRefreshButton();
        this.renderComboParity();
        this.renderComboStopBits();
        this.renderComboDataBits();
        (this.comboComPortItems = (SimpleObjectProperty<ObservableList<String>>)new SimpleObjectProperty((Object)FXCollections.observableArrayList())).bind((ObservableValue)this.comboComPort.itemsProperty());
        ((ObservableList)this.comboComPortItems.get()).setAll((Collection)this.model.getPorts());
        this.comboComPort.getSelectionModel().select((Object)this.model.getPort());
        (this.comboBaudTimes = (SimpleObjectProperty<ObservableList<Integer>>)new SimpleObjectProperty((Object)FXCollections.observableArrayList())).bind((ObservableValue)this.comboBaud.itemsProperty());
        ((ObservableList)this.comboBaudTimes.get()).setAll((Collection)this.getIntegers());
        this.comboBaud.getSelectionModel().select((Object)this.model.getBaudRate());
        this.mockEnable.setSelected(this.model.getMockEnable());
        this.mockEnable.setDisable(true);
        this.addListeners();
    }
    
    private void addListeners() {
        this.comboComPort.getSelectionModel().selectedItemProperty().addListener((ChangeListener)this.comboComPortCL);
        this.comboBaud.getSelectionModel().selectedItemProperty().addListener((ChangeListener)this.comboBaudCL);
        this.mockEnable.selectedProperty().addListener((ChangeListener)this.mockEnableCL);
    }
    
    private void removeListeners() {
        this.comboComPort.getSelectionModel().selectedItemProperty().removeListener((ChangeListener)this.comboComPortCL);
        this.comboBaud.getSelectionModel().selectedItemProperty().removeListener((ChangeListener)this.comboBaudCL);
        this.mockEnable.selectedProperty().removeListener((ChangeListener)this.mockEnableCL);
    }
    
    private void renderComboParity() {
        this.comboParity.getItems().clear();
        this.comboParity.getItems().add((Object)"Disabled");
        this.comboParity.getSelectionModel().select(0);
        this.comboParity.setDisable(true);
    }
    
    private void renderComboStopBits() {
        this.comboStopBits.getItems().clear();
        this.comboStopBits.getItems().add((Object)"1");
        this.comboStopBits.getSelectionModel().select(0);
        this.comboStopBits.setDisable(true);
    }
    
    private void renderComboDataBits() {
        this.comboDataBits.getItems().clear();
        this.comboDataBits.getItems().add((Object)"8");
        this.comboDataBits.getSelectionModel().select(0);
        this.comboDataBits.setDisable(true);
    }
    
    private void renderRefreshButton() {
        final Image imageRefresh = new Image(this.getClass().getResourceAsStream("/portSettings/refreshIcon.png"));
        final ImageView imageButtonRefresh = new ImageView();
        imageButtonRefresh.setImage(imageRefresh);
        imageButtonRefresh.setFitWidth(20.0);
        imageButtonRefresh.setPreserveRatio(true);
        imageButtonRefresh.setSmooth(true);
        imageButtonRefresh.setCache(true);
        this.buttonRefresh.setGraphic((Node)imageButtonRefresh);
    }
    
    private List<Integer> getIntegers() {
        final List<Integer> rates = new ArrayList<Integer>();
        rates.add(1200);
        rates.add(2400);
        rates.add(4800);
        rates.add(9600);
        rates.add(19200);
        rates.add(38400);
        rates.add(57600);
        rates.add(115200);
        rates.add(230400);
        rates.add(460800);
        return rates;
    }
}
