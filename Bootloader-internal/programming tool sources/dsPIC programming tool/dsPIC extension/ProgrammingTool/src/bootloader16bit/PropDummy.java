// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.nio.ByteBuffer;

public class PropDummy extends DefaultCommand
{
    private final Command others;
    private final int size;
    
    public PropDummy(final Command others, final int size) {
        this.others = others;
        this.size = size;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forDummy(this.others, this.size);
    }
}
