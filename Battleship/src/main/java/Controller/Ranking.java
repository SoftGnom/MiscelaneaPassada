package Controller;
import Model.EditorFile;

import java.sql.Array;
import java.util.ArrayList;

public class Ranking {

  private EditorFile file;
  public Ranking(){
    file = new EditorFile();
  }
  public ArrayList<String> getData(){
    ArrayList<String> data = new ArrayList<>();
    if (file.ifExist()){
      return file.read();
    } else{
      data.add("");
      return data;
    }
  }

  public void saveData(String winner, String loser){ //guardar en el document
    ArrayList<String> entry = new ArrayList<>();
    entry.add("Winner: " + winner);
    entry.add("\t\tLoser: " + loser);
    entry.add("--");
    if (file.ifExist()){
      ArrayList<String> readed = file.read();
      int i = 0;
      int fiWhile = 1;//1-> buscar el Winner
      while(i < readed.size() && fiWhile != 0){
        if ( compareStrings(readed.get(i), entry.get(0))) {
          fiWhile = 2;//2-> comensar a buscar la posicio
        } else if (compareStrings(readed.get(i), entry.get(2)) && fiWhile==2) {
          fiWhile = 0;
        }
        i++;
      }
      if (fiWhile==0){
        readed.add((i-1), entry.get(1));
      } else {
        readed.add((i++), entry.get(0));
        readed.add((i++), entry.get(1));
        readed.add((i), entry.get(2));
      }

      file.write(readed);
    } else{
      file.createFile();
      file.write(entry);
    }

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

  //Test
  public void setEditorFile(EditorFile editorFile){
    file = editorFile;
  }
  public boolean compareStringsRedirect(String str1, String str2) {
    return compareStrings(str1, str2);
  }
  public void deleteFile(){
    file.deleteFile();
  }

}
