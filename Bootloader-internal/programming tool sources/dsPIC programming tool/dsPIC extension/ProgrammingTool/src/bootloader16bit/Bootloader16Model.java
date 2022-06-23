// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Iterator;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.nio.channels.ByteChannel;
import java.util.concurrent.Future;
import java.io.IOException;
import javafx.scene.Scene;
import javafx.scene.Parent;
import javafx.stage.Modality;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import java.util.HashMap;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicBoolean;
import java.io.File;
import java.util.Map;
import console16bit.Console16bit;
import java.util.Observable;

public class Bootloader16Model extends Observable implements PortModel
{
    private final Bootloader16AbstractFactory factory;
    private final HexParser hexParser;
    private final int DEFAULT_APP_START = 12288;
    private final int DEFAULT_APP_END = 45056;
    private final Console16bit console;
    private final SerialAdapterBuilder adapterBuilder;
    @GuardBy("this")
    private Double progress;
    @GuardBy("this")
    private String configStatus;
    @GuardBy("this")
    private int startAddress;
    @GuardBy("this")
    private int endAddress;
    @GuardBy("this")
    private String statusResult;
    @GuardBy("this")
    private boolean resetEnabled;
    @GuardBy("this")
    private boolean readBackVerifyEnabled;
    @GuardBy("this")
    private boolean selfVerifyEnabled;
    @GuardBy("this")
    private final Map<Integer, Integer> parse;
    @GuardBy("this")
    private File hexFile;
    @GuardBy("self")
    private AtomicBoolean isProgramming;
    private final ExecutorService service;
    
    Bootloader16Model(final Bootloader16AbstractFactory factory, final HexParser hexParser, final Console16bit console) {
        this.service = Executors.newSingleThreadExecutor();
        this.factory = factory;
        this.parse = new HashMap<Integer, Integer>();
        this.startAddress = 12288;
        this.endAddress = 45056;
        this.resetEnabled = true;
        this.readBackVerifyEnabled = true;
        this.selfVerifyEnabled = false;
        this.hexParser = hexParser;
        this.console = console;
        this.progress = 0.0;
        this.adapterBuilder = factory.makeAdapterBuilder(console);
        this.isProgramming = new AtomicBoolean(false);
    }
    
    public void setHexFileName(final File hexFile) {
        this.parse.clear();
        this.hexFile = hexFile;
        this.setChanged();
        this.notifyObservers();
        this.console.addConsoleText("Selected Hex File: " + hexFile.getPath());
    }
    
    private File getHexFile() {
        return this.hexFile;
    }
    
    public void showSerialConfig() {
        try {
            final Stage dialogStage = new Stage();
            final FXMLLoader loader = new FXMLLoader(this.getClass().getResource("/unified/bootloader16bit/PortSettingsFXML.fxml"));
            loader.setControllerFactory(param -> new PortSettingsControllerImpl(dialogStage, this));
            dialogStage.initModality(Modality.APPLICATION_MODAL);
            dialogStage.setScene(new Scene((Parent)loader.load()));
            dialogStage.setTitle("Port Settings");
            dialogStage.showAndWait();
            this.setChanged();
            this.notifyObservers();
        }
        catch (IOException e) {
            final EventHandler eventHandler = this.factory.makeEventHandler(new ModelProxyImpl(this), this.console);
            eventHandler.serialConfigException(e);
        }
    }
    
    public Future<?> program() {
        final EventHandler eventHandler = this.factory.makeEventHandler(new ModelProxyImpl(this), this.console);
        final SerialAdapter serialAdapter = this.adapterBuilder.getSerialAdapter();
        try {
            serialAdapter.open();
            final ByteChannel channel = serialAdapter.getChannel();
            final Target target = this.factory.makeTarget(channel);
            final ModelProxy modelProxy = new ModelProxyImpl(this);
            this.service.submit(this.notifyProgrammingStarted());
            final Future<?> programFuture = this.service.submit(this.factory.makeProgrammer(modelProxy, eventHandler, target));
            this.service.submit(this.makeExceptionHandler(programFuture, eventHandler));
            final Future<?> closeFuture = this.service.submit(serialAdapter::close);
            this.service.submit(this.notifyProgrammingStopped());
            return this.service.submit(this.makeExceptionHandler(closeFuture, eventHandler));
        }
        catch (SerialAdapterInUseException e) {
            eventHandler.adapterInUseException(e, serialAdapter);
        }
        catch (UnsupportedSerialAdapterOperationException e3) {
            eventHandler.unsupportedAdapterOperation();
        }
        catch (IOException e2) {
            eventHandler.ioException(e2);
        }
        return this.service.submit(() -> {});
    }
    
    public Future<?> readDeviceSettings() {
        final EventHandler eventHandler = this.factory.makeEventHandler(new ModelProxyImpl(this), this.console);
        final SerialAdapter serialAdapter = this.adapterBuilder.getSerialAdapter();
        try {
            serialAdapter.open();
            final ByteChannel channel = serialAdapter.getChannel();
            final Target target = this.factory.makeTarget(channel);
            final ModelProxy modelProxy = new ModelProxyImpl(this);
            this.service.submit(this.notifyProgrammingStarted());
            final Future<?> programFuture = this.service.submit(this.factory.makeDeviceReader(modelProxy, eventHandler, target));
            this.service.submit(this.makeExceptionHandler(programFuture, eventHandler));
            final Future<?> closeFuture = this.service.submit(serialAdapter::close);
            this.service.submit(this.notifyProgrammingStopped());
            return this.service.submit(this.makeExceptionHandler(closeFuture, eventHandler));
        }
        catch (SerialAdapterInUseException e) {
            eventHandler.adapterInUseException(e, serialAdapter);
        }
        catch (UnsupportedSerialAdapterOperationException e3) {
            eventHandler.unsupportedAdapterOperation();
        }
        catch (IOException e2) {
            eventHandler.ioException(e2);
        }
        return this.service.submit(() -> {});
    }
    
