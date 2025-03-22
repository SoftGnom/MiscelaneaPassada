
package base.no.states.requests;
import base.no.states.areas.DirectoryAreas;
import base.no.states.doors.Door;
import java.util.ArrayList;
import org.json.JSONArray;
import org.json.JSONObject;

//A subclass of the template method
//It's the one in charge of painting the doors
//in the visual part of the simulator

public class RequestRefresh implements Request {
  private final ArrayList<JSONObject> jsonsDoors = new ArrayList<>();
  @Override
  public JSONObject answerToJson() {
    JSONObject json = new JSONObject();
    json.put("doors", new JSONArray(jsonsDoors));
    // jsonDoors has been set previously by process()
    return json;
  }
  @Override
  public String toString() {
    return "RequestRefresh{"
        + jsonsDoors
        + "}";
  }

  // Also this is used to paint the simulator
  // when the page is loaded, and to display
  // doors and readers after passing from
  // locked to propped or propped to locked,
  // pressing the Refresh Request button of the simulator.
  // Also, to quickly test if the partition
  // requests sent by the client app in Flutter
  // works or not, retrieves the state
  // of all the doors so that the simulator can
  // repaint the readers
  public void process() {
    for (Door door : DirectoryAreas.getAllDoors()) {
      jsonsDoors.add(door.toJson());
    }
  }
}
