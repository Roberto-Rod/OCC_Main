// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.List;

class SerialAdapterBuilderImpl implements SerialAdapterBuilder
{
    private final SerialAdapterFactory factory;
    private SerialAdapter serialAdapter;
    private Integer baudRate;
    private String serialPortName;
    private boolean mockEnable;
    private AdapterStats adapterStats;
    
    SerialAdapterBuilderImpl(final SerialAdapterFactory factory) {
        this.factory = factory;
        this.baudRate = 9600;
        this.mockEnable = false;
        this.serialPortName = "";
        this.build();
    }
    
    @Override
    public void build() {
        if (this.mockEnable) {
            this.serialAdapter = this.factory.makeMockAdapter();
        }
        else {
            this.serialAdapter = this.factory.makeSerialAdapter();
        }
        this.serialAdapter.setBaudRate(this.baudRate);
        if (this.serialPortName.isEmpty()) {
            final List<String> ports = this.serialAdapter.getPorts();
            if (!ports.isEmpty()) {
                this.serialAdapter.setDeviceName(ports.get(0));
            }
        }
        else {
            this.serialAdapter.setDeviceName(this.serialPortName);
        }
        this.serialAdapter.reportToConsole();
        this.adapterStats = this.serialAdapter.getAdapterStats();
    }
    
    @Override
    public AdapterStats getAdapterStats() {
        return this.adapterStats;
    }
    
    @Override
    public String getPort() {
        return this.serialAdapter.getPort();
    }
    
    @Override
    public Integer getBaudRate() {
        return this.serialAdapter.getBaudRate();
    }
    
    @Override
    public void setSerialPortName(final String serialPortName) {
        this.serialPortName = serialPortName;
    }
    
    @Override
    public void setBaudRate(final Integer baudRate) {
        this.baudRate = baudRate;
    }
    
    @Override
    public void setMockEnable(final boolean mockEnable) {
        this.mockEnable = mockEnable;
    }
    
    @Override
    public SerialAdapter getSerialAdapter() {
        return this.serialAdapter;
    }
    
    @Override
    public boolean getMockEnable() {
        return this.mockEnable;
    }
}