    Runnable notifyProgrammingStopped() {
        return () -> {
            this.isProgramming.set(false);
            this.setChanged();
            this.notifyObservers();
        };
    }
    
    Runnable notifyProgrammingStarted() {
        return () -> {
            this.isProgramming.set(true);
            this.setChanged();
            this.notifyObservers();
        };
    }
    
    private Runnable makeExceptionHandler(final Future<?> submit, final EventHandler eventHandler) {
        return () -> {
            try {
                submit.get();
            }
            catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                eventHandler.interruptException(e);
            }
            catch (ExecutionException e2) {
                eventHandler.executionException(e2);
            }
        };
    }
    
    synchronized boolean isResetEnabled() {
        return this.resetEnabled;
    }
    
    synchronized void setResetEnabled(final boolean isEnabled) {
        this.resetEnabled = isEnabled;
    }
    
    synchronized boolean isReadBackVerifyEnabled() {
        return this.readBackVerifyEnabled;
    }
    
    synchronized boolean isSelfVerifyEnabled() {
        return this.selfVerifyEnabled;
    }
    
    synchronized void setReadBackVerifyEnabled(final boolean isEnabled) {
        this.readBackVerifyEnabled = isEnabled;
    }
    
    synchronized void setSelfVerifyEnabled(final boolean isEnabled) {
        this.selfVerifyEnabled = isEnabled;
    }
    
    public synchronized Double getProgress() {
        return this.progress;
    }
    
    synchronized String getStatusResult() {
        return this.statusResult;
    }
    
    synchronized String getConfigState() {
        return this.configStatus;
    }
    
    public synchronized void setProgress(final double progress) {
        this.progress = progress;
        this.setChanged();
        this.notifyObservers();
    }
    
    public synchronized int getStartAddress() {
        return this.startAddress;
    }
    
    public synchronized int getEndAddress() {
        return this.endAddress;
    }
    
    public synchronized void setMemoryRange(final int startAddress, final int endAddress) {
        this.startAddress = startAddress;
        this.endAddress = endAddress;
        this.setChanged();
        this.notifyObservers();
    }
    
    public synchronized void setStartAddress(final int startAddress) {
        this.startAddress = startAddress;
        this.setChanged();
        this.notifyObservers();
    }
    
    public synchronized void setEndAddress(final int endAddress) {
        this.endAddress = endAddress;
        this.setChanged();
        this.notifyObservers();
    }
    
    synchronized void setStatusResult(final String message) {
        this.statusResult = message;
        this.setChanged();
        this.notifyObservers();
    }
    
    public synchronized Map<Integer, Integer> getImage() throws ChecksumException {
        try {
            this.parse.clear();
            this.parse.putAll(this.hexParser.parse(this.getHexFile().toPath()));
            return this.parse;
        }
        catch (IOException e) {
            throw new IllegalStateException(e);
        }
    }
    
    Boolean getProgramDisable() {
        final File hexFile = this.getHexFile();
        return !this.adapterBuilder.getSerialAdapter().isDeviceNameSet() || hexFile == null || !hexFile.exists() || this.isProgramming.get();
    }
    
    public void displayConsole() {
        this.console.displayConsole();
    }
    
    @Override
    public void setBaudRate(final Integer baudRate) {
        this.adapterBuilder.setBaudRate(baudRate);
        this.setChanged();
        this.notifyObservers();
    }
    
    @Override
    public List<String> getPorts() {
        return this.adapterBuilder.getSerialAdapter().getPorts();
    }
    
    @Override
    public void buildAdapter() {
        this.adapterBuilder.build();
    }
    
    @Override
    public String getPort() {
        return this.adapterBuilder.getPort();
    }
    
    @Override
    public boolean getMockEnable() {
        return this.adapterBuilder.getMockEnable();
    }
    
    @Override
    public int getBaudRate() {
        return this.adapterBuilder.getBaudRate();
    }
    
    @Override
    public void setSerialPortName(final String serialPortName) {
        this.adapterBuilder.setSerialPortName(serialPortName);
        this.setChanged();
        this.notifyObservers();
    }
    
    @Override
    public void setMockEnable(final boolean mockEnable) {
        this.adapterBuilder.setMockEnable(mockEnable);
        this.setChanged();
        this.notifyObservers();
    }
    
    public AdapterStats getAdapterStats() {
        return this.adapterBuilder.getAdapterStats();
    }
    
    Map<Integer, Integer> getFilteredImage() throws ChecksumException {
        final Map<Integer, Integer> image = this.getImage();
        final Map<Integer, Integer> image2 = new HashMap<Integer, Integer>();
        for (final Map.Entry<Integer, Integer> e : image.entrySet()) {
            final Integer addr = e.getKey();
            if (addr >= this.getStartAddress() && addr < this.getEndAddress()) {
                image2.put(e.getKey(), e.getValue());
            }
        }
        return image2;
    }
}
