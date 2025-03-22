package View;
import java.util.Objects;
import java.util.Scanner;

import Model.Box;
import Model.Hidden;

import java.util.ArrayList;

public class View {

  private Scanner scanner;

  public View() {
    scanner = new Scanner(System.in);
  }

  private void header(String name) {
    System.out.println("-----------------------  " + name + "  -----------------------\n");

  }
  //Poder aquest es més senzill de provar que l'altre
  private void printBoard(ArrayList<ArrayList<String>> board) {
    int y=0;
    System.out.print(" X ");
    for (int i = 1; i <= board.get(0).size(); i++){
      System.out.print(i);
    }
    System.out.println(" X");
    System.out.print("Y ");
    for (int i = -2; i < board.get(0).size(); i++){
      System.out.print("*");
    }
    System.out.println();
    for (ArrayList<String> row : board) {
      y++;
      System.out.print(y + " *");
      for (String cell : row) {
        System.out.print(cell);
      }
      System.out.println("*");
    }
    System.out.print("Y ");
    for (int i = -2; i < board.get(0).size(); i++){
      System.out.print("*");
    }
    System.out.println("\n");
  }

  public ArrayList<Integer> chooseTheBox(ArrayList<ArrayList<String>> board, String name) {
    header(name);
    printBoard(board);

    System.out.println();

    ArrayList<Integer> axis = new ArrayList<>();
    System.out.print("On the X-axis.");
    axis.add((getUserChoice(board.size())-1));
    System.out.print("On the Y-axis.");
    axis.add((getUserChoice(board.get(0).size())-1));
    return axis;
  }

  public void showTheBoard(ArrayList<ArrayList<String>> board, String name) {
    header(name);
    printBoard(board);
  }
  public ArrayList<String> askForPlayersNames(){
    ArrayList<String> names = new ArrayList<>();
    names.add("");
    names.add("");
    do {
      header("Players Names");
      System.out.print("Introduir el nom del jugador 1:");
      names.set(0, scanner.nextLine());
      System.out.print("Introduir el nom del jugador 2:");
      names.set(1, scanner.nextLine());
    } while ((compareStrings(names.get(0), names.get(1)) ));
    return names;
  }

  private boolean compareStrings(String str1, String str2) {
    if (str1.length() != str2.length()){
      return false;
    }
    int i = 0;
    while (i < str1.length()) {
      if (str1.charAt(i) != str2.charAt(i)) {
        return false;
      }
      i++;
    }
    return true;
  }
  public ArrayList<Integer> askForSizeOfBoard(){
    ArrayList<Integer> size = new ArrayList<>();
    header("Board size");
    System.out.print("Introduir el size de the Y-axis.");
    size.add(getUserChoice(9));
    System.out.print("Introduir el size de the X-axis.");
    size.add(getUserChoice(9));
    return size;
  }


  public int askForNumberOfShips(){
    ArrayList<Integer> size = new ArrayList<>();
    header("Number Of Ships");
    System.out.print("Introduir el numero de Ships.");
    return getUserChoice(9);
  }

  public int menu(ArrayList<String> options, int maxOption){
    header("Battleship");
    Scanner scanner = new Scanner(System.in);
    for (int i = 0; i < options.size(); i++) {
      System.out.println("\t" + (i+1) + " - " + options.get(i));
    }
    return getUserChoice(maxOption);
  }

  public void showRanking(ArrayList<String> ranking) { //
    header("Ranking");
    System.out.println("Ranking:");
    for (String entry : ranking) {
      System.out.println(entry);
    }
    System.out.println("\n\t\tEnter per continuar.");
    scanner.nextLine();
  }

  private int getUserChoice(int maxOption) {
    int choice = -1;

    while (choice < 1 || choice > maxOption) {
      System.out.print("Enter your choice (1-" + maxOption + "): ");

      // Manejar excepcions si l'usuari ingressa una dada que no és un número
      try {
        choice = scanner.nextInt();
        scanner.nextLine();
      } catch (Exception e) {
        System.out.println("Invalid input. Please enter a number.");
        scanner.next(); // Netejar el buffer del scanner
      }

      if (choice < 1 || choice > maxOption) {
        System.out.println("Invalid choice. Please enter a number between 1 and " + maxOption + ".");
      }
    }

    return choice;
  }

  private int getUserChoice(int minOption,int maxOption) {
    int choice = minOption-1;

    while (choice < minOption || choice > maxOption) {
      System.out.print("Enter your choice (" + minOption + "-" + maxOption + "): ");

      // Manejar excepcions si l'usuari ingressa una dada que no és un número
      try {
        choice = scanner.nextInt();
        scanner.nextLine();
      } catch (Exception e) {
        System.out.println("Invalid input. Please enter a number.");
        scanner.next(); // Netejar el buffer del scanner
      }

      if (choice < 1 || choice > maxOption) {
        System.out.println("Invalid choice. Please enter a number between " + minOption + " and " + maxOption + ".");
      }
    }

    return choice;
  }

  public void viewMisathe(String misathe,String name){
    header(name);
    System.out.println("\n\t\t" + misathe);

    System.out.println("\n\t\tEnter per continuar.");
    scanner.nextLine();
  }

  public ArrayList<Integer> getDataOfShip(String name){
    header(name);
    ArrayList<Integer> data = new ArrayList<>();
    System.out.print("Introduir el size del ship.");
    data.add(getUserChoice(2,9));
    System.out.print("Introduir el punt 1 de Y-axis.");
    data.add(getUserChoice(9)-1);
    System.out.print("Introduir el punt 1 de X-axis.");
    data.add(getUserChoice(9)-1);
    System.out.print("Introduir el punt 2 de Y-axis.");
    data.add(getUserChoice(9)-1);
    System.out.print("Introduir el punt 2 de X-axis.");
    data.add(getUserChoice(9)-1);
    return data;
  }

}
