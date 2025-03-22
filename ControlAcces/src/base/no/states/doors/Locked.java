
package base.no.states.doors;
import base.no.states.States;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

//It's one of the states of the door

public class Locked extends DoorState {
    private static final Logger LOGGER = LoggerFactory.getLogger("Fita1");
    public Locked(final Door door) {
        super(door); }
    @Override
    public String getState() {
        return States.LOCKED; }
    @Override
    public void open() {
        LOGGER.info("Can't open a locked door");
    }
    @Override
    public void close() {
        LOGGER.info("Door already closed");
    }
    @Override
    public void lock() {
        LOGGER.info("Can't lock door that is already locked");
    }
    @Override
    public void unlock() {
        if (getDoor().isClosed()) {
            getDoor().setState(new Unlocked(getDoor()));
        }
    }

}
