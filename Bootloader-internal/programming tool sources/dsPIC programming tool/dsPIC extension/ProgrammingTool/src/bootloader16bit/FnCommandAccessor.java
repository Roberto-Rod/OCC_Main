// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnCommandAccessor extends FnDefaultCommandVisitor<Byte>
{
    @Override
    public Byte forCommand(final Command others, final int cmd) {
        return (byte)cmd;
    }
}
