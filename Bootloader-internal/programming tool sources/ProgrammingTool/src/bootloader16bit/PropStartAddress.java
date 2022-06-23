// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropStartAddress extends DefaultCommand
{
    private final Command others;
    private final long startAddress;
    
    PropStartAddress(final Command others, final long startAddress) {
        this.others = others;
        this.startAddress = startAddress;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forStartAddress(this.others, this.startAddress);
    }
}
