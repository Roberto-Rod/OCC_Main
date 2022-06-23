// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Collections;
import java.util.Map;

class NullAdapterStatsImpl implements AdapterStats
{
    @Override
    public Map<Integer, Integer> getWriteCounts() {
        return Collections.emptyMap();
    }
    
    @Override
    public Map<Integer, Integer> getReadCounts() {
        return Collections.emptyMap();
    }
    
    @Override
    public Map<Integer, Integer> getMirrorImage() {
        return Collections.emptyMap();
    }
}
