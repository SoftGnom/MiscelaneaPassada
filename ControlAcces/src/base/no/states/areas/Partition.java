
package base.no.states.areas;
import base.no.states.doors.Door;
import org.json.JSONArray;
import org.json.JSONObject;
import java.util.ArrayList;
import java.util.List;

//This class is the container of our pattern composite

public class Partition extends Area {
    private ArrayList<Area> areaInside = new ArrayList<>();
    public Partition(final String areaId) {
        super(areaId);
    }
    void addPartition(final Area partition) {
        areaInside.add(partition);
    }
    public ArrayList<Area> getAllAreasInside() {
        ArrayList<Area> areas  = new ArrayList<>();
        areas .add(this);
        for (Area areaIterator: areaInside) {
            areas.addAll(areaIterator.getAllAreasInside());
        }
        return areas;
    }
    @Override
    public List<Door> getDoorsGivingAccess() {
        List<Door> doors = new ArrayList<>();
        for (Area area: areaInside) {
            doors.addAll(area.getDoorsGivingAccess());
        }
        return doors;
    }

    public JSONObject toJson(int depth) {
        // for depth=1 only the root and children,
        // for recusive = all levels use Integer.MAX_VALUE
        JSONObject json = new JSONObject();
        json.put("class", "partition");
        json.put("id", getId());
        JSONArray jsonAreas = new JSONArray();
        if (depth > 0) {
            for (Area a : areaInside) {
                jsonAreas.put(a.toJson(depth - 1));
            }
            json.put("areas", jsonAreas);
        }
        return json;
    }
}
