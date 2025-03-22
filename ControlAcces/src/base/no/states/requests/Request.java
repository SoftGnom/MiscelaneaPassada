
package base.no.states.requests;
import org.json.JSONObject;

//It's the base part of a template method
//Given the subclasses it will create a type of request

public interface Request {
  JSONObject answerToJson();
  String toString();
  void process();
}
