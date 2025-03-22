
package base.no.states.requests;
import java.time.LocalDateTime;
import java.util.ArrayList;
import base.no.states.areas.DirectoryAreas;
import base.no.states.groups.DirectoryGroup;
import base.no.states.groups.User;
import base.no.states.doors.Door;
import org.json.JSONArray;
import org.json.JSONObject;

//A subclass of the template method.
//It takes charge of the individual request
//Individual meaning that only affects one door

public class RequestReader implements Request {
  private final String credential; // who
  private final String action;     // what
  private final LocalDateTime now; // when
  private final String doorId;     // where
  private String userName;
  private boolean authorized;
  private final ArrayList<String> reasons; // why not authorized
  private String doorStateName;
  private boolean doorClosed;
  public RequestReader(
          final String consCredential, final String consAction,
          final LocalDateTime consNow, final String consDoorId) {
    this.credential = consCredential;
    this.action = consAction;
    this.doorId = consDoorId;
    reasons = new ArrayList<>();
    this.now = consNow;
  }
  public void setDoorStateName(final String name) {
    doorStateName = name;
  }
  public String getAction() {
    return action;
  }
  public boolean isAuthorized() {
    return authorized;
  }
  public void addReason(final String reason) {
    reasons.add(reason);
  }
  @Override
  public String toString() {
    if (userName == null) {
      userName = "unknown";
    }
    return "Request{"
            + "credential=" + credential
            + ", userName=" + userName
            + ", action=" + action
            + ", now=" + now
            + ", doorID=" + doorId
            + ", closed=" + doorClosed
            + ", authorized=" + authorized
            + ", reasons=" + reasons
            + "}";
  }
  public JSONObject answerToJson() {
    JSONObject json = new JSONObject();
    json.put("authorized", authorized);
    json.put("action", action);
    json.put("doorId", doorId);
    json.put("closed", doorClosed);
    json.put("state", doorStateName);
    json.put("reasons", new JSONArray(reasons));
    return json;
  }

  // see if the request is authorized and put this into the request,
  // then send it to the door.
  // if authorized, perform the action.
  public void process() {
    User user = DirectoryGroup.findUserByCredential(credential);
    Door door = DirectoryAreas.findDoorById(doorId);
    assert door != null : "door " + doorId + " not found";
    authorize(user, door);
    // this sets the boolean authorize attribute of the request
    door.processRequest(this);
    // even if not authorized we process the request,
    // so that if desired we could log all
    // the requests made to the server as part of processing the request
    doorClosed = door.isClosed();
  }

  // the result is put into the request object plus, if not authorized, why not,
  // only for testing
  private void authorize(final User user, final Door door) {
    if (user == null) {
      authorized = false;
      addReason("user doesn't exists");
    } else {
      boolean isAuthorized = user.getGrup().isAuthorized(now)
              && user.getGrup().authorizedSpaces(door.getInArea())
              && user.getGrup().authorizedSpaces(door.getOutArea())
              && user.getGrup().authorizedAction(action);
      if (!user.getGrup().isAuthorized(now)) {
        addReason("Out of hours");
      }
      if (!user.getGrup().authorizedSpaces(door.getInArea())) {
        addReason("Unable to access");
      }
      if (!user.getGrup().authorizedSpaces(door.getOutArea())) {
        addReason("Unable to access");
      }
      if (!user.getGrup().authorizedAction(action)) {
        addReason("The action cannot be performed\n");
      }

      if (isAuthorized) {
        authorized = true;
      } else {
        authorized = false;
        addReason("Authoritzation conditions are not met");
      }
    }
  }
}

