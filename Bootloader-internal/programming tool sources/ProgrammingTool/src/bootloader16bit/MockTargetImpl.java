// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.function.Consumer;
import java.io.IOException;
import java.util.HashMap;
import java.nio.ByteOrder;
import java.util.Map;
import java.nio.ByteBuffer;

public class MockTargetImpl implements MockTarget
{
    private final CommandFactory commandFactory;
    private final CommandStatusFactory commandStatusFactory;
    private final ByteBuffer response;
    private final ByteBuffer flashBuffer;
    private final Map<Integer, Integer> flash;
    private final Map<Integer, Integer> flashWriteCount;
    private final Map<Integer, Integer> flashReadCount;
    private final byte minByteCount;
    
    public MockTargetImpl(final Integer minByteCount) {
        this.response = ByteBuffer.allocate(1024);
        this.flashBuffer = ByteBuffer.allocate(1024);
        this.commandFactory = new CommandFactoryImpl();
        this.commandStatusFactory = new CommandStatusFactoryImpl();
        this.response.order(ByteOrder.LITTLE_ENDIAN);
        this.flashBuffer.order(ByteOrder.LITTLE_ENDIAN);
        this.flash = new HashMap<Integer, Integer>();
        this.flashWriteCount = new HashMap<Integer, Integer>();
        this.flashReadCount = new HashMap<Integer, Integer>();
        this.minByteCount = minByteCount.byteValue();
    }
    
    @Override
    public AdapterStats getAdapterStats() {
        return new AdapterStats() {
            @Override
            public Map<Integer, Integer> getWriteCounts() {
                return MockTargetImpl.this.flashWriteCount;
            }
            
            @Override
            public Map<Integer, Integer> getReadCounts() {
                return MockTargetImpl.this.flashReadCount;
            }
            
            @Override
            public Map<Integer, Integer> getMirrorImage() {
                return MockTargetImpl.this.flash;
            }
        };
    }
    
    @Override
    public void writeFlash(final int address, final int data) {
        this.flash.put(address, data);
    }
    
    @Override
    public int read(final ByteBuffer dst) throws IOException {
        this.response.flip();
        final int remaining = this.response.remaining();
        while (this.response.hasRemaining()) {
            dst.put(this.response.get());
        }
        this.response.clear();
        return remaining;
    }
    
    @Override
    public int write(final ByteBuffer src) throws IOException {
        final int remaining = src.remaining();
        src.mark();
        final byte b = src.get();
        src.reset();
        if (b == this.commandFactory.getVersionCommandId()) {
            this.handleGetVersion();
        }
        else if (b == this.commandFactory.getWriteFlashCommandId()) {
            this.handleWriteFlash(src);
        }
        else if (b == this.commandFactory.getReadFlashCommandId()) {
            this.handleReadFlash(src);
        }
        else if (b == this.commandFactory.getEraseFlashCommandId()) {
            this.handleErase(src);
        }
        else if (b == this.commandFactory.getResetDeviceCommandId()) {
            this.handleReset(src);
        }
        else if (b == this.commandFactory.getSelfVerifyCommandId()) {
            this.handleSelfVerify(src);
        }
        else {
            this.handleUnsupportedCommand(src);
        }
        return remaining;
    }
    
    private void successfulCommand(final ByteBuffer src) {
        this.response.clear();
        while (src.hasRemaining()) {
            this.response.put(src.get());
        }
        this.response.put(this.commandStatusFactory.getCommandSuccessId());
    }
    
    private void handleReset(final ByteBuffer src) {
        this.flash.clear();
        this.successfulCommand(src);
    }
    
    private void handleSelfVerify(final ByteBuffer src) {
        this.successfulCommand(src);
    }
    
    private void handleUnsupportedCommand(final ByteBuffer src) {
        this.response.clear();
        while (src.hasRemaining()) {
            this.response.put(src.get());
        }
        this.response.put(this.commandStatusFactory.getCommandUnsupportedId());
    }
    
    private void handleErase(final ByteBuffer src) {
        this.flash.clear();
        this.successfulCommand(src);
    }
    
