// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public class FnMinWriteSizeAccessor extends FnDefaultCommandVisitor<Integer>
{
    @Override
    public Integer forMinWriteSize(final Command others, final int minWriteSize) {
        return minWriteSize;
    }
}
