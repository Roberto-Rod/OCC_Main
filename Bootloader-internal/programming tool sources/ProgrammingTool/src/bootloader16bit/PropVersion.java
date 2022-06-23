// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropVersion extends DefaultCommand
{
    private final Command others;
    private final int version;
    
    PropVersion(final Command others, final int version) {
        this.others = others;
        this.version = version;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forVersion(this.others, this.version);
    }
}
