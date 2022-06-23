// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropProgramEndAddress extends DefaultCommand
{
    private final Command others;
    private final long programEndAddres;
    
    PropProgramEndAddress(final Command others, final long programEndAddres) {
        this.others = others;
        this.programEndAddres = programEndAddres;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forProgramEndAddress(this.others, this.programEndAddres);
    }
}
