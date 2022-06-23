// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropCommand extends DefaultCommand
{
    private final Command others;
    private final int cmd;
    
    PropCommand(final Command others, final int cmd) {
        this.others = others;
        this.cmd = cmd;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forCommand(this.others, this.cmd);
    }
}
