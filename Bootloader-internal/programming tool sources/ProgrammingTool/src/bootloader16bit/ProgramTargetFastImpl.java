// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Collection;
import java.util.HashMap;
import java.util.ArrayList;
import java.io.IOException;

class ProgramTargetFastImpl implements Runnable
{
    private CommandFactory commandFactory;
    private CommandStatusFactory commandStatusFactory;
    private Bootloader16AbstractFactory factory;
    private final ModelProxy model;
    private final Target target;
    private EventHandler eventHandler;
    private int pages;
    private Integer minWriteSize;
    private Integer maxPacketSize;
    
    ProgramTargetFastImpl(final Bootloader16AbstractFactory factory, final ModelProxy model, final Target target, final EventHandler eventHandler) {
        this.commandFactory = new CommandFactoryImpl();
        this.commandStatusFactory = new CommandStatusFactoryImpl();
        this.factory = factory;
        this.model = model;
        this.target = target;
        this.eventHandler = eventHandler;
    }
    
    @Override
    public void run() {
        try {
            this.flushInput();
            this.getVersion();
            this.erase();
            this.program();
            if (this.model.isReadBackVerifyEnabled()) {
                this.readBackVerify();
            }
            if (this.model.isSelfVerifyEnabled()) {
                this.selfVerify();
            }
            if (this.model.isResetEnabled()) {
                this.reset();
            }
            this.eventHandler.finishedEverything();
        }
        catch (VerificationException e) {
            this.eventHandler.readBackVerificationFailed(e.getAddress(), e.getActual(), e.getExpected());
        }
        catch (IOException e2) {
            this.eventHandler.ioException(e2);
        }
        catch (TimeoutException e3) {
            this.eventHandler.timeoutException(e3);
        }
        catch (ChecksumException e4) {
            this.eventHandler.checksumFailed(e4.getRecordLine());
        }
        catch (SelfVerificationException e5) {
            if (e5.getMessage().equals(SelfVerificationException.NOT_SUPPORTED)) {
                this.eventHandler.selfVerificationNotSupported();
            }
            else {
                this.eventHandler.selfVerificationFailed();
            }
        }
        catch (BadResponseException e6) {
            this.eventHandler.badResponse(e6.getRequest(), e6.getResponse());
        }
        catch (IllegalStateException e7) {
            this.eventHandler.illegalState(e7);
        }
    }
    
    private void getVersion() throws IOException, TimeoutException {
        final Command version = this.target.getVersion();
        this.minWriteSize = version.accept((FnCommandVisitor<Integer>)new FnMinWriteSizeAccessor());
        this.pages = this.model.getPages(version.accept((FnCommandVisitor<Integer>)new FnErasePageSizeAccessor()));
        this.maxPacketSize = version.accept((FnCommandVisitor<Integer>)new FnMaxPacketSize());
    }
    
    private void flushInput() throws IOException {
        this.target.flushInput();
    }
    
    private void readBackVerify() throws VerificationException, IOException, TimeoutException, ChecksumException, BadResponseException {
        this.eventHandler.readBackVerificationRequested();
        final List<Command> allCommands = new ArrayList<Command>();
        final Map<Integer, Integer> actual = new HashMap<Integer, Integer>();
        final Map<Integer, Integer> filteredImage = this.model.getFilteredImage();
        final SegmentedImage segmentedImage = this.factory.makeSegmentedImage(filteredImage);
        for (final Segment segment : segmentedImage.makeSegments()) {
            final VerificationCommandProducer producer = this.makeVerificationCommandProducer(segment);
            allCommands.addAll(producer.makeCommands());
        }
        final double tasksTotal = allCommands.size();
        double tasksComplete = 0.0;
        for (final Command command : allCommands) {
            actual.putAll(this.target.read(command));
            ++tasksComplete;
            this.eventHandler.setProgress(tasksComplete / tasksTotal);
        }
        for (final Map.Entry<Integer, Integer> expected : filteredImage.entrySet()) {
            final Integer address = expected.getKey();
            final Integer expectedValue = expected.getValue();
            if (!actual.containsKey(address)) {
                throw new IllegalStateException(String.format("We expected the actual image to contain %x, but it didn't!  This is a unified host bug!", address));
            }
            final Integer actualValue = actual.get(address);
            if (!expectedValue.equals(actualValue)) {
                throw new VerificationException(address, actualValue, expectedValue);
            }
        }
        this.eventHandler.readBackVerificationPassed();
    }
    
    private VerificationCommandProducer makeVerificationCommandProducer(final Segment segment) {
        final Integer headerSize = this.makeResponsePrototype().accept((FnCommandVisitor<Integer>)new FnPrototypeSizeVisitorImpl());
        final int maxResponsePayloadSize = this.maxPacketSize - headerSize;
        return this.factory.makeVerificationCommandProducer(segment, maxResponsePayloadSize);
    }
    
    private Command makeResponsePrototype() {
        return new PropCommandBase().setCommand(this.commandFactory.getWriteFlashCommandId()).setAddress(0L).setLength(0).setUnlock(this.commandFactory.getUnlockSequence()).setStatus(1);
    }
    
    private void erase() throws IOException, TimeoutException, BadResponseException {
        this.eventHandler.eraseRequested();
        this.target.erasePages(this.model.getApplicationStart(), this.pages);
        this.eventHandler.eraseFinished();
    }
    
    private void program() throws IOException, TimeoutException, ChecksumException, BadResponseException {
        this.eventHandler.programmingStarted();
        final Integer headerSize = this.factory.makeWriteCommandConsumer().getHeaderSize();
        final int maxPayloadSize = this.maxPacketSize - headerSize;
        final WriteCommandProducer producer = this.factory.makeWriteCommandProducer(this.model.getFilteredImage(), maxPayloadSize, this.minWriteSize);
        final List<Command> commands = producer.makeCommands();
        final double tasksTotal = commands.size();
        final double[] tasksComplete = { 0.0 };
        final Object o;
        final int n;
        final Object o2;
        this.target.write(commands, () -> {
            ++o[n];
            this.eventHandler.setProgress(o[0] / o2);
            return;
        });
        this.eventHandler.programmingFinished();
    }
    
    private void selfVerify() throws IOException, TimeoutException, BadResponseException, VerificationException, SelfVerificationException {
        this.eventHandler.selfVerificationRequested();
        this.eventHandler.setProgress(0.5);
        final Integer selfVerifyResult = this.target.selfVerify();
        this.eventHandler.setProgress(1.0);
        if (selfVerifyResult == this.commandStatusFactory.getVerifyFailId()) {
            throw new SelfVerificationException(SelfVerificationException.VERIFY_FAILED);
        }
        if (selfVerifyResult == this.commandStatusFactory.getCommandUnsupportedId()) {
            throw new SelfVerificationException(SelfVerificationException.NOT_SUPPORTED);
        }
        this.eventHandler.selfVerificationPassed();
    }
    
    private void reset() throws IOException, TimeoutException, BadResponseException {
        this.eventHandler.resetRequested();
        this.target.reset();
        this.eventHandler.resetSuccessful();
    }
}
