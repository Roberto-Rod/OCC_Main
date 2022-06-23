// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Map;

public interface AdapterStats
{
    Map<Integer, Integer> getWriteCounts();
    
    Map<Integer, Integer> getReadCounts();
    
    Map<Integer, Integer> getMirrorImage();
}
