// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnProgramStartAddressAccessor extends FnDefaultCommandVisitor<Integer>
{
    @Override
    public Integer forProgramStartAddress(final Command others, final long address) {
        return (int)address;
    }
    
    @Override
    public Integer forBase() {
        return 0;
    }
}
