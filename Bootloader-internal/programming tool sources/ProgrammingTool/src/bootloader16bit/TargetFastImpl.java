// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.function.Supplier;
import java.util.Iterator;
import java.util.List;
import java.util.HashMap;
import java.util.Map;
import java.io.IOException;
import java.nio.ByteOrder;
import java.nio.channels.ByteChannel;
import java.nio.ByteBuffer;

class TargetFastImpl implements Target
{
    private CommandFactory commandFactory;
    private CommandStatusFactory commandStatusFactory;
    private static final double NANOSECOND_DIVISOR = 1.0E9;
    private static final double TIMEOUT = 5.0;
    private static final double TIMEOUT_90_SECONDS = 90.0;
    private static final double TIMEOUT_5_SECONDS = 5.0;
    private final ByteBuffer request;
    private final ByteBuffer response;
    static final int UNLOCK = 11141205;
    private final ByteChannel channel;
    
    TargetFastImpl(final ByteChannel channel) {
        this.commandFactory = new CommandFactoryImpl();
        this.commandStatusFactory = new CommandStatusFactoryImpl();
        this.request = ByteBuffer.allocate(1024);
        this.response = ByteBuffer.allocate(1024);
        this.channel = channel;
        this.request.order(ByteOrder.LITTLE_ENDIAN);
        this.response.order(ByteOrder.LITTLE_ENDIAN);
        this.commandFactory = new CommandFactoryImpl();
    }
    
    @Override
    public Command getVersion() throws IOException, TimeoutException {
        this.write(this.commandFactory.makeGetVersionCommand());
        return this.readResponse(this::getVersionCommandResponse, 5.0);
    }
    
    @Override
    public Command erasePages(final int address, final int pages) throws IOException, TimeoutException, BadResponseException {
        return this.transceive(new PropCommandBase().setCommand(this.commandFactory.getEraseFlashCommandId()).setLength(pages).setUnlock(11141205L).setAddress(address), this::getCommonCommandResponse, 5.0);
    }
    
    @Override
    public void flushInput() throws IOException {
        this.response.clear();
        while (this.channel.read(this.response) > 0) {
            this.response.clear();
        }
    }
    
    @Override
    public Map<Integer, Integer> read(final Command command) throws IOException, BadResponseException, TimeoutException {
        this.write(command);
        final Map<Integer, Integer> map = new HashMap<Integer, Integer>();
        final Integer payloadLength = command.accept((FnCommandVisitor<Integer>)new FnDataLengthAccessor());
        final Integer commonCommandResponseSize = this.getSize(this::getCommonCommandResponse);
        final Integer size = payloadLength + commonCommandResponseSize;
        final long t0 = System.nanoTime();
        this.response.clear();
        int read = 0;
        while (read < size) {
            read += this.channel.read(this.response);
            final long t2 = System.nanoTime();
            final double delta = (t2 - t0) / 1.0E9;
            if (delta > 5.0) {
                if (read == commonCommandResponseSize) {
                    this.response.flip();
                    throw new BadResponseException(command, this.getCommonCommandResponse());
                }
                this.response.flip();
                final byte[] dst = new byte[this.response.capacity()];
                this.response.get(dst);
                throw new TimeoutException(dst);
            }
        }
        this.response.flip();
        final Command resp = this.getCommonCommandResponse();
        final Integer status = resp.accept((FnCommandVisitor<Integer>)new FnStatusAccessor());
        if (status != 1) {
            throw new BadResponseException(command, resp);
        }
        Long responseAddress = resp.accept((FnCommandVisitor<Long>)new FnAddressAccessor());
        while (this.response.hasRemaining()) {
            final int anInt = this.response.getInt();
            map.put(Math.toIntExact(responseAddress), anInt);
            responseAddress += 2L;
        }
        return map;
    }
    
    @Override
    public void write(final List<Command> commands, final Runnable post) throws IOException, TimeoutException, BadResponseException {
        for (final Command command : commands) {
            this.transceive(command, this::getCommonCommandResponse, 5.0);
            post.run();
        }
    }
    
    @Override
    public Command reset() throws IOException, TimeoutException, BadResponseException {
        return this.transceive(new PropCommandBase().setCommand(this.commandFactory.getResetDeviceCommandId()), this::getCommonCommandResponse, 5.0);
    }
    
    private void write(final Command command) throws IOException {
        this.request.clear();
        command.write(this.request);
        this.request.flip();
        for (int size = command.size(), write = 0; write < size; write += this.channel.write(this.request)) {}
    }
    
    private Command readResponse(final Supplier<Command> commandSupplier, final double timeOut) throws IOException, TimeoutException {
        final Integer size = this.getSize(commandSupplier);
        final long t0 = System.nanoTime();
        this.response.clear();
        int read = 0;
        while (read < size) {
            read += this.channel.read(this.response);
            final long t2 = System.nanoTime();
            final double delta = (t2 - t0) / 1.0E9;
            if (delta > timeOut) {
                this.response.flip();
                final byte[] dst = new byte[this.response.capacity()];
                this.response.get(dst);
                throw new TimeoutException(dst);
            }
        }
        this.response.flip();
        return commandSupplier.get();
    }
    
