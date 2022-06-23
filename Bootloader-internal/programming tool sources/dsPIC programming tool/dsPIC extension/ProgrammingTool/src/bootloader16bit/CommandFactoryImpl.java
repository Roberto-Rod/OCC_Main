// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public class CommandFactoryImpl implements CommandFactory
{
    private final byte GET_VERSION_COMMAND = 0;
    private final byte READ_FLASH_COMMAND = 1;
    private final byte ERASE_FLASH_COMMAND = 3;
    private final byte RESET_DEVICE_COMMAND = 9;
    private final byte WRITE_FLASH_COMMAND = 2;
    private final byte SELF_VERIFY_COMMAND = 10;
    private final byte GET_MEMORY_ADDRESS_RANGE_COMMAND = 11;
    private final int UNLOCK = 11141205;
    
    @Override
    public Command makeBase() {
        return new PropCommandBase();
    }
    
    @Override
    public long getUnlockSequence() {
        return 11141205L;
    }
    
    @Override
    public Command makeGetVersionCommand() {
        return this.makeBase().setCommand(this.getVersionCommandId());
    }
    
    @Override
    public int getVersionCommandId() {
        return 0;
    }
    
    @Override
    public byte getReadFlashCommandId() {
        return 1;
    }
    
    @Override
    public byte getEraseFlashCommandId() {
        return 3;
    }
    
    @Override
    public byte getResetDeviceCommandId() {
        return 9;
    }
    
    @Override
    public byte getWriteFlashCommandId() {
        return 2;
    }
    
    @Override
    public byte getSelfVerifyCommandId() {
        return 10;
    }
    
    @Override
    public byte getMemoryAddressRangeCommandId() {
        return 11;
    }
}
