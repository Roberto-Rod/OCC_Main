// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public class FnWriteDataByteCounter<T> extends FnDefaultCommandVisitor<Integer>
{
    @Override
    public Integer forData(final Command others, final int data) {
        return 4 + others.accept(this);
    }
    
    @Override
    public Integer forBase() {
        return 0;
    }
}
