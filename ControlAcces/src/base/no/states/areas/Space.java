
package base.no.states.areas;
import base.no.states.doors.Door;
import org.json.JSONArray;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

//This class represents the leafs
//of our composite pattern

public class Space extends Area {
    private List<Door> doorsGivingAccess;
    public Space(final String areaId) {
        super(areaId);
        doorsGivingAccess = new ArrayList<>();
    }
    public List<Door> getDoors() {
        return doorsGivingAccess;
    }
    @Override
    public List<Door> getDoorsGivingAccess() {
        return doorsGivingAccess; }
    public void addDoorsGivingAccess(final Door door) {
        doorsGivingAccess.add(door);
    }
    public JSONObject toJson(int depth) { // depth not used here
        JSONObject json = new JSONObject();
        json.put("class", "space");
        json.put("id", getId());
        JSONArray jsonDoors = new JSONArray();
        for (Door d : doorsGivingAccess) {
            jsonDoors.put(d.toJson());
        }
        json.put("access_doors", jsonDoors);
        return json;
    }
}
