// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropProgramWordSegment implements CommandSegment
{
    private final int word;
    private Integer seq;
    
    PropProgramWordSegment(final int word, final Integer seq) {
        this.word = word;
        this.seq = seq;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropProgramWord(others, this.word);
    }
    
    @Override
    public Integer getSequence() {
        return this.seq;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
