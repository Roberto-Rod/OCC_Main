// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropProgramWord extends DefaultCommand
{
    private final Command others;
    private final int data;
    
    PropProgramWord(final Command others, final int data) {
        this.others = others;
        this.data = data;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forData(this.others, this.data);
    }
}
