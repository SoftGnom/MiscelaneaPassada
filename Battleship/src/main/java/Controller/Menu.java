package Controller;

import Model.OptionsMenu;
import View.View;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;

public class Menu {

  private ArrayList<String> options;
  private View view;
  private Ranking ranking;
  private Game game;


  public Menu(){
    options = new ArrayList<>();
    options.add("Play game!");    //opcio 1
    options.add("View ranking");  //opcio 2
    options.add("Exit");          //opcio 3

    view = new View();

    ranking = new Ranking();

    game = new Game();
  }

  public void menu() {
    int choice;

    do {
      //Mostrem les opcions disponibles i obtenim l'opció
      choice = view.menu(options, options.size());

      //Realitzem accions segons l'elecció de l'usuari
      switch (choice) {//es pot cambiar per el visitor
        case OptionsMenu.GAME:
          ArrayList<String> players;
          players = game.play();
          ranking.saveData(players.get(0), players.get(1));
          break;
        case OptionsMenu.RANKING:
          view.showRanking(ranking.getData());
          break;
        case OptionsMenu.EXIT:
          view.viewMisathe("Goodbye!","Menu");
          break;
        default:
          view.viewMisathe("Invalid choice. Please try again.","Menu");
      }
    }while (choice != 3);
  }

  //Test
  public void setGame(Game games){
    game = games;
  }
  public void setView(View views){
    view = views;
  }

  public void setRanking(Ranking rankings){
    ranking = rankings;
  }
}
