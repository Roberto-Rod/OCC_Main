// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropEndAddress extends DefaultCommand
{
    private final Command others;
    private final long endAddress;
    
    PropEndAddress(final Command others, final long endAddress) {
        this.others = others;
        this.endAddress = endAddress;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forEndAddress(this.others, this.endAddress);
    }
}
