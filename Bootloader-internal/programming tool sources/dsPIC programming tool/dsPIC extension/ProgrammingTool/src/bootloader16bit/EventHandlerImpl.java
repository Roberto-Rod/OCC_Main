// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.io.Writer;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.nio.BufferUnderflowException;
import java.util.concurrent.ExecutionException;
import java.io.IOException;
import javafx.application.Platform;
import javafx.stage.Modality;
import javafx.scene.control.Alert;
import console16bit.Console16bit;

class EventHandlerImpl implements EventHandler
{
    private ModelProxy modelProxy;
    private Console16bit console;
    private final String tattle = "A software error has occurred. Please see the 'Tools > Console' window for details.";
    
    EventHandlerImpl(final ModelProxy modelProxy, final Console16bit console) {
        this.modelProxy = modelProxy;
        this.console = console;
    }
    
    void showAlert(final String contentText) {
        
        Platform.runLater(() -> {
            final Alert alert;
            alert = new Alert(Alert.AlertType.ERROR);
            alert.setContentText(contentText);
            alert.initModality(Modality.APPLICATION_MODAL);
            alert.showAndWait();
        });
    }
    
    @Override
    public void unsupportedAdapterOperation() {
        this.modelProxy.setResultStatus("");
        this.showAlert("The communications adapter was not able to support an operation requested of it.  Please check the settings to ensure they are compatible with the selected adapter.");
    }
    
    @Override
    public void resetSuccessful() {
        final String msg = "Device reset successful.";
        this.modelProxy.setResultStatus(msg);
        this.console.addConsoleText(msg);
    }
    
    @Override
    public void setProgress(final double percent) {
        this.modelProxy.setProgress(percent);
    }
    
    @Override
    public void resetRequested() {
        final String msg = "Requesting to reset the device...";
        this.modelProxy.setResultStatus(msg);
        this.console.addConsoleText(msg);
    }
    
    @Override
    public void illegalState(final IllegalStateException e) {
        final String msg = e.getMessage();
        this.modelProxy.setResultStatus("Unified Host Bug Found!");
        this.console.addConsoleText(msg + System.lineSeparator() + this.getStackTrace(e));
        this.showAlert(msg);
    }
    
    @Override
    public void checksumFailed(final int recordLine) {
        this.modelProxy.setResultStatus("Hex file is corrupt!");
        final String msg = "Hex file is corrupt! The checksum for line " + recordLine + " did not compute to the correct value.";
        this.console.addConsoleText(msg);
        this.showAlert(msg);
    }
    
    @Override
    public void serialConfigException(final IOException e) {
        final String msg = "Failed to show Serial Configuration!";
        this.modelProxy.setResultStatus(msg);
        this.console.addConsoleText(msg + System.lineSeparator() + this.getStackTrace(e));
        this.showAlert(msg);
    }
    
    @Override
    public void programmingFinished() {
        final String msg = "Programming Finished.";
        this.modelProxy.setResultStatus(msg);
        this.console.addConsoleText(msg);
    }
    
    @Override
    public void programmingStarted() {
        this.modelProxy.setResultStatus("Programming...");
        this.console.addConsoleText("Programming Started.");
    }
    
    @Override
    public void eraseRequested() {
        this.modelProxy.setResultStatus("Erasing...");
        this.console.addConsoleText("Requesting to erase the application.");
    }
    
    @Override
    public void eraseFinished() {
        final String msg = "Finished erasing.";
        this.modelProxy.setResultStatus(msg);
        this.console.addConsoleText(msg);
    }
    
    @Override
    public void finishedEverything() {
        final String msg = "Finished executing requested operations.";
        this.modelProxy.setResultStatus(msg);
        this.console.addConsoleText(msg);
    }
    
    @Override
    public void readBackVerificationRequested() {
        this.modelProxy.setResultStatus("Verifying via read back...");
        this.console.addConsoleText("Verifying the contents of the application space by reading back memory contents...");
    }
    
    @Override
    public void readBackVerificationPassed() {
        final String msg = "Read back verification passed.";
        this.modelProxy.setResultStatus(msg);
        this.console.addConsoleText(msg);
    }
    
    @Override
    public void adapterInUseException(final SerialAdapterInUseException e, final SerialAdapter serialAdapter) {
        this.modelProxy.setResultStatus("Adapter already in use!");
        final String msg = "Failed to open, it is already in use.  " + serialAdapter.getDeviceName();
        this.console.addConsoleText(msg);
        this.showAlert(msg);
    }
    
