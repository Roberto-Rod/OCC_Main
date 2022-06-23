// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Collection;
import java.util.ArrayList;
import java.util.List;

public class VerificationCommandProducerForLinearRangeImpl implements VerificationCommandProducer
{
    private final List<Integer> addresses;
    private final int maxResponsePayloadSize;
    private final List<Command> commands;
    private int index;
    private Command command;
    private CommandFactory commandFactory;
    
    public VerificationCommandProducerForLinearRangeImpl(final List<Integer> addresses, final int maxResponsePayloadSize) {
        this.commandFactory = new CommandFactoryImpl();
        this.addresses = new ArrayList<Integer>(addresses);
        this.maxResponsePayloadSize = maxResponsePayloadSize;
        this.commands = new ArrayList<Command>();
    }
    
    @Override
    public List<Command> makeCommands() {
        int length = 0;
        this.index = 0;
        while (this.index < this.addresses.size()) {
            final Integer address = this.addresses.get(this.index);
            if (this.index == 0 && this.addresses.size() != 1) {
                this.startNewPacket();
                this.setAddress(address);
                length += 4;
            }
            else if (this.index == 0 && this.addresses.size() == 1) {
                this.startNewPacket();
                this.setAddress(address);
                length += 4;
                this.setLength(length);
                this.endPacket();
            }
            else if (this.index > 0 && length + 4 < this.maxResponsePayloadSize && this.index + 1 == this.addresses.size()) {
                length += 4;
                this.setLength(length);
                length = 0;
                this.endPacket();
            }
            else if (this.index > 0 && length + 4 < this.maxResponsePayloadSize && this.index + 1 != this.addresses.size()) {
                length += 4;
            }
            else if (this.index > 0 && length + 4 == this.maxResponsePayloadSize && this.index + 1 == this.addresses.size()) {
                length += 4;
                this.setLength(length);
                length = 0;
                this.endPacket();
            }
            else if (this.index > 0 && length + 4 == this.maxResponsePayloadSize && this.index + 1 != this.addresses.size()) {
                length += 4;
                this.setLength(length);
                length = 0;
                this.endPacket();
                this.startNewPacket();
                this.setAddress(this.addresses.get(this.index + 1));
            }
            else {
                if (this.index + 1 != this.addresses.size()) {
                    throw new IllegalStateException("An unexpected state was reached during verification.  This is a unified host bug!");
                }
                length += 4;
                this.setLength(length);
                this.endPacket();
            }
            ++this.index;
        }
        return this.commands;
    }
    
    private void setAddress(final Integer address) {
        this.command = this.command.setAddress(address);
    }
    
    private void setLength(final int length) {
        this.command = this.command.setLength(length);
    }
    
    private void endPacket() {
        this.commands.add(this.command);
        this.command = null;
    }
    
    private void startNewPacket() {
        this.command = new PropCommandBase().setCommand(this.commandFactory.getReadFlashCommandId()).setUnlock(this.commandFactory.getUnlockSequence());
    }
}
