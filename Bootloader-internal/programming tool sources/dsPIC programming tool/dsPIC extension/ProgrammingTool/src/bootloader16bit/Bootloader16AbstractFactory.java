// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.nio.channels.ByteChannel;
import java.io.OutputStream;
import java.io.InputStream;
import console16bit.Console16bit;
import java.util.Map;

public interface Bootloader16AbstractFactory
{
    SegmentedImage makeSegmentedImage(final Map<Integer, Integer> p0);
    
    WriteCommandProducer makeWriteCommandProducer(final Map<Integer, Integer> p0, final int p1, final int p2);
    
    VerificationCommandProducer makeVerificationCommandProducer(final Segment p0, final int p1);
    
    Runnable makeProgrammer(final ModelProxy p0, final EventHandler p1, final Target p2);
    
    Runnable makeDeviceReader(final ModelProxy p0, final EventHandler p1, final Target p2);
    
    EventHandler makeEventHandler(final ModelProxy p0, final Console16bit p1);
    
    ByteChannel makeByteChannel(final InputStream p0, final OutputStream p1);
    
    Target makeTarget(final ByteChannel p0);
    
    Console16bit makeConsole();
    
    Bootloader16Model makeBootloader16Model();
    
    SerialAdapter makeSerialAdapter(final Console16bit p0);
    
    SerialAdapter makeMockAdapter(final Console16bit p0);
    
    SerialAdapterBuilder makeAdapterBuilder(final Console16bit p0);
    
    SegmentFactory makeSegmentFactory();
    
    SerialAdapterFactory makeSerialAdapterFactory(final Console16bit p0);
    
    WriteCommandConsumer makeWriteCommandConsumer();
}
