// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.List;

interface PortModel
{
    void buildAdapter();
    
    String getPort();
    
    boolean getMockEnable();
    
    int getBaudRate();
    
    List<String> getPorts();
    
    void setMockEnable(final boolean p0);
    
    void setBaudRate(final Integer p0);
    
    void setSerialPortName(final String p0);
}