    private void handleReadFlash(final ByteBuffer src) {
        this.successfulCommand(src);
        src.reset();
        final Command request = this.getReadCommandRequest(src);
        Integer address = request.accept((FnCommandVisitor<Long>)new FnAddressAccessor()).intValue();
        for (Integer length = request.accept((FnCommandVisitor<Integer>)new FnDataLengthAccessor()); length > 0; length -= 4) {
            this.response.putInt(this.readFlash(address));
            address += 2;
        }
    }
    
    private void handleWriteFlash(final ByteBuffer src) {
        src.reset();
        final Command writeRequest = this.getWriteRequest(src);
        src.reset();
        this.fillResponse(src);
        this.fillFlashBuffer(writeRequest);
    }
    
    private Command getWriteRequest(final ByteBuffer src) {
        Command writeRequest = this.getCommonCommandRequest(src);
        while (src.hasRemaining()) {
            final int anInt = src.getInt();
            writeRequest = writeRequest.addWord(anInt);
        }
        return writeRequest;
    }
    
    private void fillResponse(final ByteBuffer src) {
        final int payloadSize = src.remaining() - 11;
        this.response.clear();
        for (int i = 0; i < 11; ++i) {
            this.response.put(src.get());
        }
        if (payloadSize % this.minByteCount == 0) {
            this.response.put(this.commandStatusFactory.getCommandSuccessId());
        }
        else {
            this.response.put(this.commandStatusFactory.getAddressErrorId());
        }
    }
    
    private void fillFlashBuffer(final Command writeRequest) {
        Integer address = writeRequest.accept((FnCommandVisitor<Long>)new FnAddressAccessor()).intValue();
        this.flashBuffer.clear();
        writeRequest.accept((FnCommandVisitor<Consumer<ByteBuffer>>)new FnDataAccessor()).accept(this.flashBuffer);
        this.flashBuffer.flip();
        while (this.flashBuffer.hasRemaining()) {
            this.flash.put(address, this.flashBuffer.getInt());
            final Integer c = this.flashWriteCount.getOrDefault(address, 0) + 1;
            this.flashWriteCount.put(address, c);
            address += 2;
        }
    }
    
    private void handleGetVersion() {
        this.response.clear();
        this.response.put((byte)this.commandFactory.getVersionCommandId());
        this.response.putShort((short)0);
        this.response.putInt(0);
        this.response.putInt(0);
        this.response.putShort((short)6);
        this.response.putShort((short)256);
        this.response.putShort((short)0);
        this.response.putShort((short)(-24228));
        this.response.putShort((short)0);
        this.response.putShort((short)4096);
        this.response.putShort(this.minByteCount);
        this.response.putInt(0);
        this.response.putInt(0);
        this.response.putInt(0);
    }
    
    @Override
    public boolean isOpen() {
        return false;
    }
    
    @Override
    public void close() throws IOException {
    }
    
    @Override
    public int readFlash(final int address) {
        final Integer count = this.flashReadCount.getOrDefault(address, 0);
        this.flashReadCount.put(address, count + 1);
        return this.flash.getOrDefault(address, 0);
    }
    
    private Command getReadCommandRequest(final ByteBuffer bb) {
        return new PropCommandBase().setCommand(this.getUnsignedByte(bb)).setLength(this.getUnsignedShort(bb)).setUnlock(this.getUnsignedInt(bb)).setAddress(this.getUnsignedInt(bb));
    }
    
    private Command getCommonCommandRequest(final ByteBuffer bb) {
        return new PropCommandBase().setCommand(this.getUnsignedByte(bb)).setLength(this.getUnsignedShort(bb)).setUnlock(this.getUnsignedInt(bb)).setAddress(this.getUnsignedInt(bb));
    }
    
    private int getUnsignedInt(final ByteBuffer bb) {
        return (int)((long)bb.getInt() & 0xFFFFFFFFL);
    }
    
    private short getUnsignedShort(final ByteBuffer bb) {
        return (short)(bb.getShort() & 0xFFFF);
    }
    
    private byte getUnsignedByte(final ByteBuffer bb) {
        return (byte)(bb.get() & 0xFF);
    }
}
