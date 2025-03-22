
package base.no.states.groups;

//It represents a user
//This class has assigned a group, a credential
//and the name of the user

public class User {
  private final String name;
  private final String credential;
  private Group group;
  public User(final String consName,
              final String consCredential, final Group consGroup) {
    this.name = consName;
    this.credential = consCredential;
    this.group = consGroup;
  }
  public String getCredential() {
    return credential;
  }
  public Group getGrup() {
    return group; }
  @Override
  public String toString() {
    return "User{name=" + name + ", credential=" + credential + "}";
  }



}
