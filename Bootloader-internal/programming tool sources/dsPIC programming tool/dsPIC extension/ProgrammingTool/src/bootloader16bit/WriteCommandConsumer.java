// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.List;

interface WriteCommandConsumer
{
    List<Command> getCommands();
    
    void endPacket();
    
    void addToPacket(final Integer p0);
    
    void startNewPacket(final Integer p0, final Integer p1);
    
    Integer getHeaderSize();
}
