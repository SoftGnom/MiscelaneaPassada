package Model;

public class Water  implements Box {
  public Water() {
  }

  @Override
  public String getContentsOfBox(Box boxResolved){
    return BoxStates.WATER;
  }

}
