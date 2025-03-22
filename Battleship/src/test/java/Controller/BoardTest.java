package Controller;

import Model.*;
import org.junit.jupiter.api.Test;

import java.awt.*;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

class BoardTest {

  @Test
  public void getPrintBoxOfBoardTableTest() {
    int size = 5;

    Board ownBoard = new Board();
    ownBoard.createOwnBoard(size,size);
    //Box null -> tauler propi (resolt)
    assert Objects.equals(ownBoard.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.WATER);

    Board toSolveBoard = new Board();
    toSolveBoard.createBoardToSolve(size,size);
    toSolveBoard.setBoxOfBoardTable(new Revealed(),0,0);
    //Box no null -> tauler per resoldre(en proces de resoldre)
    assert Objects.equals(toSolveBoard.getPrintBoxOfBoardTable(ownBoard, 0, 0), BoxStates.WATER);

}

  @Test
  public void setBoxOfBoardTableTest() {
    int size = 5;
    Board ownBoard = new Board();
    ownBoard.createOwnBoard(size,size);
    //avans de modificar
    assert Objects.equals(ownBoard.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.WATER);
    ownBoard.setBoxOfBoardTable(new PartOfShip(BoxStates.MIDDLE_OF_THE_SHIP),0,0);
    //despres de modificar
    assert Objects.equals(ownBoard.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.MIDDLE_OF_THE_SHIP);
  }

