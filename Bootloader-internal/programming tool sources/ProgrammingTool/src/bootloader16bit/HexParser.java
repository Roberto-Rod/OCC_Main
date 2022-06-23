// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.file.OpenOption;
import java.util.Map;
import java.nio.file.Path;

abstract class HexParser
{
    Map<Integer, Integer> parse(final Path file) throws IOException, ChecksumException {
        this.reset();
        try (final FileChannel fc = FileChannel.open(file, new OpenOption[0])) {
            final ByteBuffer bb = ByteBuffer.allocate(64);
            while (fc.read(bb) > 0) {
                bb.flip();
                while (bb.hasRemaining()) {
                    final byte b = bb.get();
                    if (b == 58) {
                        this.start();
                    }
                    else {
                        this.other(b);
                    }
                }
                bb.clear();
            }
        }
        return this.getMemory();
    }
    
    protected abstract Map<Integer, Integer> getMemory();
    
    protected abstract void start();
    
    protected abstract void reset();
    
    protected abstract void other(final byte p0) throws ChecksumException;
}
