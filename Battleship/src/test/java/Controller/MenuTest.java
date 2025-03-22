package Controller;

import Model.OptionsMenu;
import View.MockView;
import org.junit.jupiter.api.Test;

class MenuTest {

  @Test
  void menu() {
    //crear menu amb mock
    Menu menu = new Menu();

    MockGame game = new MockGame();
    menu.setGame(game);

    MockRanking ranking = new MockRanking();
    menu.setRanking(ranking);

    MockView view = new MockView();
    menu.setView(view);

    //selecionar -> OptionsMenu.GAME
    //preparar
    game.setBoolPlay(false);
    ranking.setBoolRanking(false);
    view.setViewInt(OptionsMenu.GAME);
    view.setRepetitionCounter(1);
    menu.menu();
    //s'han cridat les funcions correctes
    assert game.getBoolPlay();
    assert ranking.getBoolRanking();


    //selecionar -> OptionsMenu.RANKING
    //preparar
    view.setBoolView(true);
    view.setViewInt(OptionsMenu.RANKING);
    view.setRepetitionCounter(1);
    menu.menu();
    //s'han cridat les funcions correctes
    assert view.getBoolView();//1 repeticio del visualitzar el RANKING i 2 per el exit

    //selecionar -> OptionsMenu.EXIT
    //preparar
    view.setBoolView(false);
    view.setViewInt(OptionsMenu.EXIT);
    view.setRepetitionCounter(1);
    menu.menu();
    //s'han cridat les funcions correctes
    assert view.getBoolView();//1 per el exit

    //selecionar -> Altres
    //preparar
    view.setBoolView(true);
    view.setViewInt(-1);
    view.setRepetitionCounter(1);
    menu.menu();
    //s'han cridat les funcions correctes
    assert view.getBoolView();//1 repeticio del visualitzar el Altres i 2 per el exit



  }

}