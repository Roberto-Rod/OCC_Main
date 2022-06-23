// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.ByteChannel;

class MockTargetWrapperImpl implements ByteChannel
{
    private final MockTarget target;
    
    public MockTargetWrapperImpl(final MockTarget target) {
        this.target = target;
    }
    
    @Override
    public int read(final ByteBuffer dst) throws IOException {
        return this.target.read(dst);
    }
    
    @Override
    public int write(final ByteBuffer src) throws IOException {
        return this.target.write(src);
    }
    
    @Override
    public boolean isOpen() {
        return this.target.isOpen();
    }
    
    @Override
    public void close() throws IOException {
        this.target.close();
    }
}
