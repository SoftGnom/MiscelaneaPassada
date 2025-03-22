package View;

import Model.OptionsMenu;

import java.util.ArrayList;
import java.util.Scanner;

public class MockView extends View{

  private boolean boolView;
  private int repetitionCounter;
  private int maxRepetition;
  private ArrayList<ArrayList<Integer>> data;
  private int repetitionCounter1;
  private int maxRepetition1;
  private ArrayList<ArrayList<Integer>> data1;
  private int viewInt;
  private ArrayList<String> name;
  private ArrayList<Integer> sizeOfBoard;
  private int numberOfShips;


  public void setViewInt(int ints){
    viewInt = ints;
  }
  public int getViewInt(){
    return viewInt;
  }
  public void setBoolView(boolean bool){
    boolView = bool;
  }
  public boolean getBoolView(){
    return boolView;
  }
  public void setRepetitionCounter(int number){
    repetitionCounter = number;
  }
  @Override
  public void showRanking(ArrayList<String> ranking){
    boolView = !boolView;
  }
  @Override
  public void viewMisathe(String misathe,String name){
    boolView = !boolView;
  }

  @Override
  public int menu(ArrayList<String> options, int size){
    if (repetitionCounter>0){
      repetitionCounter-=1;
      return viewInt;
    } else {
      return OptionsMenu.EXIT;
    }

  }


  //per el test de createPlayer

  public void setAskForPlayersNames(ArrayList<String> names){
    name=names;
  }
  public ArrayList<String> askForPlayersNames() {
    return name;
  }
  public void setGetDataOfShip(ArrayList<ArrayList<Integer>> datas, int maxRepetitions){
    data = datas;
    maxRepetition=maxRepetitions;
    repetitionCounter=maxRepetitions;
  }
  public ArrayList<Integer> getDataOfShip(String name) {
    repetitionCounter-=1;
    if (repetitionCounter==-2){
      repetitionCounter=(maxRepetition-1);
    }
    return data.get(repetitionCounter+1);
  }

  //per el test de playerTorn

  public void setChooseTheBox(ArrayList<ArrayList<Integer>> datas, int maxRepetitions){
    data1 = datas;
    maxRepetition1=maxRepetitions;
    repetitionCounter1=maxRepetitions;
  }

  public ArrayList<Integer> chooseTheBox(ArrayList<ArrayList<String>> board, String text){
    repetitionCounter1-=1;
    if (repetitionCounter1==-2){
      repetitionCounter1=(maxRepetition1-1);
    }
    return data1.get(repetitionCounter1+1);
  }

  public void showTheBoard(ArrayList<ArrayList<String>> board, String text) { }

  //per el test de play

  public void setAskForSizeOfBoard(ArrayList<Integer> size){
    sizeOfBoard = size;
  }
  public ArrayList<Integer> askForSizeOfBoard(){
    return sizeOfBoard;
  }

  public void setAskForNumberOfShips(int number){
    numberOfShips = number;
  }
  public int askForNumberOfShips(){
    return numberOfShips;
  }

}
