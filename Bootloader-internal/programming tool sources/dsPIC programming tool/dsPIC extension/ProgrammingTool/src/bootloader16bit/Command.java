// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.nio.ByteBuffer;

interface Command
{
    Command setDummy(final Object p0, final int p1);
    
    void write(final ByteBuffer p0);
    
    int size();
    
    Command setEndAddress(final long p0);
    
    Command setStartAddress(final long p0);
    
    Command setMinWriteSize(final int p0);
    
    Command setErasePageSize(final int p0);
    
    Command setDeviceId(final int p0);
    
    Command setMaxPacketSize(final int p0);
    
    Command setStatus(final int p0);
    
    Command addWord(final int p0);
    
    Command setAddress(final long p0);
    
    Command setUnlock(final long p0);
    
    Command setLength(final int p0);
    
    Command setCommand(final int p0);
    
    Command setVersion(final int p0);
    
    Command setProgramStartAddress(final long p0);
    
    Command setProgramEndAddress(final long p0);
    
    Command setProgramRegionId(final int p0);
    
     <T> T accept(final FnCommandVisitor<T> p0);
}
