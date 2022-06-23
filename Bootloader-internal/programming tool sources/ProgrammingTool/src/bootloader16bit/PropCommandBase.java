// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropCommandBase extends DefaultCommand
{
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forBase();
    }
}
