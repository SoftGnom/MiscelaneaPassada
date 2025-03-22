
package base.no.states;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

//This is a singleton created to test the different
//levels of the logger

 public final class FakeFita2 {
    private static final Logger FAKE_FITA2_LOGGER = LoggerFactory.getLogger(
            "fakeFita2");
    private static FakeFita2 uniqueInstance = null;
    private FakeFita2() { }
    public static FakeFita2 getInstance() {
        if (uniqueInstance == null) { // lazy initialization
            FAKE_FITA2_LOGGER.debug("Initialize unique instance");
            uniqueInstance = new FakeFita2();
        }
        return uniqueInstance;
    }
    public void loggerTest() {
        FAKE_FITA2_LOGGER.debug("This is a debug message of fakeFita2");
        FAKE_FITA2_LOGGER.info("This is a info message of fakeFita2");
        FAKE_FITA2_LOGGER.warn("This is a warning message of fakeFita2");
        FAKE_FITA2_LOGGER.error("This is a error message of fakeFita2");
    }
}
