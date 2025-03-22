package Model;

import org.junit.jupiter.api.Test;

import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

class WaterTest {
 @Test
 public void getContentsOfBoxTest(){
   Water water = new Water();
   //null
   assert Objects.equals(water.getContentsOfBox(null), BoxStates.WATER);
   //not null
   Hidden hdden = new Hidden();
   assert Objects.equals(water.getContentsOfBox(hdden), BoxStates.WATER);
 }
}