// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public interface SerialAdapterBuilder
{
    void build();
    
    AdapterStats getAdapterStats();
    
    String getPort();
    
    void setBaudRate(final Integer p0);
    
    Integer getBaudRate();
    
    void setSerialPortName(final String p0);
    
    void setMockEnable(final boolean p0);
    
    SerialAdapter getSerialAdapter();
    
    boolean getMockEnable();
}
