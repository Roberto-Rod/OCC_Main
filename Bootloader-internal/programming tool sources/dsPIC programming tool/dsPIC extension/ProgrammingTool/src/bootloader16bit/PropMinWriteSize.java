// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropMinWriteSize extends DefaultCommand
{
    private final Command others;
    private final int minWriteSize;
    
    PropMinWriteSize(final Command others, final int minWriteSize) {
        this.others = others;
        this.minWriteSize = minWriteSize;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forMinWriteSize(this.others, this.minWriteSize);
    }
}
