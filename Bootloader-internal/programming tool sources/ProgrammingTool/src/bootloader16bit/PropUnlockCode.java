// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropUnlockCode extends DefaultCommand
{
    private final Command others;
    private final long unlock;
    
    PropUnlockCode(final Command others, final long unlock) {
        this.others = others;
        this.unlock = unlock;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forUnlock(this.others, this.unlock);
    }
}
