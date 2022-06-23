// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Map;

interface ModelProxy
{
    Map<Integer, Integer> getFilteredImage() throws ChecksumException;
    
    void setResultStatus(final String p0);
    
    void setProgress(final double p0);
    
    Map<Integer, Integer> getImage() throws ChecksumException;
    
    int getPages(final int p0);
    
    int getApplicationEnd();
    
    int getApplicationStart();
    
    boolean isResetEnabled();
    
    boolean isReadBackVerifyEnabled();
    
    boolean isSelfVerifyEnabled();
    
    void setStartAddress(final int p0);
    
    void setEndAddress(final int p0);
    
    void setMemoryRange(final int p0, final int p1);
}