  @Test
  public void putTheShipOnTheBoardTest() {
    int size = 9, sizeShip, startY, startX, endX, endY;

    //Construir Board i Ship
    Ship ship = new Ship();
    Board board = new Board();
    board.createOwnBoard(size,size);

    //Ship esta: |
    ///coerent
    ////2-> x:0,y:0 -- x:0,y:1
    //set
    sizeShip = 2;
    startY = 0;
    startX = 0;
    endY = 1;//startY+(sizeShip-1);
    endX = 0;//startX
    //crear
    ship.crateShip(sizeShip);
    board.putTheShipOnTheBoard(ship,new Point(startX,startY),new Point(endX,endY));
    //test
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, endX, endY), BoxStates.END_OF_THE_SHIP);
    ////3-> x:0,y:6 -- x:0,y:8
    sizeShip = 3;
    startY = 6;
    startX = 0;
    endY = 8;//startY+(sizeShip-1);
    endX = 0;//startX
    //crear
    ship.crateShip(sizeShip);
    board.putTheShipOnTheBoard(ship,new Point(startX,startY),new Point(endX,endY));
    //test
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY+1), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, endX, endY), BoxStates.END_OF_THE_SHIP);

    ////5-> x:5,y:3 -- x:5,y:7
    sizeShip = 5;
    startY = 3;
    startX = 5;
    endY = 7;//startY+(sizeShip-1);
    endX = 5;//startX
    //crear
    ship.crateShip(sizeShip);
    board.putTheShipOnTheBoard(ship,new Point(startX,startY),new Point(endX,endY));
    //test
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY+2), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, endX, endY), BoxStates.END_OF_THE_SHIP);

    ////9-> x:8,y:0 -- x:8,y:8
    sizeShip = 9;
    startY = 0;
    startX = 8;
    endY = 8;//startY+(sizeShip-1);
    endX = 8;//startX
    //crear
    ship.crateShip(sizeShip);
    board.putTheShipOnTheBoard(ship,new Point(startX,startY),new Point(endX,endY));
    //test
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY+4), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, endX, endY), BoxStates.END_OF_THE_SHIP);




    //Ship esta: -
    ///coerent
    ////2-> x:0,y:0 -- x:1,y:0
    sizeShip = 2;
    startY = 0;
    startX = 0;
    endY = 0;//startY
    endX = 1;//startX+(sizeShip-1);
    //crear
    ship.crateShip(sizeShip);
    board.putTheShipOnTheBoard(ship,new Point(startX,startY),new Point(endX,endY));
    //test
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, endX, endY), BoxStates.END_OF_THE_SHIP);


    ////3-> x:6y:0 -- x:8,y:0
    sizeShip = 3;
    startY = 0;
    startX = 6;
    endY = 0;//startY
    endX = 8;//startX+(sizeShip-1);
    //crear
    ship.crateShip(sizeShip);
    board.putTheShipOnTheBoard(ship,new Point(startX,startY),new Point(endX,endY));
    //test
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX+1, startY), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, endX, endY), BoxStates.END_OF_THE_SHIP);


    ////5-> x:0,y:5 -- x:4,y:5
    sizeShip = 5;
    startY = 5;
    startX = 0;
    endY = 5;//startY
    endX = 4;//startX+(sizeShip-1);
    //crear
    ship.crateShip(sizeShip);
    board.putTheShipOnTheBoard(ship,new Point(startX,startY),new Point(endX,endY));
    //test
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX+2, startY), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, endX, endY), BoxStates.END_OF_THE_SHIP);


    ////9-> x:0,y:8 -- x:8,y:8
    sizeShip = 9;
    startY = 8;
    startX = 0;
    endY = 8;//startY
    endX = 8;//startX+(sizeShip-1);
    //crear
    ship.crateShip(sizeShip);
    board.putTheShipOnTheBoard(ship,new Point(startX,startY),new Point(endX,endY));
    //test
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX, startY), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, startX+4, startY), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, endX, endY), BoxStates.END_OF_THE_SHIP);


  }

  @Test
  public void iCanPutTheShipOnTheBoard() {
    int size = 9, sizeShip, startY, startX, endX, endY;

    //Construir Board i Ship
    Ship ship = new Ship();
    Board board = new Board();
    board.createOwnBoard(size,size);

    //Ship esta: |
    ///coerent
    ////2-> x:0,y:0 -- x:0,y:1
    //set
    sizeShip = 2;
    startY = 0;
    startX = 0;
    endY = 1;//startY+(sizeShip-1);
    endX = 0;//startX
    //Test
    assert board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ////3-> x:0,y:6 -- x:0,y:8
    sizeShip = 3;
    startY = 6;
    startX = 0;
    endY = 8;//startY+(sizeShip-1);
    endX = 0;//startX
    //Test
    assert board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ////5-> x:5,y:3 -- x:5,y:7
    sizeShip = 5;
    startY = 3;
    startX = 5;
    endY = 7;//startY+(sizeShip-1);
    endX = 5;//startX
    //Test
    assert board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ////9-> x:8,y:0 -- x:8,y:8
    sizeShip = 9;
    startY = 0;
    startX = 8;
    endY = 8;//startY+(sizeShip-1);
    endX = 8;//startX
    //Test
    assert board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ///no coerent
    ////comensar fora -1 - 5
    sizeShip = 5;
    startY = -1;
    startX = 5;
    endY = 3;//startY+(sizeShip-1);
    endX = 5;//startX
    //Test
    assert !board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));


    ////acabar fora   6 - 10
    sizeShip = 5;
    startY = 6;
    startX = 5;
    endY = 10;//startY+(sizeShip-1);
    endX = 5;//startX
    //Test
    assert !board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ////el punts i el ship no coincideixen
    sizeShip = 3;
    startY = 1;
    startX = 2;
    endY = 2;//startY+(sizeShip-1);
    endX = 2;//startX
    //Test
    assert !board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));






    //Ship esta: -
    ///coerent
    ////2-> x:0,y:0 -- x:1,y:0
    sizeShip = 2;
    startY = 0;
    startX = 0;
    endY = 0;//startY
    endX = 1;//startX+(sizeShip-1);
    //Test
    assert board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ////3-> x:6y:0 -- x:8,y:0
    sizeShip = 3;
    startY = 0;
    startX = 6;
    endY = 0;//startY
    endX = 8;//startX+(sizeShip-1);
    //Test
    assert board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ////5-> x:0,y:5 -- x:4,y:5
    sizeShip = 5;
    startY = 5;
    startX = 0;
    endY = 5;//startY
    endX = 4;//startX+(sizeShip-1);
    //Test
    assert board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ////9-> x:0,y:8 -- x:8,y:8
    sizeShip = 9;
    startY = 8;
    startX = 0;
    endY = 8;//startY
    endX = 8;//startX+(sizeShip-1);
    //Test
    assert board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    //no coerent
    ////comensar fora -1 - 5
    sizeShip = 5;
    startY = 5;
    startX = -1;
    endY = 5;//startY
    endX = 3;//startX+(sizeShip-1);
    //Test
    assert !board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ////acabar fora  6 - 10
    sizeShip = 5;
    startY = 5;
    startX = 6;
    endY = 5;//startY
    endX = 10;//startX+(sizeShip-1);
    //Test
    assert !board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

    ////el punts i el ship no coincideixen
    sizeShip = 3;
    startY = 2;
    startX = 1;
    endY = 2;//startY
    endX = 4;//startX+(sizeShip-1);
    //Test
    assert !board.iCanPutTheShipOnTheBoard(sizeShip,new Point(startX,startY),new Point(endX,endY));

  }

  @Test
  public void orderTest() {
    Board board = new Board();
    int[] values;

    //a<b
    values = board.orderRedirect(1, 2);
    assert values[0] < values[1];
    //a>b
    values = board.orderRedirect(2, 1);
    assert values[0] < values[1];
  }

  @Test
  public void createOwnBoardTest(){
    int x, y;
    Board board = new Board();

    //01  xy
    y = 0;
    x = 1;
    board.createOwnBoard(x,y);
    assert board.getBoardTable() == null;

    //10
    y = 1;
    x = 0;
    board.createOwnBoard(x,y);
    assert board.getBoardTable() == null;

    //11
    y = 1;
    x = 1;
    board.createOwnBoard(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.WATER);

    //12
    y = 1;
    x = 2;
    board.createOwnBoard(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 1, 0), BoxStates.WATER);

    //25
    y = 2;
    x = 5;
    board.createOwnBoard(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 1, 0), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 3, 1), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 4, 1), BoxStates.WATER);


    //59
    y = 5;
    x = 9;
    board.createOwnBoard(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 1, 1), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 7, 3), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 8, 4), BoxStates.WATER);

    //59
    y = 9;
    x = 5;
    board.createOwnBoard(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 1, 1), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 3, 7), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 4, 8), BoxStates.WATER);
  }

  @Test
  public void createBoardToSolveTese(){
    int x, y;
    Board board = new Board();

    //01  xy
    y = 0;
    x = 1;
    board.createBoardToSolve(x,y);
    assert board.getBoardTable() == null;

    //10
    y = 1;
    x = 0;
    board.createBoardToSolve(x,y);
    assert board.getBoardTable() == null;

    //11
    y = 1;
    x = 1;
    board.createBoardToSolve(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.HIDDEN);

    //12
    y = 1;
    x = 2;
    board.createBoardToSolve(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 1, 0), BoxStates.HIDDEN);

    //25
    y = 2;
    x = 5;
    board.createBoardToSolve(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 1, 0), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 3, 1), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 4, 1), BoxStates.HIDDEN);


    //59
    y = 5;
    x = 9;
    board.createBoardToSolve(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 1, 1), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 7, 3), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 8, 4), BoxStates.HIDDEN);

    //59
    y = 9;
    x = 5;
    board.createBoardToSolve(x,y);
    assert board.getBoardTable().size() == y;
    assert board.getBoardTable().get(0).size() == x;
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 1, 1), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 3, 7), BoxStates.HIDDEN);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 4, 8), BoxStates.HIDDEN);


  }

  @Test
  public void shootAndallShipsAreDeadTest(){
    Board board = new Board();
    board.createOwnBoard(9,9);
    Ship ship = new Ship();
    //1 ship
    ship.crateShip(3);
    board.putTheShipOnTheBoard(ship,new Point(1,3), new Point(3,3));
    board.shoot(1,3);
    board.shoot(2,3);
    board.shoot(3,3);
    assert board.allShipsAreDead();

    //2 ship
    ship.crateShip(3);
    board.putTheShipOnTheBoard(ship,new Point(1,5), new Point(3,5));
    //no all
    assert !board.allShipsAreDead();
    board.shoot(1,5);
    board.shoot(2,5);
    board.shoot(3,5);
    //all
    assert board.allShipsAreDead();
  }

  @Test
  public void testGeneralBoard(){

    Board board = new Board();


    //Construir Board i Ship
    Ship ship = new Ship();
    Ship ship1 = new Ship();
    int size = 5;
    board.createOwnBoard(size,size);
    //Ship 1 (-)-> x:1,y:1 -- x:3,y:1
    int sizeShip1 = 3;
    int Y1 = 1, startX1=1, endX1=startX1+(sizeShip1-1);
    ship.crateShip(endX1-startX1+1);
    board.putTheShipOnTheBoard(ship,new Point(startX1,Y1),new Point(endX1,Y1));
    //Ship 2 (|)-> x:1,y:2 -- x:1,y:4
    int sizeShip2 = 3;
    int X2 = 1, startY2=2, endY2=startY2+(sizeShip2-1);
    ship1.crateShip(endY2-startY2+1);
    board.putTheShipOnTheBoard(ship1,new Point(X2,startY2),new Point(X2,endY2));


    //test tauler complet amb les solucions
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 0, 0), BoxStates.WATER);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 2, 1), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(board.getPrintBoxOfBoardTable(null, 1, 1), BoxStates.END_OF_THE_SHIP);


    //Fer el mateix amb un board amb Hidden/Reveled(tauler parcialment complet amb les solucions)

    //Construir Board i Ship
    Board boardToSolve = new Board();
    boardToSolve.createBoardToSolve(size,size);
    //Visible Ship 1 (-)-> x:1,y:1 -- x:3,y:1
    for (int i = startX1; i <= endX1; i++){
      Revealed aux = new Revealed();
      boardToSolve.setBoxOfBoardTable(aux,i,Y1);
    }
    Revealed aux = new Revealed();
    boardToSolve.setBoxOfBoardTable(aux,0,0);
    //Ocult (No s'ha de fer ress) -> Ship 2 (|)-> x:1,y:2 -- x:1,y:4


    //Ship 1
    assert Objects.equals(boardToSolve.getPrintBoxOfBoardTable(board, 0, 0), BoxStates.WATER);
    assert Objects.equals(boardToSolve.getPrintBoxOfBoardTable(board, 1, 1), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(boardToSolve.getPrintBoxOfBoardTable(board, 2, 1), BoxStates.MIDDLE_OF_THE_SHIP);
    assert Objects.equals(boardToSolve.getPrintBoxOfBoardTable(board, 3, 1), BoxStates.END_OF_THE_SHIP);
    //Ship 2
    assert Objects.equals(boardToSolve.getPrintBoxOfBoardTable(board, 1, 2), BoxStates.HIDDEN);
    assert Objects.equals(boardToSolve.getPrintBoxOfBoardTable(board, 1, 3), BoxStates.HIDDEN);
    assert Objects.equals(boardToSolve.getPrintBoxOfBoardTable(board, 1, 4), BoxStates.HIDDEN);

  }
}
