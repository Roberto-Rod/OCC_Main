// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.io.IOException;

class ReadDeviceDataFastImpl implements Runnable
{
    private final ModelProxy model;
    private final Target target;
    private EventHandler eventHandler;
    
    ReadDeviceDataFastImpl(final Bootloader16AbstractFactory factory, final ModelProxy model, final Target target, final EventHandler eventHandler) {
        this.model = model;
        this.target = target;
        this.eventHandler = eventHandler;
    }
    
    @Override
    public void run() {
        try {
            this.flushInput();
            this.getDeviceData();
            this.eventHandler.finishedEverything();
        }
        catch (IOException e) {
            this.eventHandler.ioException(e);
        }
        catch (TimeoutException e2) {
            this.eventHandler.timeoutException(e2);
        }
        catch (IllegalStateException e3) {
            this.eventHandler.illegalState(e3);
        }
        catch (BadResponseException e4) {
            this.eventHandler.badResponse(e4.getRequest(), e4.getResponse());
        }
    }
    
    private void flushInput() throws IOException {
        this.target.flushInput();
    }
    
    private void getDeviceData() throws IOException, TimeoutException, BadResponseException {
        final Command deviceData = this.target.getDeviceData();
        this.model.setMemoryRange(this.getStartAddress(deviceData), this.getEndAddress(deviceData));
    }
    
    private Integer getStartAddress(final Command deviceData) {
        return deviceData.accept((FnCommandVisitor<Integer>)new FnProgramStartAddressAccessor());
    }
    
    private Integer getEndAddress(final Command deviceData) {
        return deviceData.accept((FnCommandVisitor<Integer>)new FnProgramEndAddressAccessor());
    }
}
