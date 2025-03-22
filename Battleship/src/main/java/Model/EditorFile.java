package Model;
import java.io.File;
import java.util.ArrayList;
import java.io.*;

public class EditorFile {//hauria de ser un Singelton
  private final String nomFitxer = "ranking.txt";
  private final File fitxer;
  public EditorFile() {
    fitxer = new File(nomFitxer);
  }
  public boolean ifExist() {// 1 -> existeix
    if (fitxer.exists())
      if (!fitxer.isDirectory())
        return true;
    return false;
  }
  public boolean write(ArrayList<String> linesNewContent) {
    try (BufferedWriter writer = new BufferedWriter(new FileWriter(fitxer))) {
      for (String line : linesNewContent) {
        writer.write(line);
        writer.newLine();
      }
      return true;
    } catch (IOException e) {
      return false;
    }
  }
  public ArrayList<String> read() {
    ArrayList<String> contingut = new ArrayList<>();
    try (BufferedReader reader = new BufferedReader(new FileReader(fitxer))) {
      String line;
      while ((line = reader.readLine()) != null) {
        contingut.add(line);
      }
    } catch (IOException e) {
      contingut.add("-1");
    }
    return contingut;
  }
  public boolean createFile() {
    try {
      if (fitxer.createNewFile()) {
        return true;
      } else {
        return false;
      }
    } catch (IOException e) {
      return false;
    }
  }
  //Test
  public boolean deleteFile() {
    if (fitxer.exists()) {
      return fitxer.delete();
    }
    return false;
  }
}
