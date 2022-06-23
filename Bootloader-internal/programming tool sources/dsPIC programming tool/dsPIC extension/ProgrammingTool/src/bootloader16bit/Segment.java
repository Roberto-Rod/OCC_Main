// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.List;

public interface Segment
{
    int getLength();
    
    List<Integer> getAddresses();
    
    int getExclusiveEnd();
    
    int getInclusiveStart();
}
