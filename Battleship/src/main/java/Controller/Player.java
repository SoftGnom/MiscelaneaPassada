package Controller;

import Model.Revealed;
import Model.Box;
import Model.Water;

import java.awt.*;
import java.util.ArrayList;
import java.util.Scanner;

public class Player {

  private Board ToSolve;
  private Board Own;
  private int sizeX;
  private int sizeY;
  private String name;

  public Player(String name, int sizeX, int sizeY) {
    this.name = name;
    this.sizeX = sizeX;
    this.sizeY = sizeY;
    ToSolve = new Board();
    ToSolve.createBoardToSolve(sizeX, sizeY);
    Own = new Board();
    Own.createOwnBoard(sizeX, sizeY);
  }

  //retorna tauler parcialment complet amb les solucions amb format String no classes
  public ArrayList<ArrayList<String>> getToSolveReveled(Board opponentsBoard){
    ArrayList<ArrayList<String>> board = new ArrayList<>();

    for (int y = 0; y < sizeY; y++) {
      board.add(new ArrayList<>());
      for (int x = 0; x < sizeX; x++) {
        board.get(y).add(getARealPrintOfABoxOfBoardToSolve(opponentsBoard, x, y));
      }
    }

    return board;
  }
  //retorna el tauler complet amb les solucions
  public Board getOwnBoard(){ return Own; }

  //retorna una casella del tauler parcialment revelat amb les solucions amb format String no classes
  public String getARealPrintOfABoxOfBoardToSolve(Board opponentOwnBoard,int x, int y) {
    return ToSolve.getPrintBoxOfBoardTable(opponentOwnBoard, x, y);
  }
  //revela una casella de tauler ToSolve
  public void revealedABoxOfBoardToSolve(int x, int y){
    ToSolve.setBoxOfBoardTable(new Revealed(),x,y);
  }

  public String getName() {
    return name;
  }

  public boolean lose(){
    return Own.allShipsAreDead();
  }

  public boolean addShip(int size, Point p1, Point p2){
    if (Own.iCanPutTheShipOnTheBoard(size,p1,p2) && size>1 && size < 10){
      Ship ship = new Ship();
      ship.crateShip(size);
      Own.putTheShipOnTheBoard(ship,p1,p2);
      return true;
    }
    return false;
  }
  public void shoot(int x, int y){
    Own.shoot(x,y);
  }

  //test
  public Board getToSolveBoard(){
    return ToSolve;
  }

}
