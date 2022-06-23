// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropUnlockCodeSegment implements CommandSegment
{
    private final int unlockCode;
    
    PropUnlockCodeSegment(final int unlockCode) {
        this.unlockCode = unlockCode;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropUnlockCode(others, this.unlockCode);
    }
    
    @Override
    public Integer getSequence() {
        return 2;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
