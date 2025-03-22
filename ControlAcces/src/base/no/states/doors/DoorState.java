
package base.no.states.doors;
import base.no.states.States;

//It implements the state of the door
//using the pattern State

public abstract class DoorState {
    private Door door;
    private String name;
    public DoorState(final Door constructorDoor) {
        this.door = constructorDoor;
    }
    public String getState() {
        return States.UNLOCKED;
    }

    public Door getDoor() {
        return door;
    }

    public void setDoor(final Door setDoor) {
        this.door = setDoor;
    }
    public String getName() {
        return name;
    }
    public void setName(final String setName) {
        this.name = setName;
    }
    public void open() { }
    public void close() { }
    public void lock() { }
    public void unlock() { }
}
