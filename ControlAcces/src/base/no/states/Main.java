
package base.no.states;

// Before executing enable assertions :
// https://se-education.org/guides/tutorials/intellijUsefulSettings.html

import base.no.states.areas.DirectoryAreas;
import base.no.states.groups.DirectoryGroup;

//It initiates the execution of all the program

public final class Main {
  private Main() { }
  public static void main(final String[] args) {
    DirectoryAreas.makeAreas();
    DirectoryGroup.makeGroups();
    new WebServer();
  }
}
