// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public class CommandStatusFactoryImpl implements CommandStatusFactory
{
    private final byte COMMAND_SUCCESS = 1;
    private final byte COMMAND_UNSUPPORTED = -1;
    private final byte ADDRESS_ERROR = -2;
    private final byte BAD_LENGTH = -3;
    private final byte VERIFY_FAIL = -4;
    
    @Override
    public byte getCommandSuccessId() {
        return 1;
    }
    
    @Override
    public byte getCommandUnsupportedId() {
        return -1;
    }
    
    @Override
    public byte getAddressErrorId() {
        return -2;
    }
    
    @Override
    public byte getBadLengthId() {
        return -3;
    }
    
    @Override
    public byte getVerifyFailId() {
        return -4;
    }
}
