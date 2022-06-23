// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.io.IOException;
import java.nio.ByteBuffer;

interface MockTarget
{
    AdapterStats getAdapterStats();
    
    void writeFlash(final int p0, final int p1);
    
    int read(final ByteBuffer p0) throws IOException;
    
    int write(final ByteBuffer p0) throws IOException;
    
    boolean isOpen();
    
    void close() throws IOException;
    
    int readFlash(final int p0);
}
