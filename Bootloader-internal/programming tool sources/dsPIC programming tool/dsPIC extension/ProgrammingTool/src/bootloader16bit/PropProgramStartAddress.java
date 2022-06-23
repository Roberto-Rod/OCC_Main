// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropProgramStartAddress extends DefaultCommand
{
    private final Command others;
    private final long programStartAddress;
    
    PropProgramStartAddress(final Command others, final long programStartAddres) {
        this.others = others;
        this.programStartAddress = programStartAddres;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forProgramStartAddress(this.others, this.programStartAddress);
    }
}
