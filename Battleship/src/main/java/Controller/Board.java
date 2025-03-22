package Controller;

import Model.*;

import java.awt.*;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Objects;

public class Board {

  //Array 2 dimensions
  private ArrayList<ArrayList<Box>> boardTable;
  private ArrayList<Ship> ships;

  public Board(){
    ships = new ArrayList<>();
  }

  //get casella(Box)
  public String getPrintBoxOfBoardTable(Board boardResolved,int x, int y) {
    if (boardResolved == null){
      return boardTable.get(y).get(x).getContentsOfBox(null);
    } else {
      return boardTable.get(y).get(x).getContentsOfBox(boardResolved.boardTable.get(y).get(x));
    }
  }

  //set un forat
  public void setBoxOfBoardTable(Box box,int x, int y) {
    boardTable.get(y).set(x, box);
  }

  //cridar a clase Ship per crear els diferents barcos
  public void putTheShipOnTheBoard(Ship ship, Point point1, Point point2) {
    if (point1.x == point2.x){//Ship esta: |

      int[] y = order(point1.y,point2.y);
      int x = point1.x;


      for (int i = y[0]; i <= y[1]; i++) {
        setBoxOfBoardTable(ship.getPart(i - y[0]), x, i);
      }
      ships.add(ship);


    } else if (point1.y == point2.y){//Ship esta: --

      int[] x = order(point1.x,point2.x);
      int y = point1.y;

      for (int i = x[0]; i <= x[1]; i++) {
        setBoxOfBoardTable(ship.getPart((i - x[0])), i, y);
      }
      ships.add(ship);

    }
  }

  public boolean iCanPutTheShipOnTheBoard(int shipSize,Point point1,Point point2){
    if (point1.x == point2.x){//Ship esta: |

      int[] y = order(point1.y,point2.y);
      int x = point1.x;

      if (   ( -1 < y[0] && y[1] < boardTable.size())
          && ( -1 <  x   &&  x   < boardTable.get(0).size())) {
        if ((y[0] + (shipSize - 1)) == y[1]) {
          for (int i = y[0]; i <= y[1]; i++) {
            if (getPrintBoxOfBoardTable(null, x, i) != BoxStates.WATER) {
              return false;
            }
          }
          return true;
        }
      }


    } else if (point1.y == point2.y){//Ship esta: --

      int[] x = order(point1.x,point2.x);
      int y = point1.y;

      if (   ( -1 < x[0] && x[1] < boardTable.size())
          && ( -1 <  y   &&  y   < boardTable.get(0).size())) {
        if ((x[0] + (shipSize - 1)) == x[1]) {
          for (int i = x[0]; i <= x[1]; i++) {
            if (getPrintBoxOfBoardTable(null, i, y) != BoxStates.WATER) {
              return false;
            }
          }
          return true;
        }
      }
    }
    return false;
  }

  private int[] order(int num1, int num2) {
    if (num1 < num2) {
      return new int[] {num1, num2};
    } else {
      return new int[] {num2, num1};
    }
  }

  //crear el array 2 dimensions (pot haver les opcions de diferentes mides)
  public void createBoardToSolve(int sizeX, int sizeY) {
    if (sizeY>0 && sizeX>0) {
      boardTable = new ArrayList<>();
      for (int i = 0; i < sizeY; i++) {
        boardTable.add(new ArrayList<>());
        for (int j = 0; j < sizeX; j++) {
          boardTable.get(i).add(new Hidden());
        }
      }
    } else {
      boardTable = null;
    }
  }
  public void createOwnBoard(int sizeX, int sizeY) {
    if (sizeY>0 && sizeX>0) {
      boardTable = new ArrayList<>();
      for (int i = 0; i < sizeY; i++) {
        boardTable.add(new ArrayList<>());
        for (int j = 0; j < sizeX; j++) {
          boardTable.get(i).add(new Water());
        }
      }
    } else {
      boardTable = null;
    }
  }
  public boolean allShipsAreDead() {
    for (Ship ship : ships) {
      if (!ship.isDead()) {
        return false;
      }
    }
    return true;
  }
  public void shoot(int x, int y){
    Box box = boardTable.get(y).get(x);
    if(box.getClass() == PartOfShip.class){
      ((PartOfShip) box).shoot();
    }
  }

  //Test
  public int[] orderRedirect(int num1, int num2) {
    return order(num1, num2);
  }
  public ArrayList<ArrayList<Box>> getBoardTable(){
    return boardTable;
  }
}
