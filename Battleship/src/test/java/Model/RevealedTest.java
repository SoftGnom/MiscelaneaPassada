package Model;

import org.junit.jupiter.api.Test;

import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

class RevealedTest {
  @Test
  public void getContentsOfBoxTest(){
    Revealed revealed = new Revealed();

    //es Water o PartOfShip i no null
    Water water = new Water();
    assert Objects.equals(revealed.getContentsOfBox(water), BoxStates.WATER);

    PartOfShip shipMiddle = new PartOfShip(BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(revealed.getContentsOfBox(shipMiddle), BoxStates.MIDDLE_OF_THE_SHIP);

    //no es Water o PartOfShip i no null
    Revealed revealed2 = new Revealed();
    assert Objects.equals(revealed.getContentsOfBox(revealed2), BoxStates.ERROR);

    //es null
    assert Objects.equals(revealed.getContentsOfBox(null), BoxStates.ERROR);


    //Hidden hidden = new Hidden();    //no ha de ser posible arribar aqui
    //assert Objects.equals(revealed.getContentsOfBox(hidden), BoxStates.HIDDEN);

  }
}