// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.List;
import java.util.stream.Collector;
import java.util.function.Supplier;
import java.io.OutputStream;
import java.io.InputStream;
import java.nio.channels.ByteChannel;
import java.util.Map;
import java.util.HashMap;
import console16bit.Console16bitImpl;
import console16bit.Console16bit;

public class Bootloader16AbstractFactoryFastImpl implements Bootloader16AbstractFactory
{
    @Override
    public Console16bit makeConsole() {
        return new Console16bitImpl();
    }
    
    @Override
    public SerialAdapter makeSerialAdapter(final Console16bit console) {
        return new SerialAdapterImpl(this, console);
    }
    
    @Override
    public SerialAdapter makeMockAdapter(final Console16bit console) {
        final Map<String, MockTarget> mocks = new HashMap<String, MockTarget>();
        mocks.put("4B-MIN-WORD", new MockTargetImpl(4));
        mocks.put("8B-MIN-WORD", new MockTargetImpl(8));
        return new MockAdapterImpl(console, mocks);
    }
    
    private HexParser getHexParser() {
        return new HexParserImpl();
    }
    
    @Override
    public Bootloader16Model makeBootloader16Model() {
        final Console16bit console = this.makeConsole();
        final HexParser hexParser = this.getHexParser();
        return new Bootloader16Model(this, hexParser, console);
    }
    
    @Override
    public Target makeTarget(final ByteChannel channel) {
        return new TargetFastImpl(channel);
    }
    
    @Override
    public ByteChannel makeByteChannel(final InputStream inputStream, final OutputStream outputStream) {
        return new ByteChannelFastImpl(inputStream, outputStream);
    }
    
    @Override
    public EventHandler makeEventHandler(final ModelProxy modelProxy, final Console16bit console) {
        return new EventHandlerImpl(modelProxy, console);
    }
    
    @Override
    public Runnable makeProgrammer(final ModelProxy modelProxy, final EventHandler eventHandler, final Target target) {
        return new ProgramTargetFastImpl(this, modelProxy, target, eventHandler);
    }
    
    @Override
    public Runnable makeDeviceReader(final ModelProxy modelProxy, final EventHandler eventHandler, final Target target) {
        return new ReadDeviceDataFastImpl(this, modelProxy, target, eventHandler);
    }
    
    @Override
    public VerificationCommandProducer makeVerificationCommandProducer(final Segment segment, final int maxResponsePayloadSize) {
        return new VerificationCommandProducerForLinearRangeImpl(segment.getAddresses(), maxResponsePayloadSize);
    }
    
    @Override
    public WriteCommandProducer makeWriteCommandProducer(final Map<Integer, Integer> image, final int maxPayloadSize, final int minWriteSize) {
        if (minWriteSize == 4) {
            return new WriteCommandProducerImpl(image, this.makeWriteCommandConsumer(), maxPayloadSize);
        }
        if (minWriteSize == 8) {
            final int chunksInAChonk = maxPayloadSize / 8;
            return new WriteCommandProducer8BImpl(image, this.makeCondenserSupplier(chunksInAChonk));
        }
        throw new UnsupportedOperationException();
    }
    
    @Override
    public WriteCommandConsumer makeWriteCommandConsumer() {
        return new WriteCommandConsumerImpl();
    }
    
    private Supplier<Collector<Chunk, ChunkBuilder, List<Chonk>>> makeCondenserSupplier(final int chunksInAChonk) {
        return (Supplier<Collector<Chunk, ChunkBuilder, List<Chonk>>>)(() -> new ChunksToChonksCollectorImpl(chunksInAChonk));
    }
    
    @Override
    public SegmentedImage makeSegmentedImage(final Map<Integer, Integer> image) {
        return new SegmentedImageImpl(image, this.makeSegmentFactory());
    }
    
    @Override
    public SegmentFactory makeSegmentFactory() {
        return new SegmentFactoryImpl();
    }
    
    @Override
    public SerialAdapterFactory makeSerialAdapterFactory(final Console16bit console) {
        return new SerialAdapterFactoryImpl(this, console);
    }
    
    @Override
    public SerialAdapterBuilder makeAdapterBuilder(final Console16bit console) {
        return new SerialAdapterBuilderImpl(this.makeSerialAdapterFactory(console));
    }
}
