// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropAddress extends DefaultCommand
{
    private final Command others;
    private final long address;
    
    PropAddress(final Command others, final long address) {
        this.others = others;
        this.address = address;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forAddress(this.others, this.address);
    }
}
