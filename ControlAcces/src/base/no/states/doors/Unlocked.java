
package base.no.states.doors;
import base.no.states.FakeFita2;
import base.no.states.States;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

//It's ones of the states of the door

public class Unlocked extends DoorState {
    private static final Logger LOGGER = LoggerFactory.getLogger("Fita1");
    public Unlocked(final Door door) {
        super(door);
    }
    @Override
    public String getState() {
        return States.UNLOCKED;
    }
    @Override
    public void open() {
        if (getDoor().isClosed()) {
            getDoor().setClosed(false);
        } else {
            LOGGER.info(
                    "Can't open door "
                            + getDoor().getId() + " because it's already open");
            //This next to lines executes a singleton
            //and another level of our logger.
            //It has no real relevance in the main use of the program
            FakeFita2 prova = FakeFita2.getInstance();
            prova.loggerTest();
        }
    }
    @Override
    public void close() {
        if (getDoor().isClosed()) {
            LOGGER.info(
                    "Can't close door "
                            + getDoor().getId()
                            + " because it's already closed");
        } else {
            getDoor().setClosed(true);
        }
    }
    @Override
    public void lock() {
        if (getDoor().isClosed()) {
            getDoor().setState(new Locked(getDoor()));
        } else {
            LOGGER.info("Can't lock an open door");
        }
    }
    @Override
    public void unlock() {
        LOGGER.info("Can't unlock an unlocked door");
    }

}