    @Override
    public void interruptException(final InterruptedException e) {
        this.modelProxy.setResultStatus("");
        this.modelProxy.setProgress(0.0);
        this.showAlert(e.getMessage());
    }
    
    @Override
    public void executionException(final ExecutionException e) {
        this.modelProxy.setResultStatus("");
        this.modelProxy.setProgress(0.0);
        try {
            throw e.getCause();
        }
        catch (BufferUnderflowException e2) {
            final String contentText = "Unable to establish communication with device.  Common issues are incorrect configuration UART/Communication port settings on the PC or incorrect UART/Communication port settings on the device.  Please check and retry.";
            this.showAlert(contentText);
            this.console.addConsoleText(contentText);
        }
        catch (Throwable throwable) {
            this.showAlert("A software error has occurred. Please see the 'Tools > Console' window for details.");
            this.console.addConsoleText("A software error has occurred. Please see the 'Tools > Console' window for details.");
        }
    }
    
    @Override
    public void ioException(final IOException e) {
        this.modelProxy.setResultStatus("");
        this.modelProxy.setProgress(0.0);
        this.console.addConsoleText(this.getStackTrace(e));
        this.showAlert("A software error has occurred. Please see the 'Tools > Console' window for details.");
    }
    
    private String getStackTrace(final Exception e) {
        final StringWriter sw = new StringWriter();
        final PrintWriter pw = new PrintWriter(sw);
        e.printStackTrace(pw);
        return sw.getBuffer().toString();
    }
    
    @Override
    public void timeoutException(final TimeoutException e) {
        final String msg = "Communications timed out, check the console!";
        this.modelProxy.setResultStatus(msg);
        this.modelProxy.setProgress(0.0);
        final StringBuilder sb = new StringBuilder();
        for (final byte b : e.getPartialResponse()) {
            sb.append(String.format("0x%x ", b));
        }
        this.console.addConsoleText("Communications timed out during a read.  This data was in the request buffer: \n" + sb.toString() + " <END>\n");
        this.showAlert(msg);
    }
    
    @Override
    public void badResponse(final Command request, final Command response) {
        final String msg = "Bad response received! Request: " + request.accept((FnCommandVisitor<Command>)new FnNormalize()).accept((FnCommandVisitor<String>)new FnToStringVerbose()) + ", Response: " + response.accept((FnCommandVisitor<Command>)new FnNormalize()).accept((FnCommandVisitor<String>)new FnToStringVerbose());
        this.modelProxy.setResultStatus("Bad response!");
        this.modelProxy.setProgress(0.0);
        this.console.addConsoleText(msg);
        this.showAlert("A bad response was received, check the console for details.");
    }
    
    @Override
    public void readBackVerificationFailed(final int address, final int actual, final int expected) {
        final String msg = String.format("Read back verification failed. At address=0x%08X, actual=0x%08X, expected=0x%08X", address, actual, expected);
        this.modelProxy.setResultStatus("Read back verification failed!");
        this.modelProxy.setProgress(0.0);
        this.console.addConsoleText(msg);
        this.showAlert(msg);
    }
    
    @Override
    public void selfVerificationFailed() {
        final String message = String.format("Self verification failed!", new Object[0]);
        this.modelProxy.setResultStatus(message);
        this.modelProxy.setProgress(0.0);
        this.console.addConsoleText(message);
        this.showAlert(message);
    }
    
    @Override
    public void selfVerificationRequested() {
        this.modelProxy.setResultStatus("Requesting device to self verify...");
        this.console.addConsoleText("Requesting device to self verify the contents of the application space...");
    }
    
    @Override
    public void selfVerificationPassed() {
        final String message = String.format("Self verification passed.", new Object[0]);
        this.modelProxy.setResultStatus(message);
        this.console.addConsoleText(message);
    }
    
    @Override
    public void selfVerificationNotSupported() {
        final String message = String.format("Self verification not supported.", new Object[0]);
        final String detailedMessage = String.format("Self verification not supported.  Please disable this option and try again.", new Object[0]);
        this.modelProxy.setResultStatus(message);
        this.modelProxy.setProgress(0.0);
        this.console.addConsoleText(detailedMessage);
        this.showAlert(detailedMessage);
    }
}
