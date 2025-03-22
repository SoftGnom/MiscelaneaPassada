package Controller;

import java.util.ArrayList;

public class MockGame extends Game{
  private boolean boolPlay;

  public void setBoolPlay(boolean bool){
    boolPlay = bool;
  }
  public boolean getBoolPlay(){
    return boolPlay;
  }

  @Override
  public ArrayList<String> play(){

    boolPlay=!boolPlay;

    ArrayList<String> aux = new ArrayList<>();
    aux.add("p1");
    aux.add("p1");
    return aux;
  }


}
