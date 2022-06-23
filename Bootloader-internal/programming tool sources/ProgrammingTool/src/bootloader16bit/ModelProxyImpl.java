// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Map;

class ModelProxyImpl implements ModelProxy
{
    private final Bootloader16Model bootloader16Model;
    
    ModelProxyImpl(final Bootloader16Model bootloader16Model) {
        this.bootloader16Model = bootloader16Model;
    }
    
    @Override
    public int getApplicationEnd() {
        return this.bootloader16Model.getEndAddress();
    }
    
    @Override
    public int getApplicationStart() {
        return this.bootloader16Model.getStartAddress();
    }
    
    @Override
    public Map<Integer, Integer> getFilteredImage() throws ChecksumException {
        return this.bootloader16Model.getFilteredImage();
    }
    
    @Override
    public void setResultStatus(final String status) {
        this.bootloader16Model.setStatusResult(status);
    }
    
    @Override
    public void setProgress(final double progress) {
        this.bootloader16Model.setProgress(progress);
    }
    
    @Override
    public Map<Integer, Integer> getImage() throws ChecksumException {
        return this.bootloader16Model.getImage();
    }
    
    @Override
    public int getPages(final int erasePageSize) {
        return (this.getApplicationEnd() - this.getApplicationStart()) / erasePageSize;
    }
    
    @Override
    public boolean isResetEnabled() {
        return this.bootloader16Model.isResetEnabled();
    }
    
    @Override
    public boolean isReadBackVerifyEnabled() {
        return this.bootloader16Model.isReadBackVerifyEnabled();
    }
    
    @Override
    public boolean isSelfVerifyEnabled() {
        return this.bootloader16Model.isSelfVerifyEnabled();
    }
    
    @Override
    public void setStartAddress(final int address) {
        this.bootloader16Model.setStartAddress(address);
    }
    
    @Override
    public void setEndAddress(final int address) {
        this.bootloader16Model.setEndAddress(address);
    }
    
    @Override
    public void setMemoryRange(final int startAddress, final int endAddress) {
        this.bootloader16Model.setMemoryRange(startAddress, endAddress);
    }
}
