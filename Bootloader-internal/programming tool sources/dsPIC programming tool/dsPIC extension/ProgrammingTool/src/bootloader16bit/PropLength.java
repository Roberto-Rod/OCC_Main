// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropLength extends DefaultCommand
{
    private final Command others;
    private final int length;
    
    PropLength(final Command others, final int length) {
        this.others = others;
        this.length = length;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forLength(this.others, this.length);
    }
}
