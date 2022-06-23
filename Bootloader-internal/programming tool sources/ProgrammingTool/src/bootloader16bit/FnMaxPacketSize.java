// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public class FnMaxPacketSize extends FnDefaultCommandVisitor<Integer>
{
    @Override
    public Integer forMaxPacketSize(final Command others, final int maxPacketSize) {
        return maxPacketSize;
    }
}
