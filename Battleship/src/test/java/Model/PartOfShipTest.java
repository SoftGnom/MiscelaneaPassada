package Model;

import org.junit.jupiter.api.Test;

import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

class PartOfShipTest {
  @Test
  public void ConstructorTest(){
    PartOfShip shipEnd = new PartOfShip(BoxStates.END_OF_THE_SHIP);

    //ok part
    assert Objects.equals(shipEnd.getContentsOfBox(null), BoxStates.END_OF_THE_SHIP);
    //ok hit
    assert !shipEnd.isHit();
  }
  @Test
  public void getContentsOfBoxTest(){
    PartOfShip shipEnd = new PartOfShip(BoxStates.END_OF_THE_SHIP);
    PartOfShip shipMiddle = new PartOfShip(BoxStates.MIDDLE_OF_THE_SHIP);

    //ok null
    assert Objects.equals(shipEnd.getContentsOfBox(null), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(shipMiddle.getContentsOfBox(null), BoxStates.MIDDLE_OF_THE_SHIP);

    //ok no null
    assert Objects.equals(shipEnd.getContentsOfBox(shipMiddle), BoxStates.END_OF_THE_SHIP);
  }
  @Test
  public void shootTest(){
    PartOfShip part = new PartOfShip(BoxStates.MIDDLE_OF_THE_SHIP);

    //s'hactualitza
    assert !part.isHit();
    part.shoot();
    assert part.isHit();
  }
}