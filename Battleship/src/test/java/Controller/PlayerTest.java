package Controller;

import Model.BoxStates;
import Model.Hidden;
import Model.Water;
import org.junit.jupiter.api.Test;

import java.awt.*;
import java.util.ArrayList;
import java.util.Objects;

class PlayerTest {

  @Test
  void Player(){
    //set name
    Player player = new Player("jugador",1,1);
    assert Objects.equals(player.getName(), "jugador");

    //set OwnBoard
    Board board = player.getOwnBoard();
    assert board.getBoardTable().size() == 1;
    assert board.getBoardTable().get(0).size() == 1;
    assert (board.getBoardTable().get(0).get(0)).getClass() == Water.class;

    //set ToSolveBoard
    board = player.getToSolveBoard();
    assert board.getBoardTable().size() == 1;
    assert board.getBoardTable().get(0).size() == 1;
    assert board.getBoardTable().get(0).get(0).getClass() == Hidden.class;
  }
  @Test
  void getToSolveReveledAndGetOwnBoard() {
    Player players;
    ArrayList<ArrayList<String>>  board;

    //bucle
    //yx
    //11
    players  = new Player("a",1,1);
    board = players.getToSolveReveled(players.getOwnBoard());

    assert board.size() == 1;
    assert board.get(0).size() == 1;

    //12
    players  = new Player("a",2,1);
    board = players.getToSolveReveled(players.getOwnBoard());

    assert board.size() == 1;
    assert board.get(0).size() == 2;

    //25
    players  = new Player("a",5,2);
    board = players.getToSolveReveled(players.getOwnBoard());

    assert board.size() == 2;
    assert board.get(0).size() == 5;

    //58
    players  = new Player("a",8,5);
    board = players.getToSolveReveled(players.getOwnBoard());

    assert board.size() == 5;
    assert board.get(0).size() == 8;

    //85
    players  = new Player("a",5,8);
    board = players.getToSolveReveled(players.getOwnBoard());

    assert board.size() == 8;
    assert board.get(0).size() == 5;

  }

  @Test
  void getARealPrintOfABoxOfBoardToSolveTest_And_RevealedABoxOfBoardToSolveTest() {
    Player players  = new Player("a",2,2);

    players.revealedABoxOfBoardToSolve(0,0);
    players.revealedABoxOfBoardToSolve(1,0);

    ArrayList<ArrayList<String>>  board = players.getToSolveReveled(players.getOwnBoard());

    //amb redirecionament
    assert Objects.equals(players.getARealPrintOfABoxOfBoardToSolve(players.getOwnBoard(),0,0), BoxStates.WATER);
    //sense redirecionament
    assert Objects.equals(players.getARealPrintOfABoxOfBoardToSolve(players.getOwnBoard(),0,1), BoxStates.HIDDEN);

  }

  @Test
  void getName() {
    Player player = new Player("name",0,0);
    assert Objects.equals(player.getName(), "name");
  }

  @Test
  void addShip() {
    Player player = new Player("name",5,5);
    //puc posar baixell
    assert Objects.equals(player.getOwnBoard().getPrintBoxOfBoardTable(null, 2, 2), BoxStates.WATER);
    assert Objects.equals(player.getOwnBoard().getPrintBoxOfBoardTable(null, 2, 2), BoxStates.WATER);

    assert player.addShip(2,new Point(2,2),new Point(2,3));

    assert Objects.equals(player.getOwnBoard().getPrintBoxOfBoardTable(null, 2, 2), BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(player.getOwnBoard().getPrintBoxOfBoardTable(null, 2, 2), BoxStates.END_OF_THE_SHIP);

    //no puc posar baixell
    assert !player.addShip(2,new Point(0,0),new Point(0,0));
    assert !player.addShip(1,new Point(0,0),new Point(0,0));
    assert !player.addShip(11,new Point(0,0),new Point(10,0));

  }
}