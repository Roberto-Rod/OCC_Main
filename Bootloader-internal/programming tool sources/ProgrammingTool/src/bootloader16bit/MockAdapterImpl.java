// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Collection;
import java.util.ArrayList;
import java.util.List;
import java.io.IOException;
import java.nio.channels.ByteChannel;
import java.util.Map;
import console16bit.Console16bit;

public class MockAdapterImpl implements SerialAdapter
{
    private final Console16bit console;
    private final Map<String, MockTarget> mocks;
    private Integer baudRate;
    private String deviceName;
    private ByteChannel byteChannel;
    
    public MockAdapterImpl(final Console16bit console, final Map<String, MockTarget> mocks) {
        this.console = console;
        this.mocks = mocks;
    }
    
    @Override
    public void reportToConsole() {
    }
    
    @Override
    public AdapterStats getAdapterStats() {
        return this.mocks.get(this.deviceName).getAdapterStats();
    }
    
    @Override
    public String getPort() {
        return this.deviceName;
    }
    
    @Override
    public Integer getBaudRate() {
        return this.baudRate;
    }
    
    @Override
    public ByteChannel getChannel() throws IOException {
        return new MockTargetWrapperImpl(this.mocks.get(this.deviceName));
    }
    
    @Override
    public void open() {
    }
    
    @Override
    public void close() {
    }
    
    @Override
    public void setBaudRate(final Integer baudRate) {
        this.baudRate = baudRate;
    }
    
    @Override
    public void setDeviceName(final String deviceName) {
        this.deviceName = deviceName;
    }
    
    @Override
    public String getDeviceName() {
        return this.deviceName;
    }
    
    @Override
    public boolean isDeviceNameSet() {
        return this.deviceName != null && !this.deviceName.isEmpty();
    }
    
    @Override
    public List<String> getPorts() {
        return new ArrayList<String>(this.mocks.keySet());
    }
}
