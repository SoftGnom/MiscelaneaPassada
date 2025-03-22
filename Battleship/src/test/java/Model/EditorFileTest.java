package Model;

import org.junit.jupiter.api.Test;

import java.io.File;
import java.util.ArrayList;
import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

class EditorFileTest {

  //Per executar el test de EditorFileTest s'ha de fer una copia del ficher "ranking.txt"
  @Test
  void ifExistAndCreateFileTest() {
    EditorFile file = new EditorFile();

    //existeix
    file.deleteFile();
    assert !file.ifExist();

    //no existeix
    file.createFile();
    assert file.ifExist();

    file.deleteFile();
  }

  @Test
  void writeAndReadTest() {
    EditorFile file = new EditorFile();
    ArrayList<String> lines;
    //0 repeticions(bucle)
    file.deleteFile();
    file.createFile();
    lines = new ArrayList();
    file.write(lines);

    //el que s'ha escrit i llegit es igual
    lines = file.read();
    assert lines.isEmpty();

    //1 repeticions(bucle)
    file.deleteFile();
    file.createFile();
    lines = new ArrayList();
    file.write(lines);

    //el que s'ha escrit i llegit es igual
    lines = file.read();
    assert lines.isEmpty();

    //1 repeticions(bucle)
    file.deleteFile();
    file.createFile();
    lines = new ArrayList();
    lines.add("111");
    file.write(lines);

    //el que s'ha escrit i llegit es igual
    lines = file.read();
    assert lines.size() == 1;
    assert Objects.equals(lines.get(0), "111");

    //2 repeticions(bucle)
    file.deleteFile();
    file.createFile();
    lines = new ArrayList();
    lines.add("111111");
    lines.add("222222");
    file.write(lines);

    //el que s'ha escrit i llegit es igual
    lines = file.read();
    assert lines.size() == 2;
    assert Objects.equals(lines.get(0), "111111");
    assert Objects.equals(lines.get(1), "222222");

    //10 repeticions(bucle)
    file.deleteFile();
    file.createFile();
    lines = new ArrayList();
    lines.add("000");//0
    for (int i = 0; i<3; i++)
      lines.add("2");
    lines.add("111");//4
    for (int i = 0; i<4; i++)
      lines.add("2");
    lines.add("555");//9

    file.write(lines);

    //el que s'ha escrit i llegit es igual
    lines = file.read();
    assert lines.size() == 10;
    assert Objects.equals(lines.get(0), "000");
    assert Objects.equals(lines.get(4), "111");
    assert Objects.equals(lines.get(9), "555");


    //100 repeticions(bucle)
    file.deleteFile();
    file.createFile();
    lines = new ArrayList();
    lines.add("--");//0
    for (int i = 0; i<48; i++)
      lines.add("2");
    lines.add("***");//49
    for (int i = 0; i<49; i++)
      lines.add("2");
    lines.add("///");//99

    file.write(lines);

    //el que s'ha escrit i llegit es igual
    lines = file.read();
    assert lines.size() == 100;
    assert Objects.equals(lines.get(0), "--");
    assert Objects.equals(lines.get(49), "***");
    assert Objects.equals(lines.get(99), "///");

    file.deleteFile();

  }

}