package Controller;

import Model.MockEditorFile;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Objects;

import static org.junit.jupiter.api.Assertions.*;

class RankingTest {

  @Test
  void getData() {
    Ranking ranking = new Ranking();
    MockEditorFile editorFile = new MockEditorFile();
    ranking.setEditorFile(editorFile);
    //existeix el fitcher
    editorFile.setBool(true);
    ArrayList<String> lines = new ArrayList<>();
    lines.add("linea_1");
    lines.add("linea_2");
    lines.add("linea_3");
    editorFile.setRead(lines);

    ArrayList<String> linesOut = new ArrayList<>();
    linesOut = ranking.getData();
    assert linesOut.size() == 3;
    assert Objects.equals(linesOut.get(0), "linea_1");
    assert Objects.equals(linesOut.get(1), "linea_2");
    assert Objects.equals(linesOut.get(2), "linea_3");

    //no existeix el fitcher
    editorFile.setBool(false);
    editorFile.setRead(new ArrayList<>());

    lines = new ArrayList<>();
    lines = ranking.getData();
    assert lines.size() == 1;
    assert Objects.equals(lines.get(0), "");

  }

  @Test
  void saveData() {
    Ranking ranking = new Ranking();
    MockEditorFile editorFile = new MockEditorFile();
    ranking.setEditorFile(editorFile);
    ArrayList<String> lines;
    ArrayList<String> linesOut;

    //existeix el fitcher
    ///existeix Winer
    ////primera pocico

    //set Mock
    editorFile.setBool(true);
    lines = new ArrayList<>();
    lines.add("Winner: p1");
    lines.add("\t\tLoser: px");
    lines.add("--");
    editorFile.setRead(lines);

    //executar saveData
    ranking.saveData("p1","p2");
    linesOut = new ArrayList<>();

    //getOutput
    linesOut = editorFile.getWrite();

    //comprobacio
    assert linesOut.size() == 4;
    assert Objects.equals(linesOut.get(0), "Winner: p1");
    assert Objects.equals(linesOut.get(1), "\t\tLoser: px");
    assert Objects.equals(linesOut.get(2), "\t\tLoser: p2");
    assert Objects.equals(linesOut.get(3), "--");

    ////segona pocico (sanwich)

    //set Mock
    editorFile.setBool(true);
    lines = new ArrayList<>();
    lines.add("Winner: pw1");
    lines.add("\t\tLoser: p1");
    lines.add("--");
    lines.add("Winner: pw2");
    lines.add("\t\tLoser: p21");
    lines.add("\t\tLoser: p22");
    lines.add("--");
    lines.add("Winner: pw3");
    lines.add("\t\tLoser: p3");
    lines.add("--");
    editorFile.setRead(lines);

    //executar saveData
    ranking.saveData("pw2","px");
    linesOut = new ArrayList<>();

    //getOutput
    linesOut = editorFile.getWrite();

    //comprobacio
    assert linesOut.size() == 11;
    assert Objects.equals(linesOut.get(0), "Winner: pw1");
    assert Objects.equals(linesOut.get(1), "\t\tLoser: p1");
    assert Objects.equals(linesOut.get(2), "--");
    assert Objects.equals(linesOut.get(3), "Winner: pw2");
    assert Objects.equals(linesOut.get(4), "\t\tLoser: p21");
    assert Objects.equals(linesOut.get(5), "\t\tLoser: p22");
    assert Objects.equals(linesOut.get(6), "\t\tLoser: px");
    assert Objects.equals(linesOut.get(7), "--");
    assert Objects.equals(linesOut.get(8), "Winner: pw3");
    assert Objects.equals(linesOut.get(9), "\t\tLoser: p3");
    assert Objects.equals(linesOut.get(10), "--");

    ////cinquena pocico

    //set Mock
    editorFile.setBool(true);
    lines = new ArrayList<>();
    lines.add("Winner: pw1");
    lines.add("\t\tLoser: p1");
    lines.add("--");
    lines.add("Winner: pw2");
    lines.add("\t\tLoser: p21");
    lines.add("\t\tLoser: p22");//5
    lines.add("--");
    lines.add("Winner: pw3");
    lines.add("\t\tLoser: p3");
    lines.add("--");
    lines.add("Winner: pw4");//10
    lines.add("\t\tLoser: p4");
    lines.add("--");
    lines.add("Winner: pw5");
    lines.add("\t\tLoser: p51");
    lines.add("\t\tLoser: p52");//15
    lines.add("\t\tLoser: p53");
    lines.add("\t\tLoser: p54");
    lines.add("\t\tLoser: p55");
    lines.add("\t\tLoser: p56");
    //...               //20
    lines.add("--");
    lines.add("Winner: pw6");
    lines.add("\t\tLoser: p6");
    lines.add("\t\tLoser: p6");
    lines.add("\t\tLoser: p6");//25
    lines.add("\t\tLoser: p6");
    lines.add("\t\tLoser: p6");
    lines.add("--");
    editorFile.setRead(lines);

    //executar saveData
    ranking.saveData("pw5","px");
    linesOut = new ArrayList<>();

    //getOutput
    linesOut = editorFile.getWrite();

    //comprobacio
    assert linesOut.size() == 29;
    assert Objects.equals(linesOut.get(13), "Winner: pw5");
    assert Objects.equals(linesOut.get(20), "\t\tLoser: px");

    ////ultima pocico

    //set Mock
    editorFile.setBool(true);
    lines = new ArrayList<>();
    lines.add("Winner: pw1");
    lines.add("\t\tLoser: p1");
    lines.add("--");
    lines.add("Winner: pw2");
    lines.add("\t\tLoser: p21");
    lines.add("\t\tLoser: p22");//5
    lines.add("--");
    lines.add("Winner: pw3");
    lines.add("\t\tLoser: p3");
    lines.add("--");
    lines.add("Winner: pw4");//10
    lines.add("\t\tLoser: p4");
    lines.add("--");
    lines.add("Winner: pw5");
    lines.add("\t\tLoser: p51");
    lines.add("\t\tLoser: p52");//15
    lines.add("\t\tLoser: p53");
    lines.add("\t\tLoser: p54");
    lines.add("\t\tLoser: p55");
    lines.add("\t\tLoser: p56");
    lines.add("--");//20
    lines.add("Winner: pw6");
    lines.add("\t\tLoser: p61");
    lines.add("\t\tLoser: p62");
    lines.add("\t\tLoser: p63");
    lines.add("\t\tLoser: p64");//25
    lines.add("\t\tLoser: p65");
    lines.add("--");
    editorFile.setRead(lines);

    //executar saveData
    ranking.saveData("pw6","p65");
    linesOut = new ArrayList<>();

    //getOutput
    linesOut = editorFile.getWrite();

    //comprobacio
    assert linesOut.size() == 29;
    assert Objects.equals(linesOut.get(21), "Winner: pw6");
    assert Objects.equals(linesOut.get(27), "\t\tLoser: p65");

    ///no existeix Winer
    //set Mock
    editorFile.setBool(true);
    lines = new ArrayList<>();
    lines.add("Winner: pw1");
    lines.add("\t\tLoser: p1");
    lines.add("--");
    lines.add("Winner: pw2");
    lines.add("\t\tLoser: p21");
    lines.add("\t\tLoser: p22");//5
    lines.add("--");
    lines.add("Winner: pw3");
    lines.add("\t\tLoser: p3");
    lines.add("--");
    lines.add("Winner: pw4");//10
    lines.add("\t\tLoser: p4");
    lines.add("--");
    lines.add("Winner: pw5");
    lines.add("\t\tLoser: p51");
    lines.add("\t\tLoser: p52");//15
    lines.add("\t\tLoser: p53");
    lines.add("\t\tLoser: p54");
    lines.add("\t\tLoser: p55");
    lines.add("\t\tLoser: p56");
    lines.add("--");//20
    lines.add("Winner: pw6");
    lines.add("\t\tLoser: p61");
    lines.add("\t\tLoser: p62");
    lines.add("\t\tLoser: p63");
    lines.add("\t\tLoser: p64");//25
    lines.add("\t\tLoser: p65");
    lines.add("--");
    editorFile.setRead(lines);

    //executar saveData
    ranking.saveData("pw7","p7");
    linesOut = new ArrayList<>();

    //getOutput
    linesOut = editorFile.getWrite();

    //comprobacio
    assert linesOut.size() == 31;
    assert Objects.equals(linesOut.get(28), "Winner: pw7");
    assert Objects.equals(linesOut.get(29), "\t\tLoser: p7");
    assert Objects.equals(linesOut.get(30), "--");

    //no existeix el fitcher
    editorFile.setBool(false);
    editorFile.setRead(new ArrayList<>());

    linesOut = new ArrayList<>();
    ranking.saveData("p1","p2");
    linesOut = editorFile.getWrite();
    assert linesOut.size() == 3;
    assert Objects.equals(linesOut.get(0), "Winner: p1");
    assert Objects.equals(linesOut.get(1), "\t\tLoser: p2");
    assert Objects.equals(linesOut.get(2), "--");
  }

