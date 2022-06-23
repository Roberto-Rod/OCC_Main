// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.io.OutputStream;
import java.nio.channels.WritableByteChannel;
import java.io.InputStream;
import java.nio.channels.ReadableByteChannel;
import java.nio.channels.ByteChannel;

class ByteChannelFastImpl implements ByteChannel
{
    private final ReadableByteChannel readableByteChannel;
    private InputStream inputStream;
    private final WritableByteChannel writableByteChannel;
    
    public ByteChannelFastImpl(final InputStream inputStream, final OutputStream outputStream) {
        this.readableByteChannel = Channels.newChannel(inputStream);
        this.writableByteChannel = Channels.newChannel(outputStream);
        this.inputStream = inputStream;
    }
    
    @Override
    public int read(final ByteBuffer dst) throws IOException {
        if (this.inputStream.available() > 0) {
            return this.readableByteChannel.read(dst);
        }
        return 0;
    }
    
    @Override
    public int write(final ByteBuffer src) throws IOException {
        return this.writableByteChannel.write(src);
    }
    
    @Override
    public boolean isOpen() {
        return this.readableByteChannel.isOpen() && this.writableByteChannel.isOpen();
    }
    
    @Override
    public void close() throws IOException {
        this.readableByteChannel.close();
        this.writableByteChannel.close();
    }
}
