package Model;
import java.util.ArrayList;

public class MockEditorFile extends EditorFile{
  private boolean bool = true;
  private ArrayList<String> read;
  private ArrayList<String> write;
  public MockEditorFile() { }
  public void setBool(boolean bol) {
    bool = bol;
  }
  public void setRead(ArrayList<String> array) {
    read = array;
  }
  public ArrayList<String> getWrite() {
    return write;
  }
  @Override
  public boolean ifExist() {
    return bool;
  }
  @Override
  public boolean write(ArrayList<String> linesNewContent) {
    write = linesNewContent;
    return bool;
  }
  @Override
  public ArrayList<String> read() {
    return read;
  }
  @Override
  public boolean createFile() {
    return bool;
  }
}
