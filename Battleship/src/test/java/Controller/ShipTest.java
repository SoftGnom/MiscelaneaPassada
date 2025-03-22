package Controller;

import Model.BoxStates;
import org.junit.jupiter.api.Test;
import java.util.Objects;

class ShipTest {

  @Test
  public void createShipTest() {
    Ship ship = new Ship();

    //ship size:1 (error)
    ship.crateShip(1);
    assert Objects.equals(ship.getPart(0), null);
    //(ok):
    //ship size:2
    ship.crateShip(2);

    assert Objects.equals(ship.getPart(0).getContentsOfBox(null), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(ship.getPart(1).getContentsOfBox(null), BoxStates.END_OF_THE_SHIP);


    //ship size:5
    ship.crateShip(5);
    assert Objects.equals(ship.getPart(0).getContentsOfBox(null), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(ship.getPart(1).getContentsOfBox(null), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(ship.getPart(2).getContentsOfBox(null), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(ship.getPart(3).getContentsOfBox(null), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(ship.getPart(4).getContentsOfBox(null), BoxStates.END_OF_THE_SHIP);


    //ship size:9 (limitacio classe View)
    ship.crateShip(9);
    assert Objects.equals(ship.getPart(0).getContentsOfBox(null), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(ship.getPart(1).getContentsOfBox(null), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(ship.getPart(5).getContentsOfBox(null), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(ship.getPart(7).getContentsOfBox(null), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(ship.getPart(8).getContentsOfBox(null), BoxStates.END_OF_THE_SHIP);

  }

  @Test
  public void isDeadTest(){
    Ship ship = new Ship();
    ship.crateShip(3);

    ship.getPart(0).shoot();
    ship.getPart(1).shoot();
    //no tot amb hits
    assert !ship.isDead();

    ship.getPart(2).shoot();
    //si tot amb hits
    assert ship.isDead();
  }

  @Test
  public void getPartTest(){
    Ship ship = new Ship();

    //no te parts of Ship
    assert (ship.getPart(0) == null);

    ship.crateShip(4);
    //fora de rang
    assert (ship.getPart(-1) == null);
    assert (ship.getPart(4) == null);

    //en rang
    assert (Objects.equals(ship.getPart(0).getContentsOfBox(null), BoxStates.END_OF_THE_SHIP));

  }


}