// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropMaxPacketSize extends DefaultCommand
{
    private final Command others;
    private final int maxPacketSize;
    
    PropMaxPacketSize(final Command others, final int maxPacketSize) {
        this.others = others;
        this.maxPacketSize = maxPacketSize;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forMaxPacketSize(this.others, this.maxPacketSize);
    }
}
