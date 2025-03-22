
package base.no.states;

//This class identifies all the diferent
// actions that the doors can do

public final class Actions {
  private Actions() { }
  // possible actions in reader and area requests
  public static final String LOCK = "lock";
  public static final String UNLOCK = "unlock";
  public static final String UNLOCK_SHORTLY = "unlock_shortly";
  // possible actions in door requests
  public static final String OPEN = "open";
  public static final String CLOSE = "close";
}
