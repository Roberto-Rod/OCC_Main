// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropStatus extends DefaultCommand
{
    private final Command others;
    private final int status;
    
    PropStatus(final Command others, final int status) {
        this.others = others;
        this.status = status;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forStatus(this.others, this.status);
    }
}
