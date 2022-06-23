// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropErasePageSize extends DefaultCommand
{
    private final Command others;
    private final int erasePageSize;
    
    PropErasePageSize(final Command others, final int erasePageSize) {
        this.others = others;
        this.erasePageSize = erasePageSize;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forErasePageSize(this.others, this.erasePageSize);
    }
}
