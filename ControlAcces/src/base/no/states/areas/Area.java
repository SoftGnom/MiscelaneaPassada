
package base.no.states.areas;
import base.no.states.doors.Door;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

//This class represents the building or spaces within
//It's the component of the pattern composite
//This class organizes the areas of the composite

public abstract class Area {
    private String areaId;

    public Area(final String constructorAreaId) {
        this.areaId = constructorAreaId;
    }

    public String getId() {
        return areaId;
    }
    public ArrayList<Area> getAllAreasInside() {
        ArrayList<Area> areas = new ArrayList<>();
        areas.add(this);
        return areas;
    }
    public List<Door> getDoorsGivingAccess() {
        return null;
    }
    public abstract JSONObject toJson(int depth);
}
