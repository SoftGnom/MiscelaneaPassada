package Controller;

import Model.BoxStates;
import Model.PartOfShip;
import Model.Revealed;
import Model.Box;
import View.View;

import javax.lang.model.type.PrimitiveType;
import javax.sound.midi.SysexMessage;
import java.awt.*;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;

public class Game {

  private View view;
  private ArrayList<Player> players;
  private int sizeX;
  private int sizeY;
  private int numberOfShips;
  private final static int  numberPlayers = 2;


  public Game() {
    view = new View();
  }

  // retorna el guanyador
  public ArrayList<String> play(){

    //slecionar la mida
    ArrayList<Integer> size = view.askForSizeOfBoard();
    sizeY = size.get(0);
    sizeX = size.get(1);

    numberOfShips = view.askForNumberOfShips();//int 3

    //slecionar, els jugadors demanar el nom
    createPlayers();

    //torns
    int i = 0;//selector de jugador
    do {
      view.viewMisathe("Change turn!",players.get(i).getName());

      playerTurn(players.get(i), players.get(playerChange(i)));

      i = playerChange(i);
    }while (!players.get(i).lose());
    i = playerChange(i);
    view.viewMisathe("Game over. Thanks for playing!\n\t\tThe winner is " + players.get(i).getName(), "End Game");

    ArrayList<String> result = new ArrayList<>();
    result.add(players.get(i).getName());//0-> guanyador
    result.add(players.get(playerChange(i)).getName());//1->perdedor
    return result;
  }
  private int playerChange(int i){
    if (i == 0){
      return 1;
    }
    return 0;
  }
  //per treure requeriments a play
  private void createPlayers(){
    ArrayList<String> names;
    names = view.askForPlayersNames();
    players = new ArrayList<>();

    for (int j = 0; j < numberPlayers; j++) {
      players.add(new Player(names.get(j),sizeX,sizeY));
      for (int i = 0; i < numberOfShips; i++) {
        ArrayList<Integer> data = view.getDataOfShip("Create Ships: " + names.get(j));
        if (!players.get(j).addShip(data.get(0), new Point(data.get(1), data.get(2)), new Point(data.get(3), data.get(4)))) {
          view.viewMisathe("Error: occurred while inserting the ship", "Create Ships: " + names.get(j));
          i--;
        }
      }

    }
  }
  private void playerTurn(Player currentPlayer, Player opponentPlayer) {
    ArrayList<Integer> axis = new ArrayList<>();

    // Perform the shot
    do {//ArrayList<Integer> axis = new ArrayList<>();axis.add(x);axis.sdd(y);
      axis = view.chooseTheBox(          //mostar  i demanar entrada
          currentPlayer.getToSolveReveled(   // demanar el boad ToSolve amb les caselles revelades
              opponentPlayer.getOwnBoard())   // demanar el boad Own
          , ("Turn: " + currentPlayer.getName())
      );
    }while(!isBoxIsHidden(axis,currentPlayer, opponentPlayer));

    // Update the opponent's board
    currentPlayer.revealedABoxOfBoardToSolve(axis.get(0), axis.get(1));
    opponentPlayer.shoot(axis.get(0), axis.get(1));
    // Display the result of the shot
    view.showTheBoard(
        currentPlayer.getToSolveReveled(   // demanar el boad ToSolve amb les caselles revelades
            opponentPlayer.getOwnBoard())   // demanar el boad Own
        , ("Turn: " + currentPlayer.getName())
    );
  }
  private boolean isBoxIsHidden(ArrayList<Integer> axis,Player currentPlayer, Player opponentPlayer){
    return (Objects.equals(
        currentPlayer.getARealPrintOfABoxOfBoardToSolve(  //obtenir el print de la casella del tauler no resolt, pero substituit els Reveled per Water o Part Of Ship
            opponentPlayer.getOwnBoard(),
            axis.get(0), axis.get(1))
        , BoxStates.HIDDEN));

  }

  //Test:
  public int playerChangeTest(int i){
    return playerChange(i);
  }
  public boolean isBoxIsHiddenTest(ArrayList<Integer> axis,Player currentPlayer, Player opponentPlayer){
    return isBoxIsHidden(axis, currentPlayer, opponentPlayer);
  }
  public void createPlayersTest(){
    createPlayers();
  }
  public void playerTurnTest(Player currentPlayer, Player opponentPlayer) {
    playerTurn(currentPlayer, opponentPlayer);
  }
  public void setView(View views){
    view = views;
  }
  public void setSizeX(int size){
    sizeX = size;
  }
  public void setSizeY(int size){
    sizeY = size;
  }
  public void setNumberOfShips(int size){
    numberOfShips = size;
  }
  public ArrayList<Board> getOwnBoard() {
    ArrayList<Board> boards = new ArrayList<>();
    boards.add(players.get(0).getOwnBoard());
    boards.add(players.get(1).getOwnBoard());
    return boards;
  }
  public ArrayList<Player> getPlayers(){
    return players;
  }
 }
