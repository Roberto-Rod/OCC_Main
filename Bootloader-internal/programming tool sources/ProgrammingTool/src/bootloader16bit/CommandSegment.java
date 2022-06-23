// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public interface CommandSegment extends Comparable<CommandSegment>
{
    Command attach(final Command p0);
    
    Integer getSequence();
    
    int compareTo(final CommandSegment p0);
}
