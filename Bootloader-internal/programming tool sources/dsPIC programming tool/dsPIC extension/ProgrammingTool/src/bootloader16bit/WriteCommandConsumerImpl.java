// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.ArrayList;
import java.util.List;

public class WriteCommandConsumerImpl implements WriteCommandConsumer
{
    private final List<Command> commands;
    private Command command;
    private int length;
    private CommandFactory commandFactory;
    
    public WriteCommandConsumerImpl() {
        this.length = 0;
        this.commandFactory = new CommandFactoryImpl();
        this.commands = new ArrayList<Command>();
    }
    
    @Override
    public List<Command> getCommands() {
        return this.commands;
    }
    
    @Override
    public void endPacket() {
        this.command = this.command.setLength(this.length);
        this.commands.add(this.command);
    }
    
    @Override
    public void addToPacket(final Integer value) {
        this.command = this.command.addWord(value);
        this.length += 4;
    }
    
    @Override
    public void startNewPacket(final Integer address, final Integer value) {
        this.command = this.getHeader(address).addWord(value);
        this.length = 4;
    }
    
    private Command getHeader(final Integer address) {
        return new PropCommandBase().setCommand(this.commandFactory.getWriteFlashCommandId()).setAddress(address).setLength(0).setUnlock(this.commandFactory.getUnlockSequence());
    }
    
    @Override
    public Integer getHeaderSize() {
        return this.getHeader(0).accept((FnCommandVisitor<Integer>)new FnPrototypeSizeVisitorImpl());
    }
}
