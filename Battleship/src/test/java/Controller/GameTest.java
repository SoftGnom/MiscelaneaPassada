package Controller;

import Model.*;
import View.View;
import org.junit.jupiter.api.Test;
import View.View;
import View.MockView;
import org.junit.jupiter.api.Assertions.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

class GameTest {
  @Test
  public void playerChangeTest() {
    Game game = new Game();
    assertEquals(1, game.playerChangeTest(0));
    assertEquals(0, game.playerChangeTest(1));
  }

  @Test
  public void isBoxIsHiddenTest(){
    Game game = new Game();
    Player currentPlayer = new Player("Player1", 5, 5);
    Player opponentPlayer = new Player("Player2", 5, 5);

    //Test per a una hidden box
    assertTrue(game.isBoxIsHiddenTest(new ArrayList<>(List.of(1, 1)), currentPlayer, opponentPlayer));

    //Test per a una revealed box
    currentPlayer.revealedABoxOfBoardToSolve(1, 1);
    assertFalse(game.isBoxIsHiddenTest(new ArrayList<>(List.of(1, 1)), currentPlayer, opponentPlayer));
  }

  @Test
  public void createPlayersTest(){
    //preparar clases
    MockView view = new MockView();
    Game game = new Game();
    game.setView(view);
    //preparar valors
    int sizeBoard = 6;
    game.setSizeX(sizeBoard);
    game.setSizeY(sizeBoard);
    //preparar view
    ///noms dels jugadors
    ArrayList<String> names = new ArrayList<>();
    names.add("j1");
    names.add("j1");
    ///dades baixells
    ArrayList<Integer> dades1 = new ArrayList<>();
    dades1.add(2);//mida
    dades1.add(0);//Punt 1, x
    dades1.add(0);//Punt 1, y
    dades1.add(0);//Punt 2, x
    dades1.add(1);//Punt 2, y
    ArrayList<Integer> dades2 = new ArrayList<>();
    dades2.add(2);//mida
    dades2.add(0);//Punt 1, x
    dades2.add(2);//Punt 1, y
    dades2.add(0);//Punt 2, x
    dades2.add(3);//Punt 2, y
    ArrayList<Integer> dades3 = new ArrayList<>();
    dades3.add(2);//mida
    dades3.add(0);//Punt 1, x
    dades3.add(4);//Punt 1, y
    dades3.add(0);//Punt 2, x
    dades3.add(5);//Punt 2, y
    ArrayList<ArrayList<Integer>> dades = new ArrayList<>();
    dades.add(dades3);
    dades.add(dades2);
    dades.add(dades1);



    //1 baixell
    game.setNumberOfShips(1);
    ///carregar tot a View
    view.setAskForPlayersNames(names);//ArrayList<String> names
    view.setGetDataOfShip(dades,0);//ArrayList<ArrayList<Integer>> dades, int maxRepetition

    //execusio de la
    game.createPlayersTest();

    //comprovacio
    ///get Boards
    ArrayList<Board> boards = game.getOwnBoard();
    //comprobar el baixell
    assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, 4)
        , boards.get(1).getPrintBoxOfBoardTable(null, 0, 4));
    assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, 5)
        , boards.get(1).getPrintBoxOfBoardTable(null, 0, 5));

    assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, 4)
        , BoxStates.END_OF_THE_SHIP);
    assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, 5)
        , BoxStates.END_OF_THE_SHIP);




    //2 baixell
    game.setNumberOfShips(2);
    ///carregar tot a View
    view.setAskForPlayersNames(names);//ArrayList<String> names
    view.setGetDataOfShip(dades,1);//ArrayList<ArrayList<Integer>> dades, int maxRepetition

    //execusio de la
    game.createPlayersTest();

    //comprovacio
    ///get Boards
    boards = game.getOwnBoard();
    //comprobar el baixell

    for (int i = 2; i < sizeBoard; i++){
      assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, i)
          , boards.get(1).getPrintBoxOfBoardTable(null, 0, i));
    }
    for (int i = 2; i < sizeBoard; i++){
      assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, i)
          , BoxStates.END_OF_THE_SHIP);
    }




    //3 baixells
    game.setNumberOfShips(3);
    ///carregar tot a View
    view.setAskForPlayersNames(names);//ArrayList<String> names
    view.setGetDataOfShip(dades,2);//ArrayList<ArrayList<Integer>> dades, int maxRepetition

    //execusio de la
    game.createPlayersTest();

    //comprovacio
    ///get Boards
    boards = game.getOwnBoard();
    //comprobar la primera llinea
    for (int i = 0; i < sizeBoard; i++){
      assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, i)
          , boards.get(1).getPrintBoxOfBoardTable(null, 0, i));
    }
    for (int i = 0; i < sizeBoard; i++){
      assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, i)
          , BoxStates.END_OF_THE_SHIP);
    }


    //3 baixells + 1 malament
    game.setNumberOfShips(3);
    ///dades 1 baixell
    ArrayList<Integer> dades4 = new ArrayList<>();
    dades4.add(3);//mida
    dades4.add(0);//Punt 1, x
    dades4.add(4);//Punt 1, y
    dades4.add(0);//Punt 2, x
    dades4.add(5);//Punt 2, y
    dades.add(0,dades4);
    ///carregar tot a View
    view.setAskForPlayersNames(names);//ArrayList<String> names
    view.setGetDataOfShip(dades,3);//ArrayList<ArrayList<Integer>> dades, int maxRepetition

    //execusio de la
    game.createPlayersTest();

    //comprovacio
    ///get Boards
    boards = game.getOwnBoard();
    //comprobar la primera llinea
    for (int i = 0; i < sizeBoard; i++){
      assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, i)
          , boards.get(1).getPrintBoxOfBoardTable(null, 0, i));
    }
    for (int i = 0; i < sizeBoard; i++){
      assert Objects.equals(boards.get(0).getPrintBoxOfBoardTable(null, 0, i)
          , BoxStates.END_OF_THE_SHIP);
    }
  }

  @Test
  public void playerTurnTest() {
    //preparar clases
    MockView view = new MockView();
    Game game = new Game();
    game.setView(view);
    //preparar valors
    int sizeBoard = 6;
    game.setSizeX(sizeBoard);
    game.setSizeY(sizeBoard);
    //preparar view
    ///noms dels jugadors
    ArrayList<String> names = new ArrayList<>();
    names.add("j1");
    names.add("j1");
    ///dades baixells
    ArrayList<Integer> dades1 = new ArrayList<>();
    dades1.add(2);//mida
    dades1.add(0);//Punt 1, x
    dades1.add(0);//Punt 1, y
    dades1.add(0);//Punt 2, x
    dades1.add(1);//Punt 2, y
    ArrayList<Integer> dades2 = new ArrayList<>();
    dades2.add(2);//mida
    dades2.add(0);//Punt 1, x
    dades2.add(2);//Punt 1, y
    dades2.add(0);//Punt 2, x
    dades2.add(3);//Punt 2, y
    ArrayList<Integer> dades3 = new ArrayList<>();
    dades3.add(2);//mida
    dades3.add(0);//Punt 1, x
    dades3.add(4);//Punt 1, y
    dades3.add(0);//Punt 2, x
    dades3.add(5);//Punt 2, y
    ArrayList<ArrayList<Integer>> dades = new ArrayList<>();
    dades.add(dades3);
    dades.add(dades2);
    dades.add(dades1);
    //3 baixells
    game.setNumberOfShips(3);
    ///carregar tot a View
    view.setAskForPlayersNames(names);//ArrayList<String> names
    view.setGetDataOfShip(dades,2);//ArrayList<ArrayList<Integer>> dades, int maxRepetition
    //creacio clase Player
    game.createPlayersTest();


    //preparar Test torn
    ///crear estructures
    ArrayList<Player> players = game.getPlayers();
    ArrayList<Integer> axis = new ArrayList<>();
    dades = new ArrayList<>();
    for (int i = 0; i < sizeBoard; i++){//tota la linea
      axis = new ArrayList<>();
      axis.add(0);//x
      axis.add(i);//y
      dades.add(axis);
    }
    //carregar tot a view
    view.setChooseTheBox(dades,sizeBoard-1);

    //execusio torn (test)
    for (int i = sizeBoard-1; i >=0 ; i-=2) {
      assert !game.getPlayers().get(1).lose();
      //comprobar estat inicial
      assert Objects.equals(game.getPlayers().get(0).getToSolveBoard().getBoardTable().get(i).get(0).getClass()
          , Hidden.class);
      assert !((PartOfShip) game.getPlayers().get(1).getOwnBoard().getBoardTable().get(i).get(0)).isHit();
      //execusio
      game.playerTurnTest(players.get(0), players.get(1));
      game.playerTurnTest(players.get(0), players.get(1));
      //actuaalitzacio
      assert Objects.equals(game.getPlayers().get(0).getToSolveBoard().getBoardTable().get(i).get(0).getClass()
          , Revealed.class);
      assert  ((PartOfShip) game.getPlayers().get(1).getOwnBoard().getBoardTable().get(i).get(0)).isHit();
    }
    assert game.getPlayers().get(1).lose();


    //preparar Test torn per errors al introduir dades
    ///crear estructures
    players = game.getPlayers();
    players.get(0).getToSolveBoard().createBoardToSolve(sizeBoard,sizeBoard);
    axis = new ArrayList<>();
    dades = new ArrayList<>();
    for (int i = 0; i < sizeBoard; i++){//tota la linea
      axis = new ArrayList<>();
      axis.add(0);//x
      axis.add(i);//y
      dades.add(axis);
      axis = new ArrayList<>();
      axis.add(0);//x
      axis.add(i);//y
      dades.add(axis);
    }
    //carregar tot a view
    view.setChooseTheBox(dades,(sizeBoard*2)-1);

    //execusio torn (test)
    for (int i = sizeBoard-1; i >=0 ; i-=2) {
      //comprobar estat inicial
      assert Objects.equals(game.getPlayers().get(0).getToSolveBoard().getBoardTable().get(i).get(0).getClass()
          , Hidden.class);
      //execusio
      game.playerTurnTest(players.get(0), players.get(1));
      game.playerTurnTest(players.get(0), players.get(1));
      //actuaalitzacio
      assert Objects.equals(game.getPlayers().get(0).getToSolveBoard().getBoardTable().get(i).get(0).getClass()
          , Revealed.class);
    }

  }

  @Test
  public void playTest() {

    //preparar clases (general)
    MockView view = new MockView();
    Game game = new Game();
    game.setView(view);
    //preparar dades (View)
    int sizeBoard = 6;
    ArrayList<Integer> size = new ArrayList<>();
    size.add(sizeBoard);//y
    size.add(sizeBoard);//x
    int numberOfShips = 3;
    //cargar dades en view
    view.setAskForSizeOfBoard(size);
    view.setAskForNumberOfShips(numberOfShips);

    //preparar valors (createPlayer)
    game.setSizeX(sizeBoard);
    game.setSizeY(sizeBoard);
    //preparar view
    ///noms dels jugadors
    ArrayList<String> names = new ArrayList<>();
    names.add("j1");
    names.add("j2");
    ///dades baixells
    ArrayList<Integer> dades1 = new ArrayList<>();
    dades1.add(2);//mida
    dades1.add(0);//Punt 1, x
    dades1.add(0);//Punt 1, y
    dades1.add(0);//Punt 2, x
    dades1.add(1);//Punt 2, y
    ArrayList<Integer> dades2 = new ArrayList<>();
    dades2.add(2);//mida
    dades2.add(0);//Punt 1, x
    dades2.add(2);//Punt 1, y
    dades2.add(0);//Punt 2, x
    dades2.add(3);//Punt 2, y
    ArrayList<Integer> dades3 = new ArrayList<>();
    dades3.add(2);//mida
    dades3.add(0);//Punt 1, x
    dades3.add(4);//Punt 1, y
    dades3.add(0);//Punt 2, x
    dades3.add(5);//Punt 2, y
    ArrayList<ArrayList<Integer>> dades = new ArrayList<>();
    dades.add(dades3);
    dades.add(dades2);
    dades.add(dades1);
    //3 baixells
    game.setNumberOfShips(3);
    ///carregar tot a View
    view.setAskForPlayersNames(names);
    view.setGetDataOfShip(dades,2);

    //preparar Test (torn)
    ///crear estructures
    ArrayList<Player> players = game.getPlayers();
    ArrayList<Integer> axis = new ArrayList<>();
    ArrayList<ArrayList<Integer>> dades11 = new ArrayList<>();
    for (int i = 0; i < sizeBoard; i++){//tota la linea
      axis = new ArrayList<>();
      axis.add(0);//x
      axis.add(i);//y
      dades11.add(axis);
      axis = new ArrayList<>();
      axis.add(1);//x
      axis.add(i);//y
      dades11.add(axis);
    }
    //carregar tot a view
    view.setChooseTheBox(dades11,(sizeBoard*2)-1);


    //Test play
    ArrayList<String> playesEnd = game.play();
    assert Objects.equals(playesEnd.get(1), names.get(0));
    assert Objects.equals(playesEnd.get(0), names.get(1));
  }

}