    private Integer getSize(final Supplier<Command> supplier) {
        this.response.clear();
        this.response.position(this.response.limit());
        this.response.flip();
        final Command command = supplier.get();
        final Integer accept = command.accept((FnCommandVisitor<Integer>)new FnPrototypeSizeVisitorImpl());
        this.response.clear();
        return accept;
    }
    
    private Command getVersionCommandResponse() {
        return new PropCommandBase().setCommand(this.getUnsignedByte()).setLength(this.getUnsignedShort()).setUnlock(this.getUnsignedInt()).setAddress(this.getUnsignedInt()).setVersion(this.getUnsignedShort()).setMaxPacketSize(this.getUnsignedShort()).setDummy(this.getUnsignedShort(), 2).setDeviceId(this.getUnsignedShort()).setDummy(this.getUnsignedShort(), 2).setErasePageSize(this.getUnsignedShort()).setMinWriteSize(this.getUnsignedShort()).setDummy(this.getUnsignedInt(), 4).setStartAddress(this.getUnsignedInt()).setEndAddress(this.getUnsignedInt());
    }
    
    private Command getMemoryAddressRangeResponse() {
        return new PropCommandBase().setCommand(this.getUnsignedByte()).setLength(this.getUnsignedShort()).setUnlock(this.getUnsignedInt()).setAddress(this.getUnsignedInt()).setStatus(this.getUnsignedByte()).setProgramStartAddress(this.getUnsignedInt()).setProgramEndAddress(this.getUnsignedInt());
    }
    
    private Command getCommonCommandResponse() {
        return new PropCommandBase().setCommand(this.getUnsignedByte()).setLength(this.getUnsignedShort()).setUnlock(this.getUnsignedInt()).setAddress(this.getUnsignedInt()).setStatus(this.getUnsignedByte());
    }
    
    private int getUnsignedInt() {
        return (int)((long)this.response.getInt() & 0xFFFFFFFFL);
    }
    
    private short getUnsignedShort() {
        return (short)(this.response.getShort() & 0xFFFF);
    }
    
    private byte getUnsignedByte() {
        return (byte)(this.response.get() & 0xFF);
    }
    
    private Command transceive(final Command command, final Supplier<Command> supplier, final double timeOut) throws IOException, TimeoutException, BadResponseException {
        this.write(command);
        final Command response = this.readResponse(supplier, timeOut);
        final Integer status = response.accept((FnCommandVisitor<Integer>)new FnStatusAccessor());
        if (status != this.commandStatusFactory.getCommandSuccessId()) {
            throw new BadResponseException(command, response);
        }
        return response;
    }
    
    @Override
    public Integer selfVerify() throws IOException, TimeoutException, BadResponseException {
        Command response;
        try {
            response = this.transceive(new PropCommandBase().setCommand(this.commandFactory.getSelfVerifyCommandId()), this::getCommonCommandResponse, 90.0);
        }
        catch (BadResponseException e) {
            response = e.getResponse();
        }
        return response.accept((FnCommandVisitor<Integer>)new FnStatusAccessor());
    }
    
    private Command getMemoryRangeResponse(final Command command, final Supplier<Command> commandSupplier) throws IOException, TimeoutException, BadResponseException {
        final Integer payloadLength = command.accept((FnCommandVisitor<Integer>)new FnDataLengthAccessor());
        final Integer commonCommandResponseSize = this.getSize(this::getCommonCommandResponse);
        final Integer size = payloadLength + commonCommandResponseSize;
        final long t0 = System.nanoTime();
        this.response.clear();
        int read = 0;
        while (read < size) {
            read += this.channel.read(this.response);
            if (read == commonCommandResponseSize && this.response.get(commonCommandResponseSize - 1) != 1) {
                this.response.flip();
                throw new BadResponseException(command, this.getCommonCommandResponse());
            }
            final long t2 = System.nanoTime();
            final double delta = (t2 - t0) / 1.0E9;
            if (delta > 5.0) {
                this.response.flip();
                final byte[] dst = new byte[this.response.capacity()];
                this.response.get(dst);
                throw new TimeoutException(dst);
            }
        }
        this.response.flip();
        return commandSupplier.get();
    }
    
    @Override
    public Command getDeviceData() throws IOException, TimeoutException, BadResponseException {
        final Command command = new PropCommandBase().setCommand(this.commandFactory.getMemoryAddressRangeCommandId()).setLength(8).setUnlock(0L).setAddress(0L);
        final Supplier<Command> supplier = this::getMemoryAddressRangeResponse;
        this.write(command);
        final Command response = this.getMemoryRangeResponse(command, supplier);
        return response;
    }
}
