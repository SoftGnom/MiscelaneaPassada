
package base.no.states.areas;
import base.no.states.doors.Door;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import java.util.ArrayList;
import java.util.Arrays;

//This class instantiates all the components
//that will form part of the composite

public final class DirectoryAreas {
    private static final Logger LOGGER = LoggerFactory.getLogger("Fita1");
    private static ArrayList<Area> allAreas;
    private static ArrayList<Door> allDoors;
    private static DirectoryAreas instance = null;
    private DirectoryAreas() { }
    public static synchronized DirectoryAreas getInstance() {
        if (instance == null) {
            instance = new DirectoryAreas();
        }
        return instance;
    }
    public static void makeAreas() {
        // all areas serve to block the doors that give access to the areas
        // and areas within them

        //building
        Partition building = new Partition("building");


        ///basement
        Partition basement = new Partition("basement");
        building.addPartition(basement);
        ////parking
        Space parking = new Space("parking");
        basement.addPartition(parking);
        /////D1
        Door d1 = new Door("D1", "exterior", "parking");
        parking.addDoorsGivingAccess(d1);
        /////D2
        Door d2 = new Door("D2", "stairs", "parking");
        parking.addDoorsGivingAccess(d2);

        ///ground_floor
        Partition groundFloor = new Partition("ground_floor");
        building.addPartition(groundFloor);
        ////room_1
        Space room1 = new Space("room1");
        groundFloor.addPartition(room1);
        /////D5
        Door d5 = new Door("D5", "hall", "room1");
        room1.addDoorsGivingAccess(d5);
        ////room_2
        Space room2 = new Space("room2");
        groundFloor.addPartition(room2);
        /////D6
        Door d6 = new Door("D6", "hall", "room2");
        room2.addDoorsGivingAccess(d6);
        ////hall
        Space hall = new Space("hall");
        groundFloor.addPartition(hall);
        /////D4
        Door d4 = new Door("D4", "stairs", "hall");
        hall.addDoorsGivingAccess(d4);
        /////D3
        Door d3 = new Door("D3", "exterior", "hall");
        hall.addDoorsGivingAccess(d3);

        ///floor_1
        Partition floor1 = new Partition("floor1");
        building.addPartition(floor1);
        ////room_3
        Space room3 = new Space("room3");
        floor1.addPartition(room3);
        /////D8
        Door d8 = new Door("D8", "corridor", "room3");
        room3.addDoorsGivingAccess(d8);
        ////corridor
        Space corridor = new Space("corridor");
        floor1.addPartition(corridor);
        /////D7
        Door d7 = new Door("D7", "stairs", "corridor");
        corridor.addDoorsGivingAccess(d7);
        ////IT
        Space iT = new Space("IT");
        floor1.addPartition(iT);
        /////D9
        Door d9 = new Door("D9", "corridor", "IT");
        iT.addDoorsGivingAccess(d9);

        ///stairs
        Partition stairs = new Partition("stairs");
        building.addPartition(stairs);

        ///exterior
        Partition exterior = new Partition("exterior");
        building.addPartition(exterior);


        allAreas = new ArrayList<>(Arrays.asList(building));
        allDoors = new ArrayList<>(
                Arrays.asList(d1, d2, d3, d4, d5, d6, d7, d8, d9));
    }
    public static Area findAreaById(final String id) {
        for (Area area : allAreas) {
            for (Area placesId : area.getAllAreasInside()) {
                if (placesId.getId().equals(id)) {
                    return placesId;
                }
            }

        }
        LOGGER.warn("Area with id " + id + " not found");
        return null; // otherwise we get a Java error
    }
    public static Door findDoorById(final String id) {
        for (Door door : allDoors) {
            if (door.getId().equals(id)) {
                return door;
            }
        }
        LOGGER.warn("door with id " + id + " not found");
        return null; // otherwise we get a Java error
    }

    // this is needed by RequestRefresh
    public static ArrayList<Door> getAllDoors() {
        LOGGER.debug(allDoors.toString());
        return allDoors;
    }
}