  @Test
  void compareStringsTest() {
    Ranking ranking = new Ranking();
    //test Ok
    //simple
    assert ranking.compareStringsRedirect("a","a");
    //llarc
    assert ranking.compareStringsRedirect("bsssb","bsssb");
    //test no Ok
    //tamany
    assert !ranking.compareStringsRedirect("ccc","cc");
    assert !ranking.compareStringsRedirect("hhh","hhhh");
  }

  @Test
  void saveAndGetDataTest(){
    Ranking ranking = new Ranking();

    ranking.deleteFile();

    ranking.saveData("pw1","p1");
    ranking.saveData("pw2","p21");
    ranking.saveData("pw2","p22");
    ranking.saveData("pw2","px");
    ranking.saveData("pw3","p3");

    ArrayList<String> lines = ranking.getData();

    assert lines.size() == 11;
    assert Objects.equals(lines.get(0), "Winner: pw1");
    assert Objects.equals(lines.get(1), "\t\tLoser: p1");
    assert Objects.equals(lines.get(2), "--");
    assert Objects.equals(lines.get(3), "Winner: pw2");
    assert Objects.equals(lines.get(4), "\t\tLoser: p21");
    assert Objects.equals(lines.get(5), "\t\tLoser: p22");
    assert Objects.equals(lines.get(6), "\t\tLoser: px");
    assert Objects.equals(lines.get(7), "--");
    assert Objects.equals(lines.get(8), "Winner: pw3");
    assert Objects.equals(lines.get(9), "\t\tLoser: p3");
    assert Objects.equals(lines.get(10), "--");

    ranking.deleteFile();

  }
}