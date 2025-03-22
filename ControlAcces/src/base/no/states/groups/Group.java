
package base.no.states.groups;
import base.no.states.areas.Area;
import java.time.LocalDateTime;
import java.util.ArrayList;

//This class is used to save the information
//of each of the roles
//It also has the function to authorize the action
//of users

public class Group {
    private String groupId;
    private ArrayList<User> groupUsers = new ArrayList<>();
    private ArrayList<Area> allAreas = new ArrayList<>();
    private ArrayList<String> actions = new ArrayList<>();
    private Schedule time = new Schedule();
    public Group(final String constructorGroupId) {
        this.groupId = constructorGroupId;
    }
    public void addAtGroup(final User user) {
        groupUsers.add(user);
    }
    public void addArea(final Area area) {
        allAreas.add(area);
    }
    public void addAction(final String action) {
        actions.add(action);
    }
    public void setSchedule(final Schedule schedule) {
        this.time = schedule;
    }
    public boolean isAuthorized(final LocalDateTime now) {
        if (time != null) {
            return time.isAuthorized(now);
        } else {
            return false;
        }

    }
    public boolean authorizedSpaces(final String space) {
        for (Area area: allAreas) {
            for (Area placesId : area.getAllAreasInside()) {
                if (space == placesId.getId()) {
                    return true;
                }
            }
        }
        return false;
    }
    public boolean authorizedAction(final String action) {
        return actions.contains(action);
    }
}
