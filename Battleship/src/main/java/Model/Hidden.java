package Model;

public class Hidden implements Box {//Casella oculta
  public Hidden() { }
  @Override
  public String getContentsOfBox(Box boxResolved){
    return BoxStates.HIDDEN;
  }

}
