// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.List;
import java.io.IOException;
import java.nio.channels.ByteChannel;

interface SerialAdapter
{
    void reportToConsole();
    
    AdapterStats getAdapterStats();
    
    String getPort();
    
    Integer getBaudRate();
    
    ByteChannel getChannel() throws IOException;
    
    void open() throws SerialAdapterInUseException, UnsupportedSerialAdapterOperationException;
    
    void close();
    
    void setBaudRate(final Integer p0);
    
    void setDeviceName(final String p0);
    
    String getDeviceName();
    
    boolean isDeviceNameSet();
    
    List<String> getPorts();
}
