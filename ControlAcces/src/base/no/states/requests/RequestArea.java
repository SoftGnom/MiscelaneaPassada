
package base.no.states.requests;
import base.no.states.Actions;
import org.json.JSONArray;
import org.json.JSONObject;
import base.no.states.areas.Area;
import base.no.states.areas.DirectoryAreas;
import base.no.states.doors.Door;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

//One of the subclasses of the template method
//It recieves request for an entire area and it divides
//in smaller request to be procesed individually

public class RequestArea implements Request {
  private final String credential;
  private final String action;
  private final String areaId;
  private final LocalDateTime now;
  private ArrayList<RequestReader> requests = new ArrayList<>();
  public RequestArea(
          final String consCredential, final String consAction,
          final LocalDateTime consNow, final String consAreaId) {
    this.credential = consCredential;
    this.areaId = consAreaId;
    assert consAction.equals(Actions.LOCK) || consAction.equals(Actions.UNLOCK)
            : "invalid action " + consAction + " for an area request";
    this.action = consAction;
    this.now = consNow;
  }
  public String getAction() {
    return action;
  }
  @Override
  public JSONObject answerToJson() {
    JSONObject json = new JSONObject();
    json.put("action", action);
    json.put("areaId", areaId);
    JSONArray jsonRequests = new JSONArray();
    for (RequestReader rd : requests) {
      jsonRequests.put(rd.answerToJson());
    }
    json.put("requestsDoors", jsonRequests);
    return json;
  }
  @Override
  public String toString() {
    String requestsDoorsStr;
    if (requests.size() == 0) {
      requestsDoorsStr = "";
    } else {
      requestsDoorsStr = requests.toString();
    }
    return "Request{"
            + "credential=" + credential
            + ", action=" + action
            + ", now=" + now
            + ", areaId=" + areaId
            + ", requestsDoors=" + requestsDoorsStr
            + "}";
  }

  // processing the request of an area
  // is creating the corresponding door requests and forwarding
  // them to all of its doors. For some it may be authorized
  // and action will be done, for others
  // it won't be authorized and nothing will happen to them.
  public void process() {
    // commented out until Area, Space and Partition are implemented

    // make the door requests and put them into the area
    // request to be authorized later and
    // processed later
    Area area = DirectoryAreas.findAreaById(areaId);
    // an Area is a Space or a Partition
    if (area != null) {
      // is null when from the app we click on
      // çan action but no place is selected because
      // there (flutter) I don't control like I do in
      // javascript that all the parameters are provided
      // Make all the door requests, one for each
      // door in the area, and process them.
      // Look for the doors in the spaces of this area that give access to them.
      List<Door>  a = area.getDoorsGivingAccess();
      for (Door door : a) {
        RequestReader requestReader = new RequestReader(
                credential, action, now, door.getId());
        requestReader.process();
        // after process() the area request contains the answer as the answer
        // to each individual door request, that
        // is read by the simulator/Flutter app
        requests.add(requestReader);
      }
    }
  }
}
