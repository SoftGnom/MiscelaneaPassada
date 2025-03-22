package Model;

import org.junit.jupiter.api.Test;

import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

class HiddenTest {
  @Test
  public void getContentsOfBoxTest(){
    Hidden hidden = new Hidden();
    //es null
    assert Objects.equals(hidden.getContentsOfBox(null), BoxStates.HIDDEN);
    //es no null
    Water water = new Water();
    assert Objects.equals(hidden.getContentsOfBox(water), BoxStates.HIDDEN);
  }
}