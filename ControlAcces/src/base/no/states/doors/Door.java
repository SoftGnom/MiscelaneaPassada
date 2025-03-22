
package base.no.states.doors;
import base.no.states.Actions;
import base.no.states.requests.RequestReader;
import org.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

//This class represents a door of the building.
//It has a variable that implements
//the pattern State

public class Door {
  private final String id;
  private DoorState state;
  private String inArea;
  private String outArea;
  private boolean closed; // physically
  private static final Logger LOGGER = LoggerFactory.getLogger("Fita1");
  public Door(final String constructorId,
              final String constructorInArea,
              final String constructorOutArea) {
    this.id = constructorId;
    closed = true;
    state = new Unlocked(this);
    this.inArea = constructorInArea;
    this.outArea = constructorOutArea;
  }
  public boolean isClosed() {
    return closed;
  }
  public String getId() {
    return id;
  }
  public String getStateName() {
    return state.getState();
  }
  public void setState(final DoorState doorState) {
    this.state = doorState;
  }
  public void setClosed(final boolean closing) {
    closed = closing;
  }
  public String getInArea() {
    return inArea; }
  public String getOutArea() {
    return outArea; }
  public void processRequest(final RequestReader request) {
    // it is the Door that process the request because the door has and knows
    // its state, and if closed or open
    if (request.isAuthorized()) {
      String action = request.getAction();
      doAction(action);
    } else {
      LOGGER.warn("not authorized");
    }
    request.setDoorStateName(getStateName());
  }

  //redirect the call to the relevant function
  private void doAction(final String action) {
    switch (action) {

      case Actions.OPEN:
        state.open();
        break;
      case Actions.CLOSE:
        state.close();
        break;
      case Actions.LOCK:
        state.lock();
        break;
      case Actions.UNLOCK:
        state.unlock();
        break;
      case Actions.UNLOCK_SHORTLY:
        LOGGER.error("Action " + action + " not implemented yet");
        break;
      default:
        assert false : "Unknown action " + action;
        System.exit(-1);
    }
  }
  @Override
  public String toString() {
    return "Door{"
        + ", id='" + id + '\''
        + ", closed=" + isClosed()
        + ", state=" + getStateName()
        + "}";
  }
  public JSONObject toJson() {
    JSONObject json = new JSONObject();
    json.put("id", id);
    json.put("state", getStateName());
    json.put("closed", isClosed());
    return json;
  }
}
