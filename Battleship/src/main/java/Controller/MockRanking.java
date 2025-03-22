package Controller;

import java.util.ArrayList;

public class MockRanking extends Ranking{

  private boolean boolRanking;

  public void setBoolRanking(boolean bool){
    boolRanking = bool;
  }
  public boolean getBoolRanking(){
    return boolRanking;
  }
  @Override
  public void saveData(String winner, String loser){

    boolRanking = !boolRanking;

  }


  @Override
  public ArrayList<String> getData(){

    boolRanking = !boolRanking;

    ArrayList<String> aux = new ArrayList<>();
    aux.add("Winner: winner");
    aux.add("\t\tLoser: loser");
    aux.add("--");
    return aux;
  }
}